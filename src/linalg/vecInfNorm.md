1. [l-Infinity Vector Norm](#function-name-vecInfNorm)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

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


### Author: 
Frost Mitchell

### Last edited:
2017-12-2
