#include <stdio.h>
#include <stdlib.h>

double *func (int )

int main (int argc, char **argv)
{
    double *wynik = func(atoi(*argv++), atoi(*argv++), atoi(*argv));
    int x;
    for (int x = 0; x < *argv; ++x)
        printf ("%f\t", wynik[x]);
    return 0;
}