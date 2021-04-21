#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int thread_count = 2 ; 
int batch_size = 0 ;

void crout(double const **A, double **L, double **U, int n) {
	int i, j, k;
	double sum = 0;
	
	for (i = 0; i < n; i++) {
		L[i][i] = 1;
	}
	
	int comm_size ; 
	int my_rank ; 

	MPI_Init(NULL,NULL) ; 
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size) ; 
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank) ; 

	for (j = 0; j < n; j++) {

		for (i = j ; i < n; i++) {

			if(i % comm_size == my_rank){
				sum = 0;
				for (k = 0; k < j; k++) {
					sum = sum + L[i][k] * U[k][j];	
				}
				L[i][j] = A[i][j] - sum;
				
			}
			
			 
		}

		for(i = j ; i < n ; i++){
			MPI_Bcast((L[i] + j),1,MPI_DOUBLE,i % comm_size,MPI_COMM_WORLD) ;
			
		}
		
		for (i = j ; i < n; i++) {
			if(i % comm_size == my_rank){
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

		for(i = j ; i < n ; i++){
			
			MPI_Bcast((U[j] + i),1,MPI_DOUBLE,i % comm_size,MPI_COMM_WORLD) ;
		}
	}

	MPI_Finalize() ; 
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
	
	
	char* num_threads = (char*)malloc(sizeof(char)*(strlen(argv[3]) + 1) ); 
	thread_count = atoi(argv[3]) ;

	batch_size = n / thread_count ;
	if(n % thread_count){
		batch_size += 1 ; 
	}

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
    char lout[30] = "output_L_4_" ; 
    strcat(lout,argv[3]) ; 
    strcat(lout,".txt") ; 
    char uout[30] = "output_U_4_" ;
    strcat(uout,argv[3]) ;
    strcat(uout,".txt") ; 
    write_output(lout,L,n) ; 
    write_output(uout,U,n) ; 
   
	return 1 ; 
}

