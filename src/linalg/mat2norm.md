1. [l-1 Vector Norm](#function-name-vec1norm)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)
2. [l-2 Vector Norm](#function-name-vec2norm)
    1. [Description](#description-1)
    2. [Input](#input-1)
    3. [Output](#output-1)
    4. [Code](#code-1)
    5. [Example](#example-1)
3. [l-Infinity Vector Norm](#function-name-vecInfNorm)
    1. [Description](#description-2)
    2. [Input](#input-2)
    3. [Output](#output-2)
    4. [Code](#code-2)
    5. [Example](#example-2)
4. [l-1 Matrix Norm](#function-name-mat1norm)
    1. [Description](#description-3)
    2. [Input](#input-3)
    3. [Output](#output-3)
    4. [Code](#code-3)
    5. [Example](#example-3)
5. [l-Infinity Matrix Norm](#function-name-matInfNorm)
    1. [Description](#description-4)
    2. [Input](#input-4)
    3. [Output](#output-4)
    4. [Code](#code-4)
    5. [Example](#example-4)

# Function Name: vec1norm

## Description: 
Calculate the 1 norm of a vector, or the sum of the absolute value of each element.

## Input:
*  `double* vec` - A pointer to an array of elements  
*  `int size` - The size of the vector  

## Output:
Returns the sum of the absolute values of each element in the vector

## Code:
```c
double vec1norm(double* vec, int size){
    double out = 0;
    for (int i=0;i<size;i++)
        out += fabs(vec[i]);
    return out;
}
```

## Example:
```c
double vec3[3] = { 1.0, 1.0, 2.0};
printf(" %f \n\n", vec1norm(vec3, 3));
```
Output:
```
4.000000 
```

# Function Name: vec2norm

## Description: 
Calculate the 2 norm of a vector, or the square root of the sum of the squares of each element in the vector.

## Input:
*  `double* vec` - A pointer to an array of elements  
*  `int size` - The size of the vector  

## Output:
Returns the square root of the sum of the squares of each element in the vector.

## Code:
```c
double vec2norm(double* vec, int size){
    double out = 0;
    for (int i=0;i<size;i++)
        out += pow(vec[i], 2);
    return pow(out, 0.5);
}
```

## Example:
```c
double vec3[3] = { 1.0, 1.0, 2.0};
printf(" %f \n\n", vec2norm(vec3, 3));
```
Output:
```
2.449490 
```

# Function Name: vecInfNorm

## Description: 
Calculate the infinity norm of a vector, or the maximum absolute value of the elements in the vector.

## Input:
*  `double* vec` - A pointer to an array of elements  
*  `int size` - The size of the vector  

## Output:
Returns the maximum absolute value of the elements in the vector.

## Code:
```c
double vecInfNorm(double* vec, int size){
    double max = 0;
    for (int i=0;i<size;i++)
        if (max < fabs(vec[i]))
            max = fabs(vec[i]);
    return max;
}
```

## Example:
```c
double vec3[3] = { 1.0, 1.0, 2.0};
printf(" %f \n\n", vecInfNorm(vec3, 3));
```
Output:
```
2.000000 
```

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

# Function Name: matInfNorm

## Description: 
Calculate the 1 norm of a 2D matrix, or the maximum sum of the absolute values of each row.

## Input:
*  `double* mat` - A pointer to a 2D array of elements  
*  `int M` - The number of rows in the matrix   
*  `int M` - The number of columns in the matrix   

## Output:
Returns the maximum sum of the absolute values of each row.

## Code:
```c
double matInfNorm(double* mat, int M, int N){
    double max = 0;
    double sum;
    for (int j=0;j<N;j++)
    {
        sum = 0;
        for (int i=0;i<M;i++)
            sum += fabs(*((mat+i*N)+j));
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
printf(" %f \n\n", matInfNorm((double*) mat2x3B, 2,3));
```
Output:
```
8.000000 
```

### Author: 
Frost Mitchell

### Last edited:
2017-12-2
