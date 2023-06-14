#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

int parallel_knapsack_dyn(int capacity, int *weights, int *values, int n)
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
#pragma omp parallel for
        for (w = 1; w <= capacity; w++)
        {
            matriz[i][w] = max(values[i - 1] + matriz[i - 1][w - weights[i - 1]],
                               matriz[i - 1][w]) *
                               (weights[i - 1] <= w) +
                           matriz[i - 1][w] * (!(weights[i - 1] <= w));
        }
    }

    return matriz[n][capacity];
}

void read_values(FILE *file, int *weights, int *values, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d %d", &weights[i], &values[i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc <= 1)
        return 1;
    FILE *file = fopen(argv[1], "r");
    int i, n, W;
    fscanf(file, "%d %d", &n, &W);
    int weights[n], values[n];
    read_values(file, weights, values, n);

    printf("BEST KNAPSACK: %d\n", parallel_knapsack_dyn(W, weights, values, n));

    return 0;
}
