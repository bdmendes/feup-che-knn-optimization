#include "preprocess.h"
#include "stdio.h"
#include "stdbool.h"

static void extract_features(Point *points,
                             DATA_TYPE *out, bool inverted)
{
    for (int i = 0; i < NUM_FEATURES; i++)
    {
        for (int j = 0; j < NUM_TRAINING_SAMPLES; j++)
        {
            Point *point = &points[j];
            if (inverted)
            {
                out[i * NUM_TRAINING_SAMPLES + j] = point->features[i];
            }
            else
            {
                out[j * NUM_FEATURES + i] = point->features[i];
            }
        }
    }
}

static void extract_classifications(Point *points,
                                    CLASS_ID_TYPE *out)
{
    for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
    {
        Point *point = &points[i];
        out[i] = point->classification_id;
    }
}

PointsInverted extract_soa_inverted(Point *points,
                                    DATA_TYPE *out_features, CLASS_ID_TYPE *out_classifications)
{
    PointsInverted points_soa;
    extract_classifications(points, out_classifications);
    extract_features(points, out_features, true);
    points_soa.features = out_features;
    points_soa.classifications = out_classifications;
    return points_soa;
}

Points extract_soa(Point *points,
                   DATA_TYPE *out_features, CLASS_ID_TYPE *out_classifications)
{
    Points points_soa;
    extract_classifications(points, out_classifications);
    extract_features(points, out_features, false);
    points_soa.features = out_features;
    points_soa.classifications = out_classifications;
    return points_soa;
}