#ifndef MATOP_HPP
#define MATOP_HPP

template <typename T>
void matAdd(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) + *((B+i*N) + j);
}

template <typename T>
void matAddScalar(T* A, int M, int N, T scalar, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((A+i*N) + j) = *((A+i*N) + j) + scalar;
}

template <typename T>
void matSub(T* A, T* B, int M, int N, T* output){
    for (int i=0; i< M; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) - *((B+i*N) + j);
}

template <typename T>
void matScale(T* A, int M, int N, T scalar, T* output){
    for (int i=0; i<M ; i++)
        for (int j = 0; j < N; j++)
            *((output+i*N) + j) = *((A+i*N) + j) * scalar;
}

template <typename T>
void matMul(T* A, T* B, int M, int N, int P, T* output){
    for (int i = 0; i<M; i++){
        for ( int k=0; k<P; k++){
            T dot;
            dot = 0;
            for (int j=0; j<N; j++){
                dot = dot + (*((A+i*N) + j)) * (*((B+j*P) + k));
            }
            *((output+i*P) + k)  = dot;
        }
    }
}

template <typename T>
void matVecMul(T* A, T* v, int M, int N, T* output){
    T dot;
    for (int i = 0; i<M; i++)
    {
        dot = 0;
        for (int j=0; j<N; j++)
            dot = dot +  *((A+i*N) + j) * v[j];
        output[i] = dot;
    }
}

template <typename T>
void dotProduct(T* v1, T* v2, int size, T* output){
    T out = 0;
    for (int i = 0; i < size; i++)
        out = out + v1[i] * v2[i];
    return out;
}


#endif
