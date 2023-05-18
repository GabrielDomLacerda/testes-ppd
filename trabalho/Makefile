CPUCC     = gcc
DEFS      = 
LIBDIR   =  -fopenmp
LIBS     =  -lm
LINK     =  $(LIBDIR) $(LIBS)
CPU_COMPILE = $(CPUCC) $(DEFS)

normal: integracao.c
	$(CPU_COMPILE) integracao.c -o integracao $(LINK)

pthread: integracao_p.c
	$(CPU_COMPILE) integracao_p.c -o integracao_p $(LINK)

openmp: integracao_omp.c
	$(CPU_COMPILE) integracao_omp.c -o integracao_omp $(LINK)

all: normal pthread openmp

clean:
	rm -rf integracao integracao_p integracao_omp
