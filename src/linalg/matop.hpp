#ifndef MATOP_HPP
#define MATOP_HPP

float* matAdd(float* A, float* B, int M, int N);
float* matSub(float* A, float* B, int M, int N);
float* scaleMat(float* A, int M, int N, float scalar);
float* matMul(float* A, float* B, int M, int N, int P);
float* matVecMul(float* A, float* v, int M, int N);
float  dotProduct(float* v1, float* v2, int size);

#endif
