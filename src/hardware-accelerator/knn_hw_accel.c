#include "knn_hw_accel.h"
#include "../params.h"

void hw_get_eucledean_distances(Point new_point, DATA_TYPE *points_features,
                                DATA_TYPE *dist_points_distances) {
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES

    for (int i = 0; i < num_points; i++) {
        DATA_TYPE diffs[num_features];
        int idx =
            i * num_features;
        for (int j = 0; j < num_features; j++) {
            DATA_TYPE diff =
                new_point.features[j] - points_features[idx];
            diffs[j] = diff * diff;
            idx++;
        }

        DATA_TYPE distance = 0.0;
        for(int j = 0; j < num_features; j++){
        	distance += diffs[j];
        }
        dist_points_distances[i] = distance;
    }
}
