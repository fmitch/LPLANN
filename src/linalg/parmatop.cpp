#include "src/linalg/parmatop.hpp"
#include <stdio.h>
#include <omp.h>

double* parMatMul(double* A, double* B, int M, int N, int P){
    double* C = new double[M*N];
    #pragma omp parallel for
    for (int i = 0; i<M; i++)
        for ( int k=0; k<P; k++)
        {
            double dot;
            dot = 0;
            for (int j=0; j<N; j++)
            {
                dot += (*((A+i*N) + j)) * (*((B+j*P) + k));
            }
            *((C+i*P) + k)  = dot;
        }
    return C;
}

double* parMatVecMul(double* A, double* v, int M, int N){
    double* C = new double[M];
    #pragma omp parallel for
    for (int i = 0; i<M; i++)
    {
        double dot;
        dot = 0;
        for (int j=0; j<N; j++)
            dot += *((A+i*N) + j) * v[j];
        C[i] = dot;
    }
    return C;
}

