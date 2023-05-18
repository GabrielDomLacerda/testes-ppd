echo $1
echo "-----------NORMAL------------"
time ./integracao $1 >> teste.txt
echo "------------PTHREAD-----------"
time ./integracao_p $1 >> teste.txt
echo "------------OPENMP-----------"
time ./integracao_omp $1 >> teste.txt