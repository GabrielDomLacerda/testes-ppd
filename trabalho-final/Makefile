CPUCC     = gcc
MPICC     = mpicc
DEFS      = 
LIBDIR   =  -fopenmp
LIBS     =  -lm
LINK     =  $(LIBDIR) $(LIBS)
CPU_COMPILE = $(CPUCC) $(DEFS)
MPI_COMPILE = $(MPICC) $(DEFS)

seq: progdyn.c
	$(CPU_COMPILE) progdyn.c -o progdyn $(LINK)

openmp: omp_progdyn.c
	$(CPU_COMPILE) omp_progdyn.c -o omp_progdyn $(LINK)

mpi: mpi_progdyn.c
	$(MPI_COMPILE) mpi_progdyn.c -o mpi_progdyn $(LINK)

hybrid: hybrid.c
	$(MPI_COMPILE) hybrid.c -o hybrid $(LINK)

all: seq openmp mpi hybrid

clean:
	rm -rf progdyn omp_progdyn mpi_progdyn hybrid
