#include <stdio.h>

#include "linalg/include/linalg.h"
#include "linalg/include/matrix.h"
#include "knn.h"


#define N 6

int main(void) {
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
