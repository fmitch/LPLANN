#include "src/linalg/matop.hpp"
#include <stdio.h>

float* matAdd(float* A, float* B, int M, int N){
    float* C = new float[M*N];
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((C+i*N) + j) = *((A+i*N) + j) + *((B+i*N) + j);
    return C;
}

float* matSub(float* A, float* B, int M, int N){
    float* C = new float[M*N];
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((C+i*N) + j) = *((A+i*N) + j) - *((B+i*N) + j);
    return C;
}

float* scaleMat(float* A, int M, int N, float scalar){
    float* C = new float[M*N];
    for (int i=0; i<M ; i++)
        for (int j = 0; j < N; j++)
            *((C+i*N) + j) = *((A+i*N) + j) * scalar;
    return C;
}

float* matMul(float* A, float* B, int M, int N, int P){
    float* C = new float[M*N];
    float dot;
    for (int i = 0; i<M; i++)
        for ( int k=0; k<P; k++)
        {
            dot = 0;
            for (int j=0; j<N; j++)
            {
                dot += (*((A+i*N) + j)) * (*((B+j*P) + k));
            }
            *((C+i*P) + k)  = dot;
        }
    return C;
}

float* matVecMul(float* A, float* v, int M, int N){
    float* C = new float[M];
    float dot;
    for (int i = 0; i<M; i++)
    {
        dot = 0;
        for (int j=0; j<N; j++)
            dot += *((A+i*N) + j) * v[j];
        C[i] = dot;
    }
    return C;
}

float dotProduct(float* v1, float* v2, int size){
    float out = 0;
    for (int i = 0; i < size; i++)
        out += v1[i] * v2[i];
    return out;
}
