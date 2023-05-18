/*
 * Esse exercício resolve a integra x^2 no intervalo [0:1], ou seja,
 * o valor exato é de 1/
 * O valor de h é passado como parâmetro (h=b-a/n, sendo a e b os limites da integração e n subintervalos)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX_THREADS 12

typedef struct
{
  int ini;
  int fim;
  double h;
  double *sum;
  pthread_mutex_t *sem;
} PARAMS;

PARAMS *criar_params(int ini,
                     int fim,
                     double h,
                     double *sum,
                     pthread_mutex_t *sem)
{
  PARAMS *params = malloc(sizeof(*params));
  params->ini = ini;
  params->fim = fim;
  params->h = h;
  params->sum = sum;
  params->sem = sem;
}

double func(double x) { return (double)x * x; }

void *calcular(void *args)
{
  PARAMS *params = (PARAMS *)args;
  double h = params->h,
         k = h / 2.0,
         x = 0.0,
         local_sum = 0.0;

  unsigned int steps = (unsigned int)1.0 / h;
  if (steps % 10 != 0)
    steps++;

  for (unsigned int i = params->ini; i <= params->fim; i++)
  {
    double offset = h * (double)i;
    double aux = 2.0 * k;
    if ((i == 0) || (i == steps))
      aux = k;
    local_sum += (func(x + offset) * aux);
  }
  pthread_mutex_lock(params->sem);
  *(params->sum) += local_sum;
  pthread_mutex_unlock(params->sem);

  free(params);

  return NULL;
}

int main(int ac, char **av)
{
  pthread_t threads[MAX_THREADS];

  pthread_mutex_t sem;
  pthread_mutex_init(&sem, NULL);

  double h = atof(av[1]),
         k = h / 2,
         x = 0.0,
         sum = 0.0,
         ini = 0.0,
         fim;

  unsigned int steps = (unsigned int)1.0 / h;
  if (steps % 10 != 0)
    steps++;
  int chunk_size = ceil(steps / (double)MAX_THREADS);

  fprintf(stdout, "\nIntegração de uma função f(x)\n");
  fprintf(stdout, "Qtde. de trapézios: %u - valor do h = %15.10lf\n", steps, h);

  int num_threads = 0;
  for (int i = 0; i < MAX_THREADS; i++)
  {
    fim = ini + chunk_size;
    if (fim > steps)
      fim = steps;

    PARAMS *params = criar_params(ini, fim, h, &sum, &sem);

    pthread_create(&threads[i], NULL, &calcular, params);
    num_threads++;

    ini += chunk_size + 1;

    if (fim >= steps)
      break;
  }

  for (int i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }

  fprintf(stdout, "resultado: I = %15.10lf\n", sum);

  return EXIT_SUCCESS;
}
