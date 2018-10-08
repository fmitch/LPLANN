1. [dotProduct](#function-name-dotProduct)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)


# Function Name: dotProduct

## Description: 
Calculate the dot product of two vectors with the same size.

## Input:
*  `double* v1` - A pointer to an array of elements  
*  `double* v2` - A pointer to an array of elements  
*  `int size` - The number of elements in the vector   
 
## Output:
Return the dot product of v1 and v2. 

## Code:
```c
double  dotProduct(double* v1, double* v2, int size){
    double out = 0;
    for (int i = 0; i < size; i++)
        out += v1[i] * v2[i];
    return out;
}
```

## Example:
```c
double vec3[3] = { 1.0, 1.0, 2.0};
printf(" %f \n\n", dotProduct(vec3, vec3, 3));
```
Output:
```
6.000000 
```

### Author: 
Frost Mitchell

### Last edited:
2017-12-2

