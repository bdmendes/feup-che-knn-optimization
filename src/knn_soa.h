#pragma once
#include "types.h"

// bdmendes: We must create new functions
// to accomodate the contiguous features structure.

CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point,
                                                PointsInverted points, int k,
                                                int num_classes,
                                                int num_features,
                                                int num_points);

CLASS_ID_TYPE knn_classifyinstance_soa_inverted_static(Point new_point,
                                                       PointsInverted points);

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, Points points, int k,
                                       int num_classes, int num_features,
                                       int num_points);

CLASS_ID_TYPE knn_classifyinstance_soa_static(Point new_point, Points points);

CLASS_ID_TYPE knn_classifyinstance_soa_merge(Point new_point, Points points,
                                             int k, int num_classes,
                                             int num_features, int num_points);

CLASS_ID_TYPE knn_classifyinstance_soa_merge_static(Point new_point,
                                                    Points points);
