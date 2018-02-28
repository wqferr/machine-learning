#ifndef KMEANS_H
#define KMEANS_H 1

#include <stdbool.h>

#include "linalg/include/vector.h"

typedef struct kmeans_data kmeans_data;


int kmeans_init(
        kmeans_data **kmeans,
        vector * const *dataset,
        int n_points,
        int n_clusters,
        LINALG_SCALAR threshold);
int kmeans_free(kmeans_data *kmeans);

int kmeans_n_clusters(kmeans_data *kmeans, int *n_clusters);
int kmeans_centers(kmeans_data *kmeans, vector ***centers);
int kmeans_associated_centers(kmeans_data *kmeans, int **assoc);


#endif
