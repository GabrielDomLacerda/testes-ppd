/*
 * Esse exercício resolve a integra x^2 no intervalo [0:1], ou seja,
 * o valor exato é de 1/
 * O valor de h é passado como parâmetro (h=b-a/n, sendo a e b os limites da integração e n subintervalos)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x) { return (double)x * x; }

int main(int ac, char **av)
{
  double h = atof(av[1]),
         k = h / 2,
         x = 0.0,
         sum = 0.0;

  unsigned int steps = (unsigned int)1.0 / h;
  if (steps % 10 != 0)
    steps++;

  fprintf(stdout, "\nIntegração de uma função f(x)\n");
  fprintf(stdout, "Qtde. de trapézios: %u - valor do h = %15.10lf\n", steps, h);
  for (unsigned int i = 0; i <= steps; i++)
  {
    double offset = h * (double)i;
    double aux = 2.0 * k;
    if ((i == 0) || (i == steps))
      aux = k;
    sum += (func(x + offset) * aux);
  }

  fprintf(stdout, "resultado: I = %15.10lf\n", sum);

  return EXIT_SUCCESS;
}
