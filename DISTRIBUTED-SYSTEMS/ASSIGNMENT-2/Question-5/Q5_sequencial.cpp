#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
int main(int argc,char **argv){

    // Declaring Variables
    int n;

    freopen(argv[1], "r", stdin);   // Opening input file

    scanf("%d",&n);                 // Inputing n-> No of Rows,columns;

    std::vector<std::vector<int>> Edge  (n,std::vector<int>(n,0)); // Adjacency Matrix
    std::vector<std::vector<int>> Sum (n,std::vector<int>(n,0)); // Sum of counts of common neighbours across process
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&Edge[i][j]);
        }
    }
    // Finding the Sum[i][j]-> no of common neighbours to both i,j
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(Edge[i][j] == 0) continue;
            for(int k = j+1; k < n; k++){
                if( Edge[i][k] == 1)
                    Sum[j][k]++;
            }
        }
    }

    int triangles = 0;                            // No of triangles
    int quadrilateral = 0;                        // No of quadrilateral


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
	printf("No of triangles is %d \n",triangles);               // Outputing No of triangles
    printf("No of cycles of length 4 is %d \n",quadrilateral);  // Output No of cycles of length 4
    fclose(stdout);                                             // Closing output.txt
    return 0;
}