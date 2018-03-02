#ifndef DWNN_H
#define DWNN_H 1

#include "linalg/include/linalg.h"
#include "linalg/include/vector.h"

int dwnn(
        vector * const *dataset,
        const LINALG_SCALAR *values,
        int n_points,
        LINALG_SCALAR sigma2,
        const vector *query,
        LINALG_SCALAR *out);

#endif
