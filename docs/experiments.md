# kNN optimization: experiments

This document contains the experiments that were run to optimize the kNN algorithm. It serves as the base for a report that will be written in the future.

## Starting point

### How the algorithm works

The kNN implementation we initially have in hands works by:

1. Reading the train and test data points. If `READ` is 1, we embed them in the code, from the local `train.dat` and `test.dat`, using the preprocessor `include` directive. This ensures that the program spends no time reading from the file system and manually allocating heap memory for the data points, even though it requires hardcoding the characteristics of the dataset, such as the size and the number of features. This is used throughout our experiments, as data bootstrapping is not the main concern of the optimisation effort.

2. Known points normalization. knn uses euclidean distances to determine the nearest neighbours used for class voting. As such, we should ensure features have the same weights, via normalization. Train data is scaled to fit in the interval [0,1]. There might be an opportunity for optimisation here, as we do have a lot of nested loops (see the `minimax` function in `utils.c`).

3. knn classification for each distance, which includes, for each test point:
    - Normalizing its features, using the train min and max as target.
    - Determining the `K` nearest points. This works by getting the `k` nearest points in the first `k` positions of an array, in a way that resembles in-place partial sorting.
    - Run the plurality voting, by scoring each available class by the number of neighbour points of that class and getting the top class.
We expect the main source of optimization to be here.

1. Optionally compare the results with the expected ones, to make sure the semantics of the algorithm do not change throughout our optimization efforts and time the computation.

### How the algorithm performs

Let us use `gprof` to measure the execution time of the functions calls troughout our application, on a Linux machine bundled with a Intel® Core™ i7-8550U, running in "Balanced" mode (power-profiles-daemon).

#### -00

Compiling with -O0 yields the following results:

```
Time:  1.0325 s

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 97.75      0.87     0.87     1082   804.07   822.55  get_k_NN
  2.25      0.89     0.02     1082    18.48    18.48  select_k_nearest
  0.00      0.89     0.00     2164     0.00     0.00  get_class_name
  0.00      0.89     0.00     1082     0.00     0.00  copy_k_nearest
  0.00      0.89     0.00     1082     0.00   822.55  knn_classifyinstance
  0.00      0.89     0.00     1082     0.00     0.00  minmax_normalize_point
  0.00      0.89     0.00     1082     0.00     0.00  plurality_voting
  0.00      0.89     0.00        1     0.00     0.00  calc_delta_ms
  0.00      0.89     0.00        1     0.00     0.00  minmax
  0.00      0.89     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.89     0.00        1     0.00     0.00  timer_destroy
  0.00      0.89     0.00        1     0.00     0.00  timer_get_ms
  0.00      0.89     0.00        1     0.00     0.00  timer_get_s
  0.00      0.89     0.00        1     0.00     0.00  timer_init
  0.00      0.89     0.00        1     0.00     0.00  timer_start
  0.00      0.89     0.00        1     0.00     0.00  timer_stop
  0.00      0.89     0.00        1     0.00     0.00  verify_results
```

We can see that, as expected, no functions are inlined. Inside `knn_classify_instance`, `get_k_NN`, the function that calculates the distance of the test point to each of the train points, is the most time consuming. `select_k_nearest`, that does the partial sorting, is also non-negligible.

#### -O2

With -O2:

```
Time:  0.3973 s

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 91.43      0.32     0.32     1082   295.75   314.23  get_k_NN
  5.71      0.34     0.02     1082    18.48    18.48  select_k_nearest
  2.86      0.35     0.01     1082     9.24     9.24  minmax_normalize_point
  0.00      0.35     0.00     1082     0.00   314.23  knn_classifyinstance
  0.00      0.35     0.00     1082     0.00     0.00  plurality_voting
  0.00      0.35     0.00        1     0.00     0.00  minmax
  0.00      0.35     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.35     0.00        1     0.00     0.00  timer_destroy
  0.00      0.35     0.00        1     0.00     0.00  timer_get_s
  0.00      0.35     0.00        1     0.00     0.00  timer_init
  0.00      0.35     0.00        1     0.00     0.00  timer_start
  0.00      0.35     0.00        1     0.00     0.00  timer_stop
  0.00      0.35     0.00        1     0.00     0.00  verify_results
```

`get_k_NN` is now faster, while `select_k_nearest` stays the same. For some reason, `minmax_normalize_point` now runs in non-negligible time.

#### -03

```
Time:  0.3510 s

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
100.00      0.30     0.30     1082   277.26   277.26  get_k_NN
  0.00      0.30     0.00     1082     0.00   277.26  knn_classifyinstance
  0.00      0.30     0.00     1082     0.00     0.00  minmax_normalize_point
  0.00      0.30     0.00        1     0.00     0.00  minmax
  0.00      0.30     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.30     0.00        1     0.00     0.00  timer_destroy
  0.00      0.30     0.00        1     0.00     0.00  timer_get_s
  0.00      0.30     0.00        1     0.00     0.00  timer_init
  0.00      0.30     0.00        1     0.00     0.00  timer_start
  0.00      0.30     0.00        1     0.00     0.00  timer_stop
  0.00      0.30     0.00        1     0.00     0.00  verify_results
```

With the highest gcc optimization level, `select_k_nearest` and `plurality_voting` are inlined in `get_k_NN`, which makes sense, since they are small functions and should not increase the code size too much if copied to the caller, while reducing time in the function call preamble and return hazards.

