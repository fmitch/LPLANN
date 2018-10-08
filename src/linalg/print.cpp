#include "src/linalg/print.hpp"
#include <stdio.h>

void printMat(double* mat, int M, int N){
    for ( int i = 0; i < M; i++)
    {
        for ( int j = 0; j < N; j++)
            printf(" %f ", *((mat+i*N) + j));
            
        printf("\n");
    }
    printf("\n");
}

void printMat(double** mat, int M, int N){
    for ( int i = 0; i < M; i++)
    {
        for ( int j = 0; j < N; j++)
            printf(" %f ", mat[i][j]);
            
        printf("\n");
    }
    printf("\n");
}

void printVec(double* vec, int size){
    for ( int i = 0; i < size; i++)
    {
        printf(" %f ", vec[i]);
        printf("\n");
    }
    printf("\n");
}
