#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "linalg/include/linalg.h"
#include "linalg/include/matrix.h"
#include "knn.h"
#include "kmeans.h"

#define N 6

int knn_main(void);
int kmeans_main(void);
void vec_print(const vector *v);


int main(void) {
    return kmeans_main();
}


int knn_main(void) {
    int i;

    LINALG_SCALAR md[N][2] = {
        {0.1, 1.02},
        {-0.2, 0.98},
        {0, 1.2},
        {0.9, 0.15},
        {1.12, -0.01},
        {1, -0.2}};
    int classes[N] = {
        0, 0, 0, 1, 1, 1};
    LINALG_SCALAR mq[2] = {
        0, 1};
    vector *dataset[N];
    vector *query;
    int k = 3;
    int cls;
    int err;

    for (i = 0; i < N; i++) {
        vec_new(&dataset[i], md[i], 2);
    }
    vec_new(&query, mq, 2);

    err = knn(
            dataset, classes, N,
            k, query, &cls);

    if (err != 0) {
        printf("error code: %d\n", err);
    } else {
        printf("class: %d\n", cls);
    }

    for (i = 0; i < N; i++) {
        vec_del(dataset[i]);
    }
    vec_del(query);

    return 0;
}


int kmeans_main(void) {
    int i;
    int err;
    int n_clusters = 2;
    LINALG_SCALAR md[N][2] = {
        {0.1, 1.02},
        {-0.2, 0.98},
        {0, 1.2},
        {0.9, 0.15},
        {1.12, -0.01},
        {1, -0.2}};
    vector *dataset[N];
    vector **centers;
    int *assoc;
    kmeans_data *kmeans;

    srand(time(NULL));

    for (i = 0; i < N; i++) {
        vec_new(&dataset[i], md[i], 2);
    }

    err = kmeans_init(
            &kmeans,
            dataset,
            N,
            n_clusters,
            1e-3);
    if (err != 0) {
        printf("Error code: %d\n", err);
    } else {
        kmeans_centers(kmeans, &centers);
        kmeans_associated_centers(kmeans, &assoc);

        printf("Centers:\n");
        for (i = 0; i < n_clusters; i++) {
            printf("%d\t", i);
            vec_print(centers[i]);
            printf("\n");
        }
        printf("==========\n");
        printf("Points:\n");
        for (i = 0; i < N; i++) {
            printf("%d:\t", i);
            vec_print(dataset[i]);
            printf("\n\tCenter: %d\n", assoc[i]);
        }
    }

    for (i = 0; i < N; i++) {
        vec_del(dataset[i]);
    }
    kmeans_free(kmeans);

    return 0;
}



void vec_print(const vector *v) {
    int i, dim;

    vec_dim(v, &dim);
    for (i = 0; i < dim; i++) {
        printf("%.3f\t", vec_get(v, i));
    }
}
