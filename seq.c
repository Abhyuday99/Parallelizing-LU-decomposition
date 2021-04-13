#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void crout(double const **A, double **L, double **U, int n) {
	int i, j, k;
	double sum = 0;
	printf("TESTING\n") ; 
	for (i = 0; i < n; i++) {
		printf("TESTING3\n") ; 
		L[i][i] = 1;
	}
	printf("TESTING2\n") ; 
	for (j = 0; j < n; j++) {
		for (i = j; i < n; i++) {
			sum = 0;
			for (k = 0; k < j; k++) {
				sum = sum + L[i][k] * U[k][j];	
			}
			L[i][j] = A[i][j] - sum;
		}
		for (i = j; i < n; i++) {
			sum = 0;
			for(k = 0; k < j; k++) {
				sum = sum + L[j][k] * U[k][i];
			}
			if (L[j][j] == 0) {				
				exit(0);
			}
			U[j][i] = (A[j][i] - sum) / L[j][j];
		}
	}
}

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
	
	int N = n*n;
	char* num_threads = (char*)malloc(sizeof(char)*(strlen(argv[3]) + 1) ); 

	double **A = (double**)malloc(n*sizeof(double*)) ; 
	double **L = (double**)malloc(n*sizeof(double*)) ; 
	double **U = (double**)malloc(n*sizeof(double*)) ;  

	FILE *fp = fopen(argv[2],"r");
	
    for(int i = 0 ; i < n ; i++){
    	A[i] = (double*)malloc(n*sizeof(double)) ;
    	for(int j = 0 ; j < n ; j++){
    		fscanf(fp, "%lf", &(A[i][j])) ;
    	}
    	L[i] = (double*)malloc(n*sizeof(double)) ;
    	U[i] = (double*)malloc(n*sizeof(double)) ;
    } 
    crout(A,L,U,n) ; 
    char lout[30] = "output_L_0_" ; 
    strcat(lout,argv[3]) ; 
    strcat(lout,".txt") ; 
    char uout[30] = "output_U_0_" ;
    strcat(uout,argv[3]) ;
    strcat(uout,".txt") ; 
    write_output(lout,L,n) ; 
    write_output(uout,U,n) ; 
   
	return 1 ; 
}

