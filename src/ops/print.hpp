#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include "src/types/types.hpp"
#include <vector>

template <typename T>
void print_2d_slice(Matrix<T>* mat, int slice){
    int M = mat->dims[0];
    int N = mat->dims[1];
    T* arr = mat->slice(slice);
    for(int y=0; y<N;y++)
    {
        for(int x=0; x<M; x++){
            std::cout << arr[mat->index(x,y)] << "  ";
        }
        std::cout << std::endl;;
    }
}

template <typename T>
void print_1d_vector(Matrix<T>* mat){
    int M = mat->dims[0];
    for(int x=0; x<M; x++){
        std::cout << mat->arr[x] << "  ";
    }
    std::cout << std::endl;;
}

template <typename T>
void print_2d_slice(Matrix<T>* mat, int slice, int layer){
    int M = mat->dims[0];
    int N = mat->dims[1];
    T* arr = mat->slice(slice, layer);
    for(int y=0; y<N;y++)
    {
        for(int x=0; x<M; x++){
            std::cout << arr[mat->index(x,y)] << "  ";
        }
        std::cout << std::endl;;
    }
}


template <typename T>
void print_2d_slice(Matrix<T> mat, int slice){
    int M = mat.dims[0];
    int N = mat.dims[1];
    T* arr = mat.slice(slice);
    for(int y=0; y<N;y++)
    {
        for(int x=0; x<M; x++){
            std::cout << arr[mat.index(x,y)] << "  ";
        }
        std::cout << std::endl;;
    }
}

template <typename T>
void print_2d_slice(Matrix<T> mat, int slice, int layer){
    int M = mat.dims[0];
    int N = mat.dims[1];
    T* arr = mat.slice(slice, layer);
    for(int y=0; y<N;y++)
    {
        for(int x=0; x<M; x++){
            std::cout << arr[mat.index(x,y)] << "  ";
        }
        std::cout << std::endl;;
    }
}


#endif
