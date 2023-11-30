#include "knn_soa.h"
#include "knn.h"
#include "stdio.h"

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, int k, int num_classes, CLASS_ID_TYPE *known_points_classifications,
                                       DATA_TYPE *known_points_features, int num_points, int num_features)
{
    BestPoint best_points[k];

    get_k_NN_soa(new_point, known_points_classifications, known_points_features, num_points, best_points, k, num_features);

    CLASS_ID_TYPE classID = plurality_voting(k, best_points, num_classes);

    return classID;
}

void get_k_NN_soa(Point new_point, CLASS_ID_TYPE *known_points_classifications, DATA_TYPE *known_points_features,
                  int num_points, BestPoint *best_points,
                  int k, int num_features)
{
    // Generate difference feature by feature, point by point
    DATA_TYPE feature_diffs[NUM_TRAINING_SAMPLES * NUM_FEATURES];

#pragma omp parallel for
    for (int i = 0; i < num_features; i++)
    {
        int base_idx = i * num_points;
        for (int j = 0; j < num_points; j++)
        {
            DATA_TYPE diff = (DATA_TYPE)new_point.features[i] - (DATA_TYPE)known_points_features[base_idx + j];
            feature_diffs[base_idx + j] = diff * diff;
        }
    }

    // Generate difference point by point
    DATA_TYPE points_diffs[NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
    {
        DATA_TYPE sum = 0;
        for (int j = 0; j < NUM_FEATURES; j++)
        {
            sum += feature_diffs[j * NUM_TRAINING_SAMPLES + i];
        }
        points_diffs[i] = sum;
    }

    // Fill "best points"
    BestPoint dist_points[NUM_TRAINING_SAMPLES];
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
    {
        dist_points[i].classification_id = known_points_classifications[i];
        dist_points[i].distance = points_diffs[i];
        // printf("SOA_dist_points[%d] = %f\n", i, points_diffs[i]);
    }

    select_k_nearest(dist_points, num_points, k);
    copy_k_nearest(dist_points, num_points, best_points, k);
}