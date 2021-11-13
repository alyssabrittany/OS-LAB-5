#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MAX 4
typedef void* (*Operators)(void*);


int matA[MAX][MAX]; 
int matB[MAX][MAX]; 
int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 

void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nchecking\n");
    printf("\n");

}

void* computeSum(void* args) { // pass in the number of the ith thread
    int *i = (int*) args; // Fetches the appropriate coordinates from the argument, and sets
    int row = (*i)/MAX;
    int col = (*i)%MAX;
    matSumResult[row][col] = matA[row][col] + matB[row][col]; // the cell of matSumResult at the coordinates to the sum of the values at the coordinates of matA and matB.
}

void* computeDiff(void* args) { // pass in the number of the ith thread
    int *i = (int*) args; // Fetches the appropriate coordinates from the argument, and sets
    int row = (*i)/MAX;
    int col = (*i)%MAX;
    matDiffResult[row][col] = matA[row][col] - matB[row][col]; // the cell of matSumResult at the coordinates to the difference of the values at the coordinates of matA and matB.
}

void* computeProduct(void* args) { // pass in the number of the ith thread
    int *i = (int*) args; // Fetches the appropriate coordinates from the argument, and sets
    int row = (*i)/MAX;
    int col = (*i)%MAX;
    matProductResult[row][col] = matA[row][col] * matB[row][col]; // the cell of matSumResult at the coordinates to the inner product of matA and matB.
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    //int j,k = 0;
    Operators operation[3];
    // 0. Get the matrix size from the command line and assign it to MAX
    // not doing the extra credit
    
    // 1. Fill the matrices (matA and matB) with random values.
    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    fillMatrix(matA);
    printMatrix(matA);
    printf("Matrix B:\n");
    fillMatrix(matB);
    printMatrix(matB);
    
    // 3. Create pthread_t objects for our threads.
    pthread_t objects[3][4*4];
    
    // 4. Create a thread for each cell of each matrix operation. 
		operation[0] = &computeProduct;
    operation[1] = &computeSum;
    operation[2] = &computeDiff;
    for(int j = 0; j < 3; j++){
			for(int k = 0; k < MAX*MAX; k++){ // One way to do this is to malloc memory for the thread number i, populate the coordinates into that space, and pass that address to the thread.
        int *index = (int*)malloc(sizeof(int));
        int *op_id = index;
				*index = j;     
        pthread_create(&objects[*op_id][*index], NULL, operation[*op_id], (void*)index); // The thread will use that number to calcuate its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
      }
    }
    printf("done with 4\n");
    // 5. Wait for all threads to finish.
    for(int j = 0; j < 3; j++){
      printf("in J\n");
      for(int k = 0; k < MAX*MAX; k++){
        printf("Joining\n");
        pthread_join(objects[j][k], NULL);
        
      }
    }
    printf("done with 5\n");
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    return 0;
  
}