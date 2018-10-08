#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include "src/types/types.hpp"
#include <vector>
#include <memory>

template <typename T>
void print_2d_slice(std::shared_ptr<Matrix<T>> mat, int slice){
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


#endif
