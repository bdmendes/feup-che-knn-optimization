#pragma once
#include "types.h"

// bdmendes: We must create new functions
// to accomodate the contiguous features structure.

CLASS_ID_TYPE knn_classifyinstance_soa_inverted(Point new_point, PointsInverted points);

CLASS_ID_TYPE knn_classifyinstance_soa(Point new_point, Points points);
