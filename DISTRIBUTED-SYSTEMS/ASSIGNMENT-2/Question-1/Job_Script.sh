#!/bin/bash
#SBATCH -N 1
#SBATCH -n 8  
#SBATCH --mem-per-cpu=1024
#load the module on the node
module load hpcx-2.7.0/hpcx-ompi
#Compile Q1.cpp
mpic++ Q1.cpp
#Run the excutable using two arguments `input_filename` `output_filename`
time mpirun --use-hwthread-cpus a.out input_1.txt > output_1_8.txt
