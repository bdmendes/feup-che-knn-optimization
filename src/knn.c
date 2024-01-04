/**
 *	k-NN
 *
 *	Versions
 *	- v0.1, December 2016
 *	- v0.2, November 2019
 *	- v0.5, November 2021
 *   - v0.6, October 2023
 *
 *	by Joao MP Cardoso
 *	Email: jmpc@fe.up.pt
 *
 *	SPeCS, FEUP.DEI, University of Porto, Portugal
 */

#include "params.h"
#include <math.h>
#include <stdlib.h>

#ifndef NDEBUG
#define NDEBUG // disable assertions
#endif

#include "stdio.h"
#include <assert.h>

#include "knn.h"

#include <string.h>

#ifdef VARIABLE_PARAMETERS
void copy_k_nearest_specific(BestPoint *dist_points, BestPoint *best_points,
                             int k) {
#else
void copy_k_nearest_specific(BestPoint *dist_points, BestPoint *best_points) {
#define k K
#endif

    memcpy(best_points, dist_points, k * sizeof(BestPoint));
}

#ifdef VARIABLE_PARAMETERS
void select_k_nearest_specific(BestPoint *dist_points, int k, int num_points) {
#else
void select_k_nearest_specific(BestPoint *dist_points) {
#define k K
#define num_points NUM_TRAINING_SAMPLES
#endif
    DATA_TYPE min_distance;
    int index;

    for (int i = 0; i < k; i++) { // we only need the top k minimum distances
        min_distance = dist_points[i].distance;
        index = i;
        for (int j = i + 1; j < num_points; j++) {
            if (dist_points[j].distance < min_distance) {
                min_distance = dist_points[j].distance;
                index = j;
            }
        }
        if (index != i) { // swap
            BestPoint tmp = dist_points[index];
            dist_points[index] = dist_points[i];
            dist_points[i] = tmp;
        }
    }
}

/**
 *  Copy the top k nearest points (first k elements of dist_points)
 *  to a data structure (best_points) with k points
 */
#ifdef VARIABLE_PARAMETERS
void copy_k_nearest(BestPoint *dist_points, BestPoint *best_points, int k) {
#else
void copy_k_nearest(BestPoint *dist_points, BestPoint *best_points) {
#define k K
#endif
    // bdmendes: We can do this with a memcpy. See copy_k_nearest_specific.
    for (int i = 0; i < k; i++) { // we only need the top k minimum distances
        best_points[i].classification_id = dist_points[i].classification_id;
        best_points[i].distance = dist_points[i].distance;
    }
}

/**
 *  Get the k nearest points.
 *  This version stores the k nearest points in the first k positions of
 * dis_point
 */
#ifdef VARIABLE_PARAMETERS
void select_k_nearest(BestPoint *dist_points, int num_points, int k) {
#else
void select_k_nearest(BestPoint *dist_points) {
#define k K
#define num_points NUM_TRAINING_SAMPLES
#endif
    DATA_TYPE min_distance;
    int index;

    for (int i = 0; i < k; i++) { // we only need the top k minimum distances
        min_distance = dist_points[i].distance;
        index = i;
        for (int j = i + 1; j < num_points; j++) {
            if (dist_points[j].distance < min_distance) {
                min_distance = dist_points[j].distance;
                index = j;
            }
        }
        if (index != i) { // swap
            // bdmedes: We can do this in a cleaner way.
            // distance_i = dist_points[index].distance;
            // class_id_1 = dist_points[index].classification_id;

            // dist_points[index].distance = dist_points[i].distance;
            // dist_points[index].classification_id =
            // dist_points[i].classification_id;

            // dist_points[i].distance = distance_i;
            // dist_points[i].classification_id = class_id_1;

            BestPoint tmp = dist_points[index];
            dist_points[index] = dist_points[i];
            dist_points[i] = tmp;
        }
    }
}

/*
 * Main kNN function.
 * It calculates the distances and calculates the nearest k points.
 */
#ifdef VARIABLE_PARAMETERS
void get_k_NN(Point new_point, Point *known_points, int num_points,
              BestPoint *best_points, int k, int num_features) {
#else
void get_k_NN(Point new_point, Point *known_points, BestPoint *best_points) {
#define k K
#define num_points NUM_TRAINING_SAMPLES
#define num_features NUM_FEATURES
#endif
    BestPoint dist_points[num_points];

// calculate the Euclidean distance between the Point to classify and each one
// in the model and update the k best points if needed

// bdmendes: This is embarrassingly parallel.
// bdmendes: Speedup: 2
#ifdef PARALLELIZATION
#pragma omp parallel for
#endif
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE distance = (DATA_TYPE)0.0;

        // calculate the Euclidean distance

        // bdmendes: Let us apply a parallel reduction here.
#if defined(PARALLELIZATION) && defined(PARALLEL_REDUCTION)
#pragma omp parallel for reduction(+ : distance)
#endif
        // bdmendes: Speedup: 0.043
        // bdmendes: We are yielding too many threads here.
        for (int j = 0; j < num_features; j++) {
            DATA_TYPE diff = (DATA_TYPE)new_point.features[j] -
                             (DATA_TYPE)known_points[i].features[j];
            distance += diff * diff;
        }
        // distance = sqrt(distance);

        dist_points[i].classification_id = known_points[i].classification_id;
        dist_points[i].distance = distance;
    }
#ifdef VARIABLE_PARAMETERS
    select_k_nearest(dist_points, num_points, k);

#ifndef MEMSET
    copy_k_nearest(dist_points, best_points, k);
#else
    copy_k_nearest_specific(dist_points, best_points, k);
#endif

#else
    select_k_nearest(dist_points);

#ifndef MEMSET
    copy_k_nearest(dist_points, best_points);
#else
    copy_k_nearest_specific(dist_points, best_points);
#endif
#endif
}

/*
 *	Classify using the k nearest neighbors identified by the get_k_NN
 *	function. The classification uses plurality voting.
 *
 *	Note: it assumes that classes are identified from 0 to
 *	num_classes - 1.
 */
#ifdef VARIABLE_PARAMETERS
CLASS_ID_TYPE plurality_voting(BestPoint *best_points, int num_classes) {
#else
CLASS_ID_TYPE plurality_voting(BestPoint *best_points) {
#define num_classes NUM_CLASSES
#endif
    // bdmendes: specialized implementation for K=3
    // This makes the execution slower.
#ifdef SPECIFIC_VOTING
#if K == 3
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
    CLASS_ID_TYPE class_0 = best_points[0].classification_id;
    CLASS_ID_TYPE class_1 = best_points[1].classification_id;
    CLASS_ID_TYPE class_2 = best_points[2].classification_id;

    if (class_0 == class_1 || class_0 == class_2) {
        return class_0;
    } else if (class_1 == class_2) {
        return class_1;
    } else {
        return MIN(class_0, MIN(class_1, class_2));
    }
#endif
#endif

    CLASS_ID_TYPE histogram[num_classes]; // maximum is the value of k

    // initialize the histogram
#ifndef MEMSET
    // bdmendes: We can do this with a memset.
    for (int i = 0; i < num_classes; i++) {
        histogram[i] = 0;
    }
#else
    memset(histogram, 0, num_classes * sizeof(CLASS_ID_TYPE));
#endif

    // build the histogram
    // bdmendes: Use specific k.
    for (int i = 0; i < K; i++) {
        BestPoint p = best_points[i];
        // if (best_points[i].distance < min_distance) {
        //     min_distance = best_points[i].distance;
        // }

        // bdmendes: Comment out debug code.
        // assert(p.classification_id != -1);

        histogram[(int)p.classification_id] += 1;
    }

    CLASS_ID_TYPE max = 0;                // maximum is k
    CLASS_ID_TYPE classification_id = -1; // -1 represents an unknown class
    for (int i = 0; i < num_classes; i++) {
        if (histogram[i] > max) {
            max = histogram[i];
            classification_id = (CLASS_ID_TYPE)i;
        }
    }

    return classification_id;
}

/*
 * Classify a given Point (instance).
 * It returns the classified class ID.
 */
#ifdef VARIABLE_PARAMETERS
CLASS_ID_TYPE knn_classifyinstance(Point new_point, Point *known_points, int k,
                                   int num_classes, int num_features,
                                   int num_points) {
#else
CLASS_ID_TYPE knn_classifyinstance(Point new_point, Point *known_points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif
    BestPoint best_points[k]; // Array with the k nearest points to the Point to
                              // classify

    // calculate the distances of the new point to each of the known points and
    // get the k nearest points
#ifdef VARIABLE_PARAMETERS
    get_k_NN(new_point, known_points, num_points, best_points, k, num_features);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
#else
    get_k_NN(new_point, known_points, best_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points);
#endif

    return classID;
}
