#include "util.h"

#include <stdlib.h>
#include <string.h>

int sample(
        const void *data,
        int elm_count,
        int elm_size,
        int sample_size,
        void *out) {
    int i, r;

    memcpy(out, data, sample_size * elm_size);
    for (i = sample_size; i < elm_count; i++) {
        r = rand() % i;
        if (r < sample_size) {
            memcpy(out + r*elm_size, data + i*elm_size, elm_size);
        }
    }
    return 0;
}
