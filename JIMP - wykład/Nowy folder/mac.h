#include <stdio.h>

typedef struct {
    int w, k;
    double *e;
} mac_t;

mac_t *czytaj (FILE *f);

void pisz (mac_t m, FILE *f);