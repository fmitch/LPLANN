#include <math.h>
#include "src/linalg/norms.hpp"

double vec1norm(double* vec, int size){
    double out = 0;
    for (int i=0;i<size;i++)
        out += fabs(vec[i]);
    return out;
}

double vec2norm(double* vec, int size){
    double out = 0;
    for (int i=0;i<size;i++)
        out += pow(vec[i], 2);
    return pow(out, 0.5);
}

double vecInfNorm(double* vec, int size){
    double max = 0;
    for (int i=0;i<size;i++)
        if (max < fabs(vec[i]))
            max = fabs(vec[i]);
    return max;
}

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
