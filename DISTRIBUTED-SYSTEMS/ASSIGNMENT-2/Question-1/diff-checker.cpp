#include"bits/stdc++.h"
using namespace std;
int main(){
    vector<double> a[3557];
    vector<double> b[3557];
    double x;
    freopen("output_3_comb.txt", "r", stdin);
    for(int i=0;i<3357;i++)
        for(int j=0;j<3357;j++){
            cin>>x;
            a[i].push_back(x);
        }
    for(int i=0;i<3357;i++)
        for(int j=0;j<3357;j++){
            cin>>x;
            b[i].push_back(x);
        }
    fclose(stdin);
    freopen("output_3_diff.txt", "w", stdout);
    int k = 0;
    for(int i=0;i<3357;i++)
        for(int j=0;j<3357;j++)
            if(a[i][j]!=b[i][j]){
                cout<<i<<" "<<j<<" "<<a[i][j]<<" "<<b[i][j]<<" "<< abs(a[i][j]-b[i][j])<<'\n';
                k++;
                if(k>1000)
                    break;
            }
    fclose(stdout);
    return 0;
        
}