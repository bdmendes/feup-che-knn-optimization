#include "preprocess.h"
#include "stdio.h"

void extract_features(Point *points, int points_len,
                      DATA_TYPE *out)
{
    // for (int i = 0; i < 4; i++)
    // {
    //     Point *point = points + i;
    //     for (int j = 0; j < NUM_FEATURES; j++)
    //     {
    //         printf("point %d feature %d: %f\n", i, j, point->features[j]);
    //     }
    // }

    // out has size = sizeof(points) * NUM_CLASSES
    int curr_idx = 0;
    for (int i = 0; i < NUM_FEATURES; i++)
    {
        for (int j = 0; j < points_len; j++)
        {
            Point *point = &points[j];
            out[curr_idx + j] = point->features[i];
        }
        curr_idx += points_len;
    }
}

void extract_classifications(Point *points, int points_len,
                             CLASS_ID_TYPE *out)
{
    for (int i = 0; i < points_len; i++)
    {
        Point *point = &points[i];
        out[i] = point->classification_id;
    }
}
