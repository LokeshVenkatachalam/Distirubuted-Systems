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

    std::vector<std::vector<int>> Edge  (n,std::vector<int>(n,0)); // Adjacency Matrix
    std::vector<std::vector<int>> Sum   (n,std::vector<int>(n,0)); // Count of common neighbours to vertex i,j in the given process
    std::vector<std::vector<int>> Count (n,std::vector<int>(n,0)); // Sum of counts of common neighbours across process
    // Inputing the graph as adjacency matrix 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&Edge[i][j]);
        }
    }
    // Finding the count[i][j]-> no of common neighbours to both i,j in the submatrix given to a process
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
        int triangles = 0;                              // No of triangles                 
        int quadrilateral = 0;                          // No of quadrilateral

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                /*
                # if i->j edge exists , then we can form a triangle with a neighbour of i,j
                # Sum[i][j] gives no of common neighbour of i,j
                # It implies no of triangles containing edge i,j is = Sum[i][j]
                */
                if(Edge[i][j] == 1)
                    triangles += Sum[i][j];
                /*
                # Every pair of common neigbour to i,j can form a cycle of length 4 with vertices i,j
                # Sum[i][j] gives no of common neighbour of i,j
                # It implies no of cycles of length 4,containing vertex i,j is = (Sum[i][j]*(Sum[i][j]-))/2
                */
                quadrilateral += (Sum[i][j]*(Sum[i][j]-1))/2;
            }
        }
        triangles = triangles/3;                // Every triangles is counted as part of every edge,so by 3
        quadrilateral = quadrilateral/2;        // Every cycle of length 4 is counted as part opposite pair of vertices, so by 2

        freopen(argv[2], "w", stdout);                              // Opening output file
	    printf("No of triangles is %d \n",triangles);               // Outputing the answer
        printf("No of cycles of length 4 is %d \n",quadrilateral);  // Output No of cycles of length 4
        fclose(stdout);                                             // Closing output.txt
    }
    MPI_Finalize();
    return 0;
}