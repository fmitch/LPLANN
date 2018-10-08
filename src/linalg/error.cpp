#include "src/linalg/norms.hpp"
#include "src/linalg/error.hpp"

double vec1error(double* v1, double* v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vec1norm(v, size);
}

double vec2error(double* v1, double* v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vec2norm(v, size);
}

double vecInfError(double* v1, double* v2, int size){
    double* v = new double[size];
    for (int i = 0; i < size; i++)
        v[i] = v1[i] - v2[i];
    return vecInfNorm(v, size);
}
