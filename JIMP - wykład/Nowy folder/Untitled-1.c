#include "mac.h"

mac_t *czytaj (FILE *f)
{
    mac_t *m = malloc (sizeof *m);
    if (m == NULL)
        return NULL;
    if (fscanf (f, "%d %d", m->w, m->k) != 2)
    {
        free (m);
        return NULL;
    }
    if (m->e = malloc (m->w * m->k * sizeof (*(m->e))))
    {
        free (m);
        return NULL;
    }
    int i;
    for (i = 0; i < m->w * m->k; ++i)
        if (fscanf (f, "%lf", m->e+i) != 1)
        {
            free (m->e);
            return NULL;
        }
    
}

void pisz (mac_t *m, FILE *f)
{
    fprintf (f, "%d %d\n", m->w, m->k);
    int i;
    for (i = 0; i < m->w; ++i)
    {
        for (j = 0; j < m->w; ++j)
            fprintf (f, " %lf", *(m->e+i*m->k+j));
        fprintf (f, "\n");
    }
}