#include "kmeans.h"

#include <math.h>
#include <stdlib.h>

#include "util.h"

struct kmeans_data {
    int n_clusters;
    vector **centers;
    int *associated_centers;
};


int kmeans_init(
        kmeans_data **out,
        vector * const *dataset,
        int n_points,
        int n_clusters,
        LINALG_SCALAR threshold) {
    int err;
    int i, j, n, dim;
    int best;
    LINALG_SCALAR center_div;
    LINALG_SCALAR divergence;
    int *closest;
    vector *zero;
    vector *next_center;
    const vector *point;
    const vector **point_sample;
    vector **centers;
    LINALG_SCALAR *distances;
    kmeans_data *kmeans;

    centers = malloc(n_clusters * sizeof(*centers));
    distances = malloc(n_clusters * sizeof(*distances));
    closest = malloc(n_points * sizeof(*closest));
    point_sample = malloc(n_clusters * sizeof(*point_sample));

    sample(dataset, n_points, sizeof(*dataset), n_clusters, point_sample);
    for (i = 0; i < n_clusters; i++) {
        vec_dup(&centers[i], point_sample[i]);
    }
    free(point_sample);

    vec_dim(dataset[0], &dim);
    vec_zero(&zero, dim);
    vec_zero(&next_center, dim);

    do {
        divergence = 0;
        for (i = 0; i < n_points; i++) {
            point = dataset[i];
            best = 0;

            for (j = 0; j < n_clusters; j++) {
                err = vec_dist(point, centers[j], &distances[j]);
                if (err != 0) {
                    free(centers);
                    free(distances);
                    free(closest);
                    return err;
                }
                if (distances[j] < distances[best]) {
                    best = j;
                }
            }
            closest[i] = best;
        }

        for (i = 0; i < n_clusters; i++) {
            n = 0;
            vec_cpy(next_center, zero);
            for (j = 0; j < n_points; j++) {
                if (closest[j] == i) {
                    vec_add_(next_center, dataset[j]);
                    n++;
                }
            }
            vec_sdiv_(next_center, n);

            vec_dist2(centers[i], next_center, &center_div);
            vec_cpy(centers[i], next_center);
            divergence += center_div;
        }
        divergence = sqrt(divergence);
    } while (divergence > threshold);

    vec_del(zero);
    vec_del(next_center);

    kmeans = malloc(sizeof(*kmeans));

    kmeans->n_clusters = n_clusters;
    kmeans->centers = centers;
    kmeans->associated_centers = closest;

    free(distances);

    *out = kmeans;
    return 0;
}


int kmeans_free(kmeans_data *kmeans) {
    int i;
    free(kmeans->associated_centers);
    for (i = 0; i < kmeans->n_clusters; i++) {
        vec_del(kmeans->centers[i]);
    }
    free(kmeans->centers);
    free(kmeans);

    return 0;
}


int kmeans_n_clusters(kmeans_data *kmeans, int *out) {
    *out = kmeans->n_clusters;
    return 0;
}


int kmeans_centers(kmeans_data *kmeans, vector ***centers) {
    *centers = kmeans->centers;
    return 0;
}


int kmeans_associated_centers(kmeans_data *kmeans, int **assoc) {
    *assoc = kmeans->associated_centers;
    return 0;
}
