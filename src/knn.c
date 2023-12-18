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

#include <math.h>
#include <stdlib.h>

#ifndef NDEBUG
#define NDEBUG // disable assertions
#endif

#include <assert.h>
#include "stdio.h"

#include "knn.h"

#include <string.h>

void copy_k_nearest_specific(BestPoint *dist_points, BestPoint *best_points)
{
    memcpy(best_points, dist_points, K * sizeof(BestPoint));
}

void select_k_nearest_specific(BestPoint *dist_points)
{
    DATA_TYPE min_distance;
    int index;

    for (int i = 0; i < K; i++)
    { // we only need the top k minimum distances
        min_distance = dist_points[i].distance;
        index = i;
        for (int j = i + 1; j < NUM_TRAINING_SAMPLES; j++)
        {
            if (dist_points[j].distance < min_distance)
            {
                min_distance = dist_points[j].distance;
                index = j;
            }
        }
        if (index != i)
        { // swap
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
void copy_k_nearest(BestPoint *dist_points,
                    BestPoint *best_points)
{
    // bdmendes: We can do this with a memcpy.
    // for (int i = 0; i < k; i++)
    // { // we only need the top k minimum distances
    //     best_points[i].classification_id = dist_points[i].classification_id;
    //     best_points[i].distance = dist_points[i].distance;
    // }

    memcpy(best_points, dist_points, K * sizeof(BestPoint));
}

/**
 *  Get the k nearest points.
 *  This version stores the k nearest points in the first k positions of dis_point
 */
void select_k_nearest(BestPoint *dist_points)
{
    DATA_TYPE min_distance;
    int index;

    for (int i = 0; i < K; i++)
    { // we only need the top k minimum distances
        min_distance = dist_points[i].distance;
        index = i;
        for (int j = i + 1; j < NUM_TRAINING_SAMPLES; j++)
        {
            if (dist_points[j].distance < min_distance)
            {
                min_distance = dist_points[j].distance;
                index = j;
            }
        }
        if (index != i)
        { // swap
            // bdmedes: We can do this in a cleaner way.
            // distance_i = dist_points[index].distance;
            // class_id_1 = dist_points[index].classification_id;

            // dist_points[index].distance = dist_points[i].distance;
            // dist_points[index].classification_id = dist_points[i].classification_id;

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
void get_k_NN(Point new_point, Point *known_points,
              BestPoint *best_points)
{
    BestPoint dist_points[NUM_TRAINING_SAMPLES];

// calculate the Euclidean distance between the Point to classify and each one in the model
// and update the k best points if needed

// bdmendes: This is embarrassingly parallel.
// bdmendes: Speedup: 2
#pragma omp parallel for
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
    {
        DATA_TYPE distance = (DATA_TYPE)0.0;

        // calculate the Euclidean distance

        // bdmendes: Let us apply a parallel reduction here.
        // #pragma omp parallel for reduction(+ : distance)
        // bdmendes: Speedup: 0.043
        // bdmendes: We are yielding too many threads here.
        for (int j = 0; j < NUM_FEATURES; j++)
        {
            DATA_TYPE diff = (DATA_TYPE)new_point.features[j] - (DATA_TYPE)known_points[i].features[j];
            distance += diff * diff;
        }
        distance = sqrt(distance);

        dist_points[i].classification_id = known_points[i].classification_id;
        dist_points[i].distance = distance;
    }

    select_k_nearest(dist_points);

    copy_k_nearest(dist_points, best_points);
}

/*
 *	Classify using the k nearest neighbors identified by the get_k_NN
 *	function. The classification uses plurality voting.
 *
 *	Note: it assumes that classes are identified from 0 to
 *	num_classes - 1.
 */
CLASS_ID_TYPE plurality_voting(BestPoint *best_points)
{
    // bdmendes: specialized implementation for K=3
    // This makes the execution slower.
#if 0 && K == 3
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
    CLASS_ID_TYPE class_0 = best_points[0].classification_id;
    CLASS_ID_TYPE class_1 = best_points[1].classification_id;
    CLASS_ID_TYPE class_2 = best_points[2].classification_id;

    if (class_0 == class_1 || class_0 == class_2)
    {
        return class_0;
    }
    else if (class_1 == class_2)
    {
        return class_1;
    }
    else
    {
        return MIN(class_0, MIN(class_1, class_2));
    }
#endif

    CLASS_ID_TYPE histogram[NUM_CLASSES]; // maximum is the value of k

    // initialize the histogram

    // bdmendes: We can do this with a memset.
    // for (int i = 0; i < num_classes; i++)
    // {
    //     histogram[i] = 0;
    // }

    memset(histogram, 0, NUM_CLASSES * sizeof(CLASS_ID_TYPE));

    // build the histogram
    // bdmendes: Use specific k.
    for (int i = 0; i < K; i++)
    {
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
    for (int i = 0; i < NUM_CLASSES; i++)
    {
        if (histogram[i] > max)
        {
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
CLASS_ID_TYPE knn_classifyinstance(Point new_point, Point *known_points)
{
    BestPoint best_points[K]; // Array with the k nearest points to the Point to classify

    // calculate the distances of the new point to each of the known points and get
    // the k nearest points
    get_k_NN(new_point, known_points, best_points);

    // use plurality voting to return the class inferred for the new point
    CLASS_ID_TYPE classID = plurality_voting(best_points);

    return classID;
}