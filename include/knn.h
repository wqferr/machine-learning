#ifndef KNN_H
#define KNN_H 1

#include "linalg/include/vector.h"

/*
 * Given the array of vectors dataset, find the class that better
 * represents the point query given its k nearest neighbors.
 */
int knn(
        vector * const *dataset,
        const int *classes,
        int n_points,
        int k,
        const vector *query,
        int *out);

#endif
