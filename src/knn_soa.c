#include "knn_soa.h"
#include "knn.h"
#include "params.h"
#include "stdio.h"

static void get_k_NN_soa(Point new_point, Points points, BestPoint *best_points,
                         int k, int num_features, int num_points) {
    BestPoint dist_points[num_points];

#pragma omp parallel for
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

    select_k_nearest_specific(dist_points, k, num_points);

#ifdef ASSIGNMENT_LOOP
    copy_k_nearest(dist_points, best_points, k);
#else
    copy_k_nearest_specific(dist_points, best_points, k);
#endif
}

static void get_k_NN_soa_static(Point new_point, Points points,
                                BestPoint *best_points) {
    BestPoint dist_points[NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++) {
        DATA_TYPE sum = 0;
        int idx = i * NUM_FEATURES; // bdmendes: This is better than calculating
                                    // i * NUM_FEATURES + j every time
        for (int j = 0; j < NUM_FEATURES; j++) {
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

    select_k_nearest_specific_static(dist_points);

#ifdef ASSIGNMENT_LOOP
    copy_k_nearest_static(dist_points, best_points);
#else
    copy_k_nearest_specific_static(dist_points, best_points);
#endif
}

static void get_k_NN_soa_inverted(Point new_point, Points points,
                                  BestPoint *best_points, int k,
                                  int num_features, int num_points) {
    // Generate difference feature by feature, point by point
    DATA_TYPE feature_diffs[num_features][num_points];

#pragma omp parallel for
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

#pragma omp parallel for
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE sum = 0;
        for (int j = 0; j < num_features; j++) {
            sum += feature_diffs[j][i];
        }
        dist_points[i].distance = sum;
        dist_points[i].classification_id = points.classifications[i];
    }

    select_k_nearest_specific(dist_points, k, num_points);

#ifdef ASSIGNMENT_LOOP
    copy_k_nearest(dist_points, best_points, k);
#else
    copy_k_nearest_specific(dist_points, best_points, k);
#endif
}

static void get_k_NN_soa_inverted_static(Point new_point, Points points,
                                         BestPoint *best_points) {
    // Generate difference feature by feature, point by point
    DATA_TYPE feature_diffs[NUM_FEATURES][NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_FEATURES; i++) {
        DATA_TYPE new_point_feature = (DATA_TYPE)new_point.features[i];
        for (int j = 0; j < NUM_TRAINING_SAMPLES; j++) {
            DATA_TYPE diff =
                new_point_feature -
                (DATA_TYPE)points.features[i * NUM_TRAINING_SAMPLES + j];
            feature_diffs[i][j] = diff * diff;
        }
    }

    // Generate difference point by point
    BestPoint dist_points[NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++) {
        DATA_TYPE sum = 0;
        for (int j = 0; j < NUM_FEATURES; j++) {
            sum += feature_diffs[j][i];
        }
        dist_points[i].distance = sum;
        dist_points[i].classification_id = points.classifications[i];
    }

    select_k_nearest_specific_static(dist_points);

#ifdef ASSIGNMENT_LOOP
    copy_k_nearest_static(dist_points, best_points);
#else
    copy_k_nearest_specific_static(dist_points, best_points);
#endif
}

CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point,
                                                PointsInverted points, int k,
                                                int num_classes,
                                                int num_features,
                                                int num_points) {
    BestPoint best_points[k];
    get_k_NN_soa_inverted(new_point, points, best_points, k, num_features,
                          num_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
    return classID;
}

CLASS_ID_TYPE knn_classifyinstance_soa_inverted_static(Point new_point,
                                                       PointsInverted points) {
    BestPoint best_points[K];
    get_k_NN_soa_inverted_static(new_point, points, best_points);
    CLASS_ID_TYPE classID = plurality_voting_static(best_points);
    return classID;
}

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, Points points, int k,
                                       int num_classes, int num_features,
                                       int num_points) {
    BestPoint best_points[K];
    get_k_NN_soa(new_point, points, best_points, k, num_features, num_points);
    CLASS_ID_TYPE classID = plurality_voting(best_points, num_classes);
    return classID;
}

CLASS_ID_TYPE knn_classifyinstance_soa_static(Point new_point, Points points) {
    BestPoint best_points[K];
    get_k_NN_soa_static(new_point, points, best_points);
    CLASS_ID_TYPE classID = plurality_voting_static(best_points);
    return classID;
}
