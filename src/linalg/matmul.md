1. [matMul](#function-name-matMul)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)
    

# Function Name: matMul

## Description: 
Multiply two matrices, A and B. A must be MxN and B must be NxP in dimensions.

## Input:
*  `double* A` - A pointer to a 2D array of elements  
*  `double* B` - A pointer to a 2D array of elements  
*  `int M` - The number of rows in A  
*  `int N` - The number of columns in A and the number of rows in B  
*  `int P` - The number of columns in B  

## Output:
Returns the product of the two matrices.

## Code:
```c
double* matMul(double* A, double* B, int M, int N, int P){
    double* C = new double[M*N];
    double dot;
    for (int i = 0; i<M; i++)
        for ( int k=0; k<P; k++)
        {
            dot = 0;
            for (int j=0; j<N; j++)
                dot += (*((A+i*N) + j)) * (*((B+j*P) + k));
            *((C+i*P) + k)  = dot;
        }
    return C;
}
```

## Example:
```c
    double mat2x3[2][3] = {{1.0, 2.0, 2.0},
                            {1.0,1.0,2.0}};
    double mat3x2[3][2] = {{1.0, 2.0}, 
                            {2.0,1.0},
                            {1.0,2.0}};
    printMat(matMul( (double*) mat2x3, (double*) mat3x2,2, 3, 2), 2, 2);
```
Output:
``` 
7.000000  8.000000 
5.000000  7.000000 
```


### Author: 
Frost Mitchell

### Last edited:
2017-12-2

