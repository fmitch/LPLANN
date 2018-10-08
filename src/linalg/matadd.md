1. [matAdd](#function-name-matAdd)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

# Function Name: matAdd 

## Description: 
Add two 2D matrices with the same dimensions.

## Input:
*  `double* A` - A pointer to a 2D array of elements  
*  `double* B` - A pointer to a 2D array of elements  
*  `int M` - The number of rows in the matrix   
*  `int N` - The number of columns in the matrix   

## Output:
Returns the sum of the two matrices, element wise.
 
## Code:
```c
double* matAdd(double* A, double* B, int M, int N){
    double* C = new double[M*N];
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((C+i*N) + j) = *((A+i*N) + j) + *((B+i*N) + j);
    return C;
}
```

## Example:
```c
double mat2x3[2][3] = {{1.0, 2.0, 2.0},
						{1.0,1.0,2.0}};
double mat2x3B[2][3] = {{2.0, 1.0, 1.0},
						{2.0,1.0,1.0}};
printMat(matAdd( (double*) mat2x3, (double*) mat2x3B,2, 3), 2, 3);

```

Output:
```
3.000000  3.000000  3.000000 
3.000000  2.000000  3.000000 
```


### Author: 
Frost Mitchell

### Last edited:
2017-12-2