As a whole, this is our best time yet, so we should optimize against this setting. Let's copy the original source code to `oldsrc` and start optimizing inside `src`.

## Optimizing via software fiddling techniques

### Removing unnecessary console traffic

Printing to stdout is slow and not very predictable, so let us remove the logs that `verify_results` and `main` and emit.

This reduces the time:

```
Time:  0.1995 s.

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
100.00      0.15     0.15     1082   138.63   138.63  get_k_NN
  0.00      0.15     0.00     1082     0.00   138.63  knn_classifyinstance
  0.00      0.15     0.00     1082     0.00     0.00  minmax_normalize_point
  0.00      0.15     0.00        1     0.00     0.00  minmax
  0.00      0.15     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.15     0.00        1     0.00     0.00  timer_destroy
  0.00      0.15     0.00        1     0.00     0.00  timer_get_s
  0.00      0.15     0.00        1     0.00     0.00  timer_init
  0.00      0.15     0.00        1     0.00     0.00  timer_start
  0.00      0.15     0.00        1     0.00     0.00  timer_stop
  0.00      0.15     0.00        1     0.00     0.00  verify_results
```

### Parallelizing with OpenMP (speedup: 2x)

Let us look at data parallelism opportunities inside our application. In main.c, we do, in a simplified way:

```c
	for (int i = 0; i < num_new_points; i++)
	{
        ...
        minmax_normalize_point(...);
        knn_classifyinstance(...);
    }
```

There are no data interdependencies between each point so we could try to assign each point to different cores. However, we will not be doing this since we are emulating real-time classification in a streaming environment, as stated by the comment the maintainers left in the code: `Note that depending on the application this can be instances arriving as streaming data. Here assume that the loop below needs to run in serial mode`.

However, the kNN algorithm does include computing distances to all points in the train dataset, which is "embarrassingly parallelizable". Let's add the `#pragma omp parallel for` directive in the loop inside `get_k_NN`.

```c
#pragma omp parallel for
    for (int i = 0; i < num_points; i++)
    {
        DATA_TYPE distance = 0;
        for (int j = 0; j < num_features; j++)
        {
            distance += ...;
        }
        ...
    }
```

This yields a speedup of about 2x in execution time.

```
Time:  0.0983 s

 %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 90.48      0.19     0.19                             generate_random_data
  9.52      0.21     0.02     1082    18.48    18.48  knn_classifyinstance
  0.00      0.21     0.00     1082     0.00     0.00  minmax_normalize_point
  0.00      0.21     0.00        1     0.00     0.00  minmax
  0.00      0.21     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.21     0.00        1     0.00     0.00  timer_destroy
  0.00      0.21     0.00        1     0.00     0.00  timer_get_s
  0.00      0.21     0.00        1     0.00     0.00  timer_init
  0.00      0.21     0.00        1     0.00     0.00  timer_start
  0.00      0.21     0.00        1     0.00     0.00  timer_stop
  0.00      0.21     0.00        1     0.00     0.00  verify_results
```

Let us try to parallelize the calculation of the overall distance based on the cumulative difference of features.

```c
#pragma omp parallel for
    for (int i = 0; i < num_points; i++)
    {
        DATA_TYPE distance = 0;
        #pragma omp parallel for reduction(+: distance)
        for (int j = 0; j < num_features; j++)
        {
            distance += ...;
        }
        ...
    }
```

Unfortunately, this results in a considerable slowdown, probably since we are spawning too many threads here.

```
Time:  2.2670 s

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  us/call  us/call  name    
 97.18      0.69     0.69                             generate_random_data
  1.41      0.70     0.01     1082     9.24     9.24  knn_classifyinstance
  1.41      0.71     0.01                             _init
  0.00      0.71     0.00     1082     0.00     0.00  minmax_normalize_point
  0.00      0.71     0.00        1     0.00     0.00  minmax
  0.00      0.71     0.00        1     0.00     0.00  minmax_normalize
  0.00      0.71     0.00        1     0.00     0.00  timer_destroy
  0.00      0.71     0.00        1     0.00     0.00  timer_get_s
  0.00      0.71     0.00        1     0.00     0.00  timer_init
  0.00      0.71     0.00        1     0.00     0.00  timer_start
  0.00      0.71     0.00        1     0.00     0.00  timer_stop
  0.00      0.71     0.00        1     0.00     0.00  verify_results
```

Let us scratch this by now and proceed with the speedup of 2x.

### Optimizing data structures locality

In our application, each point is a struct containing an array of features and its classification:

```c
typedef struct {
    DATA_TYPE features[NUM_FEATURES];
    CLASS_ID_TYPE classification_id;
} Point;
```

We then work with arrays of (train and test) Points througout the execution:

```c
Point known_points1[NUM_TRAINING_SAMPLES] = {
#include "train.dat"
}; //{{{1,2,3,4,5},'a'}};
Point *known_points = known_points1;

Point new_points1[NUM_TESTING_SAMPLES] = {
#include "test.dat"
}; //{{{1,2,3,4,5},'a'}};
Point *new_points = new_points1;
```

This means that in memory, data is placed like:

```
Point1_feature1
Point1_feature2
Point1_feature3
Point1_feature4
...
Point1_classification
Point2_feature1
Point2_feature2
Point2_feature3
Point2_feature4
...
Point2_classification
...
```

When calculating distances based on each feature sequentially, the CPU needs to load data from memory each time for each feature, since they are not contiguous on memory. Let's refactor this to increase cache locality.