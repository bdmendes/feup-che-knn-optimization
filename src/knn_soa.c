#include <omp.h>
#include <string.h>

#include "knn.h"
#include "knn_soa.h"
#include "params.h"
#include "stdio.h"

#ifdef VARIABLE_PARAMETERS
static void get_k_NN_soa_merge(Point new_point, Points points,
                               BestPoint *best_points, int k, int num_classes,
                               int num_features, int num_points) {
#else
static void get_k_NN_soa_merge(Point new_point, Points points,
                               BestPoint *best_points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

#if !defined(PARALLELIZATION) || defined(MERGE_SINGLE)
    BestPoint closestPoints[k];
#else
    BestPoint closestPoints[k * omp_get_max_threads()];
#endif

#if defined(PARALLELIZATION) && !defined(MERGE_SINGLE)
#pragma omp parallel
#endif
    {
#if defined(PARALLELIZATION) && !defined(MERGE_SINGLE)
        int threadNum = omp_get_thread_num();
        BestPoint *localClosest = &closestPoints[k * threadNum];
#else
        BestPoint *localClosest = closestPoints;
#endif

        for (int i = 0; i < k; i++) {
            localClosest[i].distance = DBL_MAX;
        }
#if defined(PARALLELIZATION) && !defined(MERGE_SINGLE)
#pragma omp for
#endif
        for (int i = 0; i < num_points; i++) {
            DATA_TYPE distance = 0;
            int idx =
                i * num_features; // bdmendes: This is better than calculating i
                                  // * NUM_FEATURES + j every time
            for (int j = 0; j < num_features; j++) {
                DATA_TYPE diff =
                    new_point.features[j] - (DATA_TYPE)points.features[idx];
                distance += diff * diff;
                idx++;
            }

            // Find the farthest point in the localClosest array
            int maxIndex = 0;
            for (int j = 1; j < k; j++) {
                if (localClosest[j].distance >
                    localClosest[maxIndex].distance) {
                    maxIndex = j;
                }
            }

            // If the current point is closer than the farthest point in the
            // localClosest array, replace it
            if (distance < localClosest[maxIndex].distance) {
                localClosest[maxIndex].classification_id =
                    points.classifications[i];
                localClosest[maxIndex].distance = distance;
            }
        }
    }

    // Merge the results
    for (int i = 0; i < k; i++) {
        best_points[i].distance = DBL_MAX;
    }

#if defined(PARALLELIZATION) && !defined(MERGE_SINGLE)
    for (int i = 0; i < k * omp_get_max_threads(); i++)
#else
    for (int i = 0; i < k; i++)
#endif
    {
        int maxIndex = 0;
        for (int j = 1; j < k; j++) {
            if (best_points[j].distance > best_points[maxIndex].distance) {
                maxIndex = j;
            }
        }
        if (closestPoints[i].distance < best_points[maxIndex].distance) {
            best_points[maxIndex] = closestPoints[i];
        }
    }
}

#ifdef VARIABLE_PARAMETERS
static void get_k_NN_soa(Point new_point, Points points, BestPoint *best_points,
                         int k, int num_features, int num_points) {
#else
static void get_k_NN_soa(Point new_point, Points points,
                         BestPoint *best_points) {
#define k K
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

    BestPoint dist_points[num_points];

#ifdef PARALLELIZATION
#pragma omp parallel for
#endif
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE sum = 0;
        int idx = i * num_features; // bdmendes: This is better than calculating
                                    // i * NUM_FEATURES + j every time
        for (int j = 0; j < num_features; j++) {
            DATA_TYPE diff =
                new_point.features[j] - (DATA_TYPE)points.features[idx];
            sum += diff * diff;
            idx++;
        }
        dist_points[i].distance = sum;
        dist_points[i].classification_id = points.classifications[i];
    }

    // bdmendes: Let us use the specialized functions instead of the generic
    // ones. select_k_nearest(dist_points, NUM_TRAINING_SAMPLES, k);
#ifdef VARIABLE_PARAMETERS
    select_k_nearest_specific(dist_points, k, num_points);
#else
    select_k_nearest_specific(dist_points);
#endif

#ifdef VARIABLE_PARAMETERS
#ifndef MEMSET
    copy_k_nearest(dist_points, best_points, k);
#else
    copy_k_nearest_specific(dist_points, best_points, k);
#endif
#else
#ifndef MEMSET
    copy_k_nearest(dist_points, best_points);
#else
    copy_k_nearest_specific(dist_points, best_points);
#endif
#endif
}

#ifdef VARIABLE_PARAMETERS
static void get_k_NN_soa_inverted(Point new_point, Points points,
                                  BestPoint *best_points, int k,
                                  int num_features, int num_points) {
#else
static void get_k_NN_soa_inverted(Point new_point, Points points,
                                  BestPoint *best_points) {
#define k K
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

    // Generate difference feature by feature, point by point
    DATA_TYPE feature_diffs[num_features][num_points];

#ifdef PARALLELIZATION
#pragma omp parallel for
#endif
    for (int i = 0; i < num_features; i++) {
        DATA_TYPE new_point_feature = (DATA_TYPE)new_point.features[i];
        for (int j = 0; j < num_points; j++) {
            DATA_TYPE diff = new_point_feature -
                             (DATA_TYPE)points.features[i * num_points + j];
            feature_diffs[i][j] = diff * diff;
        }
    }

    // Generate difference point by point
    BestPoint dist_points[num_points];

#ifdef PARALLELIZATION
#pragma omp parallel for
#endif
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE sum = 0;
        for (int j = 0; j < num_features; j++) {
            sum += feature_diffs[j][i];
        }
        dist_points[i].distance = sum;
        dist_points[i].classification_id = points.classifications[i];
    }

#ifdef VARIABLE_PARAMETERS
    select_k_nearest_specific(dist_points, k, num_points);

#ifndef MEMSET
    copy_k_nearest(dist_points, best_points, k);
#else
    copy_k_nearest_specific(dist_points, best_points, k);
#endif
#else
    select_k_nearest_specific(dist_points);

#ifndef MEMSET
    copy_k_nearest(dist_points, best_points);
#else
    copy_k_nearest_specific(dist_points, best_points);
#endif
#endif
}

#ifdef VARIABLE_PARAMETERS
CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point,
                                                PointsInverted points, int k,
                                                int num_classes,
                                                int num_features,
                                                int num_points) {
#else
CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point,
                                                PointsInverted points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

    BestPoint best_points[k];
#ifdef VARIABLE_PARAMETERS
    get_k_NN_soa_inverted(new_point, points, best_points, k, num_features,
                          num_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
#else
    get_k_NN_soa_inverted(new_point, points, best_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points);
#endif

    return classID;
}

#ifdef VARIABLE_PARAMETERS
CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, Points points, int k,
                                       int num_classes, int num_features,
                                       int num_points) {
#else
CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, Points points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

    BestPoint best_points[K];
#ifdef VARIABLE_PARAMETERS
    get_k_NN_soa(new_point, points, best_points, k, num_features, num_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
#else
    get_k_NN_soa(new_point, points, best_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points);
#endif

    return classID;
}

#ifdef VARIABLE_PARAMETERS
CLASS_ID_TYPE knn_classifyinstance_soa_merge(Point new_point, Points points,
                                             int k, int num_classes,
                                             int num_features, int num_points) {
#else
CLASS_ID_TYPE knn_classifyinstance_soa_merge(Point new_point, Points points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
#endif

    BestPoint best_points[k];
#ifdef VARIABLE_PARAMETERS
    get_k_NN_soa_merge(new_point, points, best_points, k, num_classes,
                       num_features, num_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
#else
    get_k_NN_soa_merge(new_point, points, best_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points);
#endif

    return classID;
}
