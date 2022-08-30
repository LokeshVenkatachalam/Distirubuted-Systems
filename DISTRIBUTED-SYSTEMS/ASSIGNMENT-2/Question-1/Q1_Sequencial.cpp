#include <stdio.h>
#include <math.h>
#include <vector>
int main(int argc,char **argv ){

    freopen(argv[1], "r", stdin);        // Opening input file
    int n;                               // n-> No of rows , columns
    scanf("%d",&n);                      // Input n
    std::vector<double> Matrix[n];       // Input matrix
    std::vector<double> AnsMatrix[n]; // Ans Matrix
    std::vector<int> chosen(n,0);        // Chosen List
    int pivot;
    double scaling;
    double elimination_Scaling;
    double temp;

    // Inputing the matrix
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++){
            scanf("%lf",&temp);
            Matrix[i].push_back(temp);
            if(i==j) AnsMatrix[i].push_back(1.0);
            else     AnsMatrix[i].push_back(0.0);
        }

    fclose(stdin);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(Matrix[i][j] != 0 && chosen[j] == 0){
                chosen[j] = i;
                pivot = j;
                break;
            }
        }
        scaling = double(1)/Matrix[i][pivot];
        for(int j = 0; j < n; j++){
            Matrix[i][j] = Matrix[i][j]*scaling;
            AnsMatrix[i][j] = AnsMatrix[i][j]*scaling;
        }
        for(int k = 0; k < n; k++){
            if(k != i){
                elimination_Scaling = Matrix[k][pivot]/Matrix[i][pivot];
                for(int j = 0; j < n; j++){
                       Matrix[k][j] =    Matrix[k][j] - elimination_Scaling*Matrix[i][j];
                    AnsMatrix[k][j] = AnsMatrix[k][j] - elimination_Scaling*AnsMatrix[i][j];
                }
            }
        }
    }

    freopen(argv[2], "w", stdout);   // Opening input file
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%.8lf",AnsMatrix[chosen[i]][j]);
            if(j != n-1)
                printf(" ");
        }
        if(i != n-1)
            printf("\n");
    }
    fclose(stdout);
    return 0;
}