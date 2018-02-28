#include "knn.h"

#include <stdlib.h>

#include "linalg/include/vector.h"


struct _knn_pair {
    int cls;
    LINALG_SCALAR dist;
};


int _knn_pair_cmp(const void *p1, const void *p2) {
    LINALG_SCALAR d1 = ((const struct _knn_pair *) p1)->dist;
    LINALG_SCALAR d2 = ((const struct _knn_pair *) p2)->dist;

    if (d1 < d2) {
        return -1;
    }
    if (d1 > d2) {
        return 1;
    }
    return 0;
}


int knn(
        vector * const *dataset,
        const int *classes,
        int n_points,
        int k,
        const vector *query,
        int *out) {
    int i;
    int max_class_idx;
    int err;
    int best_class_count;
    int cls;
    int *class_count;
    struct _knn_pair *distances;

    distances = malloc(n_points * sizeof(*distances));
    max_class_idx = -1;
    for (i = 0; i < n_points; i++) {
        distances[i].cls = classes[i];
        err = vec_dist(query, dataset[i], &distances[i].dist);
        if (err != 0) {
            free(distances);
            return err;
        }

        /* Used for counting later */
        if (classes[i] > max_class_idx) {
            max_class_idx = classes[i];
        }
    }

    qsort(distances, n_points, sizeof(*distances), &_knn_pair_cmp);

    class_count = calloc(max_class_idx+1, sizeof(*class_count));
    for (i = 0; i < k; i++) {
        cls = distances[i].cls;
        class_count[cls]++;
    }

    best_class_count = 0;
    for (i = 1; i <= max_class_idx; i++) {
        if (class_count[i] > class_count[best_class_count]) {
            best_class_count = i;
        }
    }

    free(distances);
    free(class_count);

    *out = best_class_count;
    return 0;
}

