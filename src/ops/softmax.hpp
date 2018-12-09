#ifndef SOFTMAX_HPP
#define SOFTMAX_HPP

#include <math.h>
#include <limits>

template <typename T>
void softmax(Matrix<T>* input, Matrix<float>* output){
    int size = 1;
    for (int i = 0; i < input->dims.size(); i++){
        size *= input->dims[i];
    }
    float sum = 0;
    for (int i = 0; i < size; i++){
        output->arr[i] = exp(input->arr[i]);
        sum += output->arr[i];
    }
    for (int i = 0; i < size; i++){
        output->arr[i] /= sum;
    }
}

template <typename T>
void softmax(T* input, float* output, int size){
    float sum = 0;
    for (int i = 0; i < size; i++){
        output[i] = exp(input[i]);
        sum += output[i];
    }
    for (int i = 0; i < size; i++){
        output[i] /= sum;
    }
}

template <typename T>
void normalize(Matrix<T>* input, Matrix<float>* output){
    int size = 1;
    for (int i = 0; i < input->dims.size(); i++){
        size *= input->dims[i];
    }
    T max = 0;
    for (int i = 0; i < size; i++){
        if (max < input->arr[i]){
            max = input->arr[i];
        }
    }
    float m = max/1.0;
    for (int i = 0; i < size; i++){
        output->arr[i] = input->arr[i] / m;
    }
}


#endif
