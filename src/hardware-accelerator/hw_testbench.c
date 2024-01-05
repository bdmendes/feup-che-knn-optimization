#include <stdio.h>

#include "../params.h"
#include "../preprocess.h"
#include "../types.h"
#include "../utils.h"
#include "knn_hw_accel.h"
#include "../knn.h"

#if TIMMING == 1
#include "../timer.h"
#endif

Point known_points1[NUM_TRAINING_SAMPLES] = {
#include "../train.dat"
}; //{{{1,2,3,4,5},'a'}};
Point *known_points = known_points1;

Point new_points1[NUM_TESTING_SAMPLES] = {
#include "../test.dat"
}; //{{{1,2,3,4,5},'a'}};
Point *new_points = new_points1;


char key[NUM_TESTING_SAMPLES] = {
#if K == 20
#include "../key-READ1-k20.dat"
#elif K == 3
#include "../key-READ1-k3.dat"
#endif
};

CLASS_ID_TYPE hw_knn_classifyinstance(Point new_point,
                                                Points points) {
#define k K
#define num_classes NUM_CLASSES
#define num_features NUM_FEATURES
#define num_points NUM_TRAINING_SAMPLES
    
    DATA_TYPE dist_points_distances[num_points];
    hw_get_eucledean_distances(new_point, points.features, dist_points_distances);

    BestPoint best_points[num_points];
    for (int i = 0; i< num_points; i++){
        best_points[i].distance = dist_points_distances[i];
        best_points[i].classification_id = points.classifications[i];
    }

    select_k_nearest_specific(best_points);
    return plurality_voting(best_points);

#undef k
#undef num_classes
#undef num_features
#undef num_points
}

int main(int argc, char **argv) {
    int num_points, num_classes, num_new_points, k;
    const int num_features = NUM_FEATURES;

    printf("Data points initialized with WISDM dataset...\n");

    k = K;
    num_classes = NUM_CLASSES;
    num_points = NUM_TRAINING_SAMPLES;
    num_new_points = NUM_TESTING_SAMPLES;

    printf("Initialization done.\n\n");

    DATA_TYPE min[num_features];
    DATA_TYPE max[num_features];

    // determine min and max from known points
    minmax(min, max, num_points, known_points, num_features);

    // normalize known points
    minmax_normalize(min, max, num_points, known_points, num_features);

    printf("Executing kNN...\n");

    /*
            bdmendes: Data structure transformation.
            Contiguosly storing the features in memory increases
            cache locality while accessing the same features.
    */
    DATA_TYPE known_points_features[NUM_FEATURES * NUM_TRAINING_SAMPLES];
    CLASS_ID_TYPE known_points_classifications[NUM_TRAINING_SAMPLES];

    Points points =
        extract_soa(known_points, (DATA_TYPE *)known_points_features,
                    (CLASS_ID_TYPE *)known_points_classifications);

    int fail = 0; // count the number of test instances incorrectly classified

    // Loop over the input instances to classify.
    // Note that depending on the application this can be
    // instances arriving as streaming data.
    // Here assume that the loop below needs to run in serial mode and the
    // value of num_new_point is just to test

#if TIMMING == 1
    Timer *timer = timer_init();
    timer_start(timer);
#endif
    for (int i = 0; i < num_new_points; i++) {
        // Get instance to classify
        // in a streaming implementation this might be something like:
        // Point *new_point = getPoint();
        Point *new_point = &new_points[i];

        // normalize the point to classify
        minmax_normalize_point(min, max, new_point, num_features);

        // bdmendes: We need to call a new function to fit in the SoA structure.

        CLASS_ID_TYPE instance_class =
            hw_knn_classifyinstance(*new_point, points);

        // to show the data associated to the point
        // show_point(*new_points,num_features);

        if (new_point->classification_id != instance_class)
            fail++;

        new_point->classification_id = instance_class;
    }

#if TIMMING == 1
    timer_stop(timer);
#endif

    printf("kNN done.\n\n");

    printf("kNN: number of classes = %d\n", num_classes);
    printf("kNN: number of training instances = %d\n", num_points);
    printf("kNN: number of features = %d\n", num_features);
    printf("kNN: k = %d\n", k);

    if (sizeof(DATA_TYPE) == 4)
        printf("kNN: data type used = float\n");
    else if (sizeof(DATA_TYPE) == 8)
        printf("kNN: data type used = double\n");

    printf("kNN: number of classified instances = %d\n", num_new_points);

    printf("kNN: number of classifications wrong = %d\n", fail);
    printf("kNN: number of classifications right = %d\n",
           num_new_points - fail);
    printf("kNN: accuracy = %.2f %c\n\n",
           100 * (float)(num_new_points - fail) / (float)num_new_points, '%');

#if TIMMING == 1
    const double time = timer_get_s(timer);

    printf("\nTime:  %.4f s\n", time);

    timer = timer_destroy(timer);
#endif

    printf("kNN: verifying results...\n");
    return verify_results(num_new_points, new_points, key);
}
