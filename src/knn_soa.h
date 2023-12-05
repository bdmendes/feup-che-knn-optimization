#pragma once
#include "types.h"

// bdmendes: We must create new functions
// to accomodate the contiguous features structure.

CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point, int k, int num_classes, PointsInverted points);

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, int k, int num_classes, Points points);
