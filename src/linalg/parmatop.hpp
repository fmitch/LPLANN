#ifndef PARMATOP_HPP
#define PARMATOP_HPP

#include <omp.h>

template <typename T>
void parMatAdd(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) + *((B+i*N) + j);
}

template <typename T>
void parMatAddScalarInPlace(T* A, int M, int N, T scalar){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((A+i*N) + j) = *((A+i*N) + j) + scalar;
}

template <typename T>
void parMatSub(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) - *((B+i*N) + j);
}

template <typename T>
void parScaleMat(T* A, int M, int N, T scalar, T* output){
    for (int i=0; i<M ; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) * scalar;
}

template <typename T>
void parMatMul(T* A, T* B, int M, int N, int P, T* output){
    #pragma omp parallel for
    for (int i = 0; i<M; ++i)
        for ( int k=0; k<P; ++k)
        {
            T dot = 0;
            for (int j=0; j<N; ++j)
            {
                dot = dot + (*((A+i*N) + j)) * (*((B+j*P) + k));
            }
            *((output+i*P) + k)  = dot;
        }
}

template <typename T>
void parMatVecMul(T* A, T* v, int M, int N, T* output){
    #pragma omp parallel for
    for (int i = 0; i<M; i++)
    {
        T dot;
        dot = 0;
        for (int j=0; j<N; j++)
            dot = dot +  *((A+i*N) + j) * v[j];
        output[i] = dot;
    }
}


#endif
