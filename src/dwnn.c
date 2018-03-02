#include "dwnn.h"

#include <math.h>

#include <stdio.h>


LINALG_SCALAR _dwnn_weight(
        LINALG_SCALAR dist2,
        LINALG_SCALAR sigma2) {
    return exp(-dist2 / (2*sigma2));
}


int dwnn(
        vector * const *dataset,
        const LINALG_SCALAR *values,
        int n_points,
        LINALG_SCALAR sigma2,
        const vector *query,
        LINALG_SCALAR *out) {
    int i, err;
    LINALG_SCALAR dist2;
    LINALG_SCALAR w, total_w;
    LINALG_SCALAR res;

    total_w = 0;
    res = 0;
    for (i = 0; i < n_points; i++) {
        err = vec_dist2(dataset[i], query, &dist2);
        if (err != 0) {
            return err;
        }
        w = _dwnn_weight(dist2, sigma2);
        total_w += w;
        res += w * values[i];
        printf("%f\n", res);
    }
    res /= total_w;

    *out = res;
    return 0;
}
