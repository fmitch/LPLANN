1. [l-1 Matrix Norm](#function-name-mat1norm)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)


# Function Name: mat1norm

## Description: 
Calculate the 1 norm of a 2D matrix, or the maximum sum of the absolute values of each column.

## Input:
*  `double* mat` - A pointer to a 2D array of elements  
*  `int M` - The number of rows in the matrix   
*  `int N` - The number of columns in the matrix   
  
## Output:
Returns the maximum sum of the absolute values of each column.

## Code:
```c
double mat1norm(double* mat, int M, int N){
    double max = 0;
    double sum;
    for (int i=0;i<M;i++)
    {
        sum = 0;
        for (int j=0;j<N;j++)
            sum += fabs( *((mat+i*N)+j) );
        if (max < sum)
            max = sum;
    }
    return max;
}
```

## Example:
```c
double mat2x3B[2][3] = {{2.0, 1.0, 1.0},
						{2.0,7.0,1.0}};
printf(" %f \n\n", mat1norm((double*) mat2x3B, 2,3));
```
Output:
```
10.000000 
```


### Author: 
Frost Mitchell

### Last edited:
2017-12-2
