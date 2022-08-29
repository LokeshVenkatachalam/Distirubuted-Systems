#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
int main(int argc,char **argv ){
    
    // Declaring Variables
    long double Input[2];
    long double ans=0,sum=0;
    int myid, numprocs;
    int done = 0;
    int i=1;
    long double term=1;

    
    MPI_Init(&argc,&argv);  // Intializing  MPI

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); //Finding the number of process
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);     //Finding the id of process

    if(myid==0){
        freopen(argv[1], "r", stdin);   // Opening input file
        scanf("%Lf %Lf",&Input[0],&Input[1]); // Inputing X and precission
        fclose(stdin);
    }

	MPI_Bcast(Input, 2, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD); // Broadcasting the input
    
    while(true){

        term = (term/((long double)i))*Input[0];  // Dividing before multiplication to prevent overflow

        if(term < (Input[1]/((long double)1000))) // Dividing the Precission by 1000 to inmprove the precission
            break;
        
        if(i%2 == 1){ // Checking whether it is odd term

            if((i/2)%numprocs == myid){  // Finding the processid to be included in

                // Deciding the +ve or -ve and adding to required sum
                if(i%4 == 1)
                    ans = ans + term;
                else if(i%4 == 3)
                    ans = ans - term;
            }
        }

        i++;
    }
    
    // adding the sum of terms accross the process
    MPI_Reduce(&ans, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);

    //Outputing the answer
    if (myid == 0){
        freopen(argv[2], "w", stdout);   // Opening output file

	    printf("Sin(%0.12Lf) is approximately = %.12Lf\n",
		   Input[0],sum);                     // Outputing the answer

        fclose(stdout);                       // Closing output.txt
	}
    
    MPI_Finalize(); // Ending MPI

    return 0;
}