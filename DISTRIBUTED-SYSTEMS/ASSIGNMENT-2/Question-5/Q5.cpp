#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include "mpi.h"
int main(int argc,char **argv ){
    
    // Declaring Variables
    int myid, numprocs;
    int n,size;
    
    MPI_Init(&argc,&argv);  // Intializing  MPI

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); //Finding the number of process
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);     //Finding the id of process

    freopen(argv[1], "r", stdin);   // Opening input file

    scanf("%d",&n);                 // Inputing n-> No of Rows,columns;

    size = n/numprocs;              // Finding Maximum no of rows to be stored in a array
    if(n%numprocs != 0)
        size++;

    std::vector<std::vector<int>> Edge  (n,std::vector<int>(n,0));
    std::vector<std::vector<int>> Sum   (n,std::vector<int>(n,0));
    std::vector<std::vector<int>> Count (n,std::vector<int>(n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&Edge[i][j]);
        }
    }
    for(int i = myid*(size); i < std::min(n,((myid+1)*(size))); i++){
        for(int j = 0; j < n; j++){
            if(Edge[i][j] == 0) continue;
            for(int k = j+1; k < n; k++){
                if( Edge[i][k] == 1)
                    Count[j][k]++;
            }
        }
    }
    
    for(int i=0;i<n;i++){
        MPI_Reduce(&Count[i][0], &Sum[i][0],n, MPI_INT, MPI_SUM, 0,
		           MPI_COMM_WORLD);
    }
    
    if(myid == 0){
        int triangles = 0;
        int quadrilateral = 0;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if(Edge[i][j] == 1)
                    triangles += Sum[i][j];
                quadrilateral += (Sum[i][j]*(Sum[i][j]-1))/2;
            }
        }
        triangles = triangles/3;
        quadrilateral = quadrilateral/2;

        freopen(argv[2], "w", stdout);                 // Opening output file

	    printf("No of triangles is %d \n",triangles); // Outputing the answer
        printf("No of cycles of length 4 is %d \n",quadrilateral);
        fclose(stdout);                                // Closing output.txt
    }
    MPI_Finalize();
}