# Notes

## Basics

- IIIT LAN/VPN required
- ssh and login with one of these extensions
    - $`username@rce`
    - $`username@rce.iiit.ac.in`
    - $`username@10.4.25.10`



### Loading Packages [rce.iiit.ac.in]

- $ `module avail`
```
$ module avail
------------------------------------- /usr/share/Modules/modulefiles-------------------------------------
cmake/3.20.3           go/1.17                     java/17.0.1                           
cuda/10.1              hdfs/hdfs                   kafka/2.8                             
cuda/10.2              hpcx-2.7.0/hpcx             maven/3.8.1                           
cuda/11.0              hpcx-2.7.0/hpcx-debug       module-git                            
cuda/11.2              hpcx-2.7.0/hpcx-debug-ompi  module-info                           
cudnn/7.6.5-cuda-10.1  hpcx-2.7.0/hpcx-mt          modules                               
cudnn/8.1.0-cuda-10.2  hpcx-2.7.0/hpcx-mt-ompi     node-blockchain/16.14.0               
cudnn/8.1.0-cuda-11.0  hpcx-2.7.0/hpcx-ompi        null                                  
cudnn/8.1.0-cuda-11.2  hpcx-2.7.0/hpcx-prof        spark/3.0.1-hadoop-3.2                
dot                    hpcx-2.7.0/hpcx-prof-ompi   TensorRT/7.2.2.3-cuda-11.2-cudnn-8.1  
ffmpeg/4.3.2           hpcx-2.7.0/hpcx-stack       TensorRT/7.2.3.4-cuda-11.0-cudnn-8.1  
geomesa/geomesa        java/11.0.13                use.own 
```
- $`module load hpcx-2.7.0/hpcx-ompi`

### Compiling

- $`mpicc helloWorld.cpp`
    - Use `mpicc filename.cpp` to compile files with mpi headers

### Running a batch script

- $`sbatch Job_Script.sh`
```
$ sbatch Job_Script.sh 
Submitted batch job 1797
```
- Job_Script.sh
```sh
#!/bin/bash
#SBATCH -N 1
#SBATCH -n 8
#SBATCH --mem-per-cpu=1024
#load the module on the node
module load hpcx-2.7.0/hpcx-ompi
#run the executable
#mpirun --use-hwthread-cpus a.out > out
mpirun --use-hwthread-cpus a.out > out
```
