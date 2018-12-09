#ifndef PARMATOP_HPP
#define PARMATOP_HPP

#include <omp.h>

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
