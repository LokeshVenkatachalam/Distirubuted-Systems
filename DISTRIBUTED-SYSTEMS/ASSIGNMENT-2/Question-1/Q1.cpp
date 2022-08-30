#include <stdio.h>
#include <math.h>
#include <vector>
#include "mpi.h"
int main(int argc,char **argv ){

    // Declaring Variables
    int myid, numprocs;
    int n,size;
    double x;
    std::vector<double> tempRow;
    std::vector<double> tempRowAns;
    std::vector<int> chosen;

    MPI_Init(&argc,&argv);  // Intializing  MPI

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); //Finding the number of process
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);     //Finding the id of process

    freopen(argv[1], "r", stdin);   // Opening input file

    scanf("%d",&n);                 // Inputing n-> No of Rows,columns;
    size = n/numprocs;              // Finding Maximum no of rows to be stored in a array
    if(n%numprocs != 0)
        size++;

    
    tempRow.resize(n);                    // Resizing the tempRow array
    tempRowAns.resize(n);                 // Resizing the tempAnsRow array
    chosen.resize(n);                     // Resizing the chosen array                           
    std::vector<double> Matrix[n+1];      // Declaring the Matrix array for input matrix
    std::vector<double> AnsMatrix[n+1];   // Declaring the AnsMatrix array for output matrix

    // Intialzing chosen vector
    for(int i = 0; i < n; i++)
        chosen[i] = 0;

    // Storing the input as rows in different process
    for(int i = 1; i <= n; i++){

        for(int j = 1; j<=n; j++){
            scanf("%lf", &x);        // Inputing matrix[i][j]

            //Checking and pushing into the row
            if(((i-1)/size) == myid){
                Matrix[i].push_back(x);    // Pushing into Matrix
                //Pushing 0.0 and 1.0->(i,i) into AnsMatrix
                if(i!=j)
                    AnsMatrix[i].push_back(0.0);
                else
                    AnsMatrix[i].push_back(1.0);
            }

        }
    }
    fclose(stdin);

    int pivot;
    double scaling;
    double elimination_Scaling;
    for(int i = 1; i <= n; i++){
        // Identifying the process
        if(((i-1)/size) == myid){
            // Finding the pivot -> First non-zero element, whose column is not chosen yet
            for(int j = 0;j < n; j++){
                if(Matrix[i][j] !=0 && chosen[j] == 0){
                    pivot = j;
                    scaling = double(1)/Matrix[i][j];
                    chosen[j] = i;
                    break;
                }
            }
            //Scaling down
            for(int j = 0;j < n; j++){
                tempRow[j]      = Matrix[i][j]*scaling;
                Matrix[i][j]    = Matrix[i][j]*scaling;
                tempRowAns[j]= AnsMatrix[i][j]*scaling;
                AnsMatrix[i][j] = AnsMatrix[i][j]*scaling;
            }
            
        }

        MPI_Bcast(&tempRow[0],    n, MPI_DOUBLE, (int) ((i-1)/size), MPI_COMM_WORLD); // Broadcasting the tempRow
        MPI_Bcast(&tempRowAns[0], n, MPI_DOUBLE, (int) ((i-1)/size), MPI_COMM_WORLD); // Broadcasting the tempRowAna
        MPI_Bcast(&chosen[0],     n, MPI_INT, (int) ((i-1)/size), MPI_COMM_WORLD); // Broadcasting the chosen
        MPI_Bcast(&pivot,     1,  MPI_INT,    (int) ((i-1)/size), MPI_COMM_WORLD); // Broadcasting pivot

        for(int j = 1; j <= n; j++){

            if(((j-1)/size) == myid && j != chosen[pivot]){

                // Find the elimination scaling
                elimination_Scaling = Matrix[j][pivot]/tempRow[pivot];
                // Elimination
                for(int k = 0; k < n; k++){
                    Matrix[j][k]    = Matrix[j][k]-tempRow[k]*elimination_Scaling;
                    AnsMatrix[j][k] = AnsMatrix[j][k]- tempRowAns[k]*elimination_Scaling;
                }
            }
        }
        MPI_Barrier( MPI_COMM_WORLD ); // Sync all process before elimination
    }


    // Print the output after swapping
    for(int i = 1; i <= n; i++){
        // Finding which row should come as i^th row and its process id
        if(myid == (chosen[i-1]-1)/size){ // chosen[i-1]^th row should be i^th row for Matrix to become identity in the end.
            // Printing

            for(int j = 0; j < n; j++){
                printf("%.8lf",AnsMatrix[chosen[i-1]][j]); // Printing A^(-1)[i,j]
                fflush(stdin);
                if(j != n-1){
                    printf(" ");   // Spacing
                    fflush(stdin);
                }
                    
            }
            if(i != n){
                printf("\n");
                fflush(stdin);    // line ending
            }
        }
        MPI_Barrier( MPI_COMM_WORLD ); // Sync all process before printing next line
    }
    MPI_Finalize(); // Ending MPI
    return 0;
}