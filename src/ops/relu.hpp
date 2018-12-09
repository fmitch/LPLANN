#ifndef RELU_HPP
#define RELU_HPP

#include <vector>
#include <algorithm>

template <typename T>
void relu(Matrix<T> * input, Matrix<T>* output){
    int size = 1;
    for( int i = 0; i < input->dims.size(); i++){
        size *= input->dims[i];
    }
    for(int i = 0; i < size; i++){
        output->arr[i] = std::max<T>(input->arr[i], 0);
    }
}

template <typename T>
void leaky_relu(Matrix<T>* input, Matrix<T>* output, T a){
    int size = 1;
    for( int i = 0; i < input->dims.size(); i++){
        size *= input->dims[i];
    }
    for(int i = 0; i < size; i++){
        output->arr[i] = std::max(input->arr[i]/a, input->arr[i]);
    }
}

template <typename T>
void relu(T* input, T* output, int size){
    for(int i = 0; i < size; i++){
        output[i] = std::max<T>(output[i], 0);
    }
}

template <typename T>
void relu(T* input, T* output, int size, T a){
    for(int i = 0; i < size; i++){
        output->arr[i] = std::max(input->arr[i]/a, input->arr[i]);
    }
}

#endif
