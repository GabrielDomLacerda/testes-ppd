#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

int knapsack_dyn(int capacity, int *weights, int *values, int n)
{
    int i, w;
    int **matriz = (int **)malloc(sizeof(int *) * (n + 1));
    for (i = 0; i < (n + 1); i++)
    {
        matriz[i] = (int *)malloc(sizeof(int) * (capacity + 1));
        for (w = 0; w < (capacity + 1); w++)
        {
            matriz[i][w] = 0;
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (w = 1; w <= capacity; w++)
        {
            matriz[i][w] = max(values[i - 1] + matriz[i - 1][w - weights[i - 1]], matriz[i - 1][w]) * (weights[i - 1] <= w) + matriz[i - 1][w] * (!(weights[i - 1] <= w));
        }
    }

    return matriz[n][capacity];
}
