for counter in $(seq 0 $1); do
    echo "-------$counter------"
    ./comando.sh 1e-$counter
    echo "---------------------"
done