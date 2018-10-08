1. [l-Infinity Vector Error](#function-name-vecinferror)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

See also [vec1error](./vec1error.md), [vec2error](./vec2error.md).


# Function Name: vecInfError

## Description: 
Calculate the error between two vectors, v1, and v2. Use the Infinity norm for the error.

## Input:
*  `double* v1` - A pointer to an array of elements  
*  `double* v2` - A pointer to an array of elements  
*  `int size` - The number of elements in the array  

## Output:
Return the Infinity norm of v1 - v2

## Code:
```c
double vecInfError(double* v1, double* v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vecInfNorm(v, size);
}
```

### Author: 
Frost Mitchell

### Last edited:
2017-12-2

