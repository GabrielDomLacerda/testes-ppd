#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

int *knapsack_brute(int n, int w[], int c)
{
    int i;
    int iadd, primeiro, ncard;
    int *s, *s_test;
    int t, t_test;

    s = (int *)malloc(n * sizeof(int));
    s_test = (int *)malloc(n * sizeof(int));

    primeiro = 1;
    ncard = 0;

    for (i = 0; i < n; i++)
    {
        s_test[i] = 0;
        s[i] = s_test[i];
    }

    t_test = 0;
    t = 0;

    while (1)
    {
        gerar_subconjuntos(n, s_test, &primeiro, &ncard, &iadd);
        t_test = 0;
        for (i = 0; i < n; i++)
        {
            t_test = t_test + s_test[i] * w[i];
        }

        if (t < t_test && t_test <= c)
        {
            t = t_test;
            for (i = 0; i < n; i++)
            {
                s[i] = s_test[i];
            }
        }

        if (primeiro)
            break;
    }

    free(s_test);

    return s;
}

void gerar_subconjuntos(int n, int *subconj, int *primeiro, int *ncard, int *iadd)
{
    int i;
    if (*(primeiro))
    {
        for (i = 0; i < n; i++)
            subconj[i] = 0;
        *iadd = 0;
        *ncard = 0;
        *primeiro = 0;
    }
    else
    {
        *iadd = 1;

        if ((*ncard % 2) != 0)
        {
            while (1)
            {
                *iadd = *iadd + 1;
                if (subconj[*iadd - 2] != 0)
                {
                    break;
                }
            }
        }

        subconj[*iadd - 1] = 1 - subconj[*iadd - 1];
        *ncard = *ncard + 2 * subconj[*iadd - 1] - 1;
        if (*ncard == subconj[n - 1])
            *primeiro = 0;
    }
}