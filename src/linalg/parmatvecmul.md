1. [Parallel Matrix-Vector Multiplication](#function-name-parmatvecmul)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

# Function Name: parMatVecMul

## Description: 
Calculate the product of a matrix and a vector. The matrix is MxN, and the vector must be Nx1. Uses OpenMP to parallelize operations.

## Input:
*  `double* A` - A pointer to a 2D array of elements
*  `double* v` - A pointer to an array of elements
*  `int M` - The number of rows in the matrix 
*  `int N` - The number of columns in the matrix 

## Output:
Return the product of A and v. 

## Code:
```c
double* parMatVecMul(double* A, double* v, int M, int N){
    double* C = new double[M];
    double dot;
    #pragma omp parallel for
    for (int i = 0; i<M; i++)
    {
        dot = 0;
        for (int j=0; j<N; j++)
            dot += *((A+i*N) + j) * v[j];
        C[i] = dot;
    }
    return C;
}
```

## Example:
```c
double mat2x3[2][3] = {{1.0, 2.0, 2.0},
						{1.0,1.0,2.0}};
double vec3[3] = { 1.0, 1.0, 2.0};
printVec(parMatVecMul( (double*) mat2x3,vec3, 2, 3),2);
```
Output:
```
7.000000 
6.000000 
```

### Author: 
Frost Mitchell

### Last edited:
2017-12-2
