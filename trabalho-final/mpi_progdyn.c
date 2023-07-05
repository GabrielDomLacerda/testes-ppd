#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int max(int a, int b)
{
    return a >= b ? a : b;
}

int knapsack_dyn(int capacity, int *weights, int *values, int n)
{
    MPI_Init(NULL, NULL);
    int rank, size;

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

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Send(matriz[0], capacity + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    for (i = 1; i < n; i++)
    {
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Recv(matriz[i - 1], capacity + 1, MPI_INT, (rank - 1) % size, i - 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (w = 1; w <= capacity; w++)
        {
            matriz[i][w] = max(values[i - 1] + matriz[i - 1][w - weights[i - 1]],
                               matriz[i - 1][w]) *
                               (weights[i - 1] <= w) +
                           matriz[i - 1][w] * (!(weights[i - 1] <= w));
            printf("%d ", matriz[i][w]);
        }
        printf("\n");
        MPI_Send(matriz[i], capacity + 1, MPI_INT, rank % size, i, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Recv(matriz[n], capacity + 1, MPI_INT, size - 1, n, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Finalize();
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

    int result = knapsack_dyn(W, weights, values, n);

    printf("BEST KNAPSACK: %d\n", result);

    return 0;
}
