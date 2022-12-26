#include <stdio.h>
#include <math.h>
#include <time.h>
int main(int argc,char **argv ){
    // Declaring Variables
    long double Input[2];
    int i=1;
    long double term=1;
    long double ans=0;
    bool negative = false;

    freopen(argv[1], "r", stdin);   // Opening input file
    scanf("%Lf %Lf",&Input[0],&Input[1]); // Inputing X and precission
    if(Input[0] < 0){
        negative = true;
        Input[0] = Input[0]*-1;
    }
    fclose(stdin);


    while(true){

        term = (term/((long double)i))*Input[0];  // Dividing before multiplication to prevent overflow

        if(term < (Input[1]/((long double)1000))) // Dividing the Precission by 1000 to inmprove the precission
            break;
        
        if(i%2 == 1){ // Checking whether it is odd term
            // Deciding the +ve or -ve and adding to required sum
            if(i%4 == 1)
                ans = ans + term;
            else if(i%4 == 3)
                ans = ans - term;
        }
        
        i++;
    }
    freopen(argv[2], "w", stdout);   // Opening output file

    if(negative == true)
        ans = ans*-1;

	printf("Sin(%.12Lf) is approximately = %.12Lf\n",
	   Input[0],ans);                     // Outputing the answer
    
    fclose(stdout);                       // Closing output.txt

    return 0;
}
