#!/bin/bash
#SBATCH -N 1
#SBATCH -n 8
#SBATCH --mem-per-cpu=1024
#load the module on the node
module load hpcx-2.7.0/hpcx-ompi
#run the executable
#mpirun --use-hwthread-cpus a.out > out
mpirun --use-hwthread-cpus a.out > findingPi_output.txt