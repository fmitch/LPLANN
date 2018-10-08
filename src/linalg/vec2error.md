1. [l-2 Vector Error](#function-name-vec2error)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

See also [vec1error](./vec1error.md), [vecInfError](./vecInfError.md).

# Function Name: vec2error

## Description: 
Calculate the error between two vectors, v1, and v2. Use the 2 norm for the error.

## Input:
*  `double* v1` - A pointer to an array of elements  
*  `double* v2` - A pointer to an array of elements  
*  `int size` - The number of elements in the array  

## Output:
Return the 2 norm of v1 - v2

## Code:
```c
double vec2error(double* v1, double*> v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vec2norm(v, size);
}
```

### Author: 
Frost Mitchell

### Last edited:
2017-12-2

