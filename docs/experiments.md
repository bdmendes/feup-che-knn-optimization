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

