#pragma once
#include "types.h"

// bdmendes: We must create new functions
// to accomodate the contiguous features structure.

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, int k, int num_classes,
                                       CLASS_ID_TYPE *known_points_classifications, DATA_TYPE *known_points_features, int num_points, int num_features);

void get_k_NN_soa(Point new_point, CLASS_ID_TYPE *known_points_classifications, DATA_TYPE *known_points_features, int num_points, BestPoint *best_points,
                  int k, int num_features);