#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void write_output(char fname[], double** arr, int n ){
	FILE *f = fopen(fname, "w");
	for( int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fprintf(f, "%0.12f ", arr[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

int main(int argc, char *argv[]){

	int n = atoi(argv[1]) ;

	double **A = (double**)malloc(n*sizeof(double*)) ;

	printf("%d\n",RAND_MAX) ; 
	
    for(int i = 0 ; i < n ; i++){
    	A[i] = (double*)malloc(n*sizeof(double)) ;
    	for(int j = 0 ; j < n ; j++){
    		A[i][j] = 1.0 + (((double) (rand())) / 2147483.647) ; 
    	}
    } 

    write_output(argv[2],A,n) ;

}