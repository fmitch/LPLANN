1. [l-1 Vector Norm](#function-name-vec1norm)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

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


### Author: 
Frost Mitchell

### Last edited:
2017-12-2
