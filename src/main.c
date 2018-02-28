#include "linalg/include/linalg.h"
#include "linalg/include/matrix.h"

int main(void) {
    LINALG_SCALAR ma[] = {
        1, 2, 3};
    matrix *a;

    mat_new(&a, ma, 1, 3);
    mat_del(a);

    return 0;
}
