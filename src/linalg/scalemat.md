1. [scaleMat](#function-name-scaleMat)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)


# Function Name: scaleMat

## Description: 
Multiply a matrix A by a constant scalar, a double. 

## Input:
*  `double* A` - A pointer to a 2D array of elements  
*  `int M` - The number of rows in the matrix   
*  `int N` - The number of columns in the matrix   
*  `double scalar` - A real, constant scalar to multiply each element of A by.   

## Output:
Returns the matrix multiplied by the constant scalar.

## Code:
```c
double* scaleMat(double* A, int N, int M, double scalar){
    double* C = new double[cols][rows];
    for (int j = 0; j < cols; j++)
        for (int i=0; i< rows; i++)
            C[i][j] = A[i][j] * scalar;
    return C;
}
```

## Example:
```c
double mat2x3B[2][3] = {{2.0, 1.0, 1.0},
						{2.0,1.0,1.0}};
printMat(scaleMat( (double*) mat2x3B,2, 3, 0.5), 2, 3);
```
Output:
```
1.000000  0.500000  0.500000 
1.000000  0.500000  0.500000 
```


### Author: 
Frost Mitchell

### Last edited:
2017-12-2

