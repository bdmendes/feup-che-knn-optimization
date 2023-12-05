#include "knn_soa.h"
#include "knn.h"
#include "stdio.h"

static void get_k_NN_soa_inverted(Point new_point, Points points, BestPoint *best_points,
                                  int k)
{
    // Generate difference feature by feature, point by point
    DATA_TYPE feature_diffs[NUM_FEATURES][NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_FEATURES; i++)
    {
        DATA_TYPE new_point_feature = (DATA_TYPE)new_point.features[i];
        for (int j = 0; j < NUM_TRAINING_SAMPLES; j++)
        {
            DATA_TYPE diff = new_point_feature - (DATA_TYPE)points.features[i * NUM_TRAINING_SAMPLES + j];
            feature_diffs[i][j] = diff * diff;
        }
    }

    // Generate difference point by point
    BestPoint dist_points[NUM_TRAINING_SAMPLES];

#pragma omp parallel for
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
    {
        DATA_TYPE sum = 0;
        for (int j = 0; j < NUM_FEATURES; j++)
        {
            sum += feature_diffs[j][i];
        }
        dist_points[i].distance = sum;
        dist_points[i].classification_id = points.classifications[i];
    }

    select_k_nearest(dist_points, NUM_TRAINING_SAMPLES, k);
    copy_k_nearest(dist_points, NUM_TRAINING_SAMPLES, best_points, k);
}

CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point, int k, int num_classes,
                                                Points points)
{
    BestPoint best_points[k];
    get_k_NN_soa_inverted(new_point, points, best_points, k);
    CLASS_ID_TYPE classID = plurality_voting(k, best_points, num_classes);
    return classID;
}
