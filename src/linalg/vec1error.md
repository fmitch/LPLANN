1. [l1 Vector Error](#function-name-vec1error)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

See also [vec2error](./vec2error.md), [vecInfError](./vecInfError.md).

# Function Name: vec1error 

## Description: 
Calculate the error between two vectors, v1, and v2. Use the 1 norm for the error.

## Input:
*  `double* v1` - A pointer to an array of elements  
*  `double* v2` - A pointer to an array of elements  
*  `int size` - The number of elements in the array  

## Output:
Return the 1 norm of v1 - v2
 
## Code:
```c
double vec1error(double* v1, double* v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vec1norm(v, size);
}
```


### Author: 
Frost Mitchell

### Last edited:
2017-12-2

