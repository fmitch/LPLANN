#include "src/linalg/matop.hpp"
#include <stdio.h>

void matAdd(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) + *((B+i*N) + j);
}

void matAddScalarInPlace(T* A, int M, int N, T scalar){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((A+i*N) + j) += scalar;
}

void matSub(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) - *((B+i*N) + j);
}

void scaleMat(T* A, int M, int N, T scalar, T* output){
    for (int i=0; i<M ; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) * scalar;
}

void matMul(T* A, T* B, int M, int N, int P, T* output){
    T dot;
    for (int i = 0; i<M; i++)
        for ( int k=0; k<P; k++)
        {
            dot = 0;
            for (int j=0; j<N; j++)
            {
                dot += (*((A+i*N) + j)) * (*((B+j*P) + k));
            }
            *((output+i*P) + k)  = dot;
        }
}

void matVecMul(T* A, T* v, int M, int N, T* output){
    T dot;
    for (int i = 0; i<M; i++)
    {
        dot = 0;
        for (int j=0; j<N; j++)
            dot += *((A+i*N) + j) * v[j];
        output[i] = dot;
    }
}

T dotProduct(T* v1, T* v2, int size){
    T out = 0;
    for (int i = 0; i < size; i++)
        out += v1[i] * v2[i];
    return out;
}
