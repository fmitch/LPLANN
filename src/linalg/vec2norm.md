1. [l-2 Vector Norm](#function-name-vec2norm)
    1. [Description](#description)
    2. [Input](#input)
    3. [Output](#output)
    4. [Code](#code)
    5. [Example](#example)

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


### Author: 
Frost Mitchell

### Last edited:
2017-12-2
