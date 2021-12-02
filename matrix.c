#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define CORE 4
  
// Maximum matrix size
#define MAX 4

int mat_A[MAX][MAX]; 
int mat_B[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 





pthread_t thread[CORE * 2];

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
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args) { // pass in the number of the ith thread
  
    int i, j;
    int core = (int)args;
  
    // Each thread computes 1/4th of matrix addition
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            // Compute Sum Row wise
            matSumResult[i][j] = mat_A[i][j] + mat_B[i][j];
        }
  
    }  
  return NULL;
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args) { // pass in the number of the ith thread
    int i, j;
    int core = (int)args;
  
    // Each thread computes 1/4th of matrix subtraction
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            // Compute Subtract row wise
            matDiffResult[i][j] = mat_A[i][j] - mat_B[i][j];
        }
  
    }  
  return NULL;
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) { // pass in the number of the ith thread
  int i, j;
    int core = (int)args;
  
    // Each thread computes 1/4th of matrix subtraction
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            // Compute Subtract row wise
            matProductResult[i][j] = mat_A[i][j] * mat_B[i][j];
        }
  
    } 
  return NULL;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() {
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    // 0. Get the matrix size from the command line and assign it to MAX
   
    // 1. Fill the matrices (matA and matB) with random values.
    
    // 2. Print the initial matrices.
    //printf("Matrix A:\n");
    //printMatrix(mat_A);
    //printf("Matrix B:\n");
    //printMatrix(mat_B);
    
    // 3. Create pthread_t objects for our threads.
    
    // 4. Create a thread for each cell of each matrix operation.
    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
   
    int i, j, step = 0;
    // Generating random values in mat_A and mat_B
    for (i = 0; i < MAX; i++)  {
  
        for (j = 0; j < MAX; j++)  {
  
            mat_A[i][j] = rand() % 10;
            mat_B[i][j] = rand() % 10;
  
        }
  
    }
  
  
    // Displaying mat_A
    printf("\nMatrix A:\n");
  
    for (i = 0; i < MAX; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            printf("%d ", mat_A[i][j]);
        }
  
        printf("\n");
    }
  
    // Displaying mat_B
    printf("\nMatrix B:\n");
  
    for (i = 0; i < MAX; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            printf("%d ", mat_B[i][j]);
        }
  
        printf("\n");
    }
  
    // Creating threads equal
    // to core size and compute matrix row
    for (i = 0; i < CORE; i++) {
  
        pthread_create(&thread[i], NULL, &computeSum, (void*)step);
        pthread_create(&thread[i + CORE], NULL, &computeDiff, (void*)step);
        pthread_create(&thread[i + CORE], NULL, &computeProduct, (void*)step);
        step++;
    }
  
    // Waiting for join threads after compute
    for (i = 0; i < CORE * 2; i++) {
  
        pthread_join(thread[i], NULL);
    }
  
    // Display Addition of mat_A and mat_B
    printf("\nSum of Matrix A and B:\n");
  
    for (i = 0; i < MAX; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            printf("%d ", matSumResult[i][j]);
        }
  
        printf("\n");
    }
  
    // Display Subtraction of mat_A and mat_B
    printf("\nSubtraction of Matrix A and B:\n");
  
    for (i = 0; i < MAX; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            printf("%d ", matDiffResult[i][j]);
        }
  
        printf("\n");
    }
    // Display Addition of mat_A and mat_B
    printf("\nProduct of Matrix A and B:\n");
  
    for (i = 0; i < MAX; i++) {
  
        for (j = 0; j < MAX; j++) {
  
            printf("%d ", matProductResult[i][j]);
        }
  
        printf("\n");
    }
  
    return 0;
  
  
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    
    // 5. Wait for all threads to finish.
    
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
