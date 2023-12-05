#include "params.h"
#include "types.h"

PointsInverted extract_soa_inverted(Point *points,
                                    DATA_TYPE *out_features, CLASS_ID_TYPE *out_classifications);

Points extract_soa(Point *points,
                   DATA_TYPE *out_features, CLASS_ID_TYPE *out_classifications);