#ifndef MATRIX_TYPES_HPP
#define MATRIX_TYPES_HPP

#include <vector>

template <typename T>
struct Matrix 
{
    T* arr;
    
    std::vector<int> dims;
    T* slice(int ind){
        return arr+ ind*dims[0]*dims[1];
    }
    T* slice(int ind, int output){
        return arr + ind*dims[0]*dims[1] + output*dims[0]*dims[1]*dims[2];
    }
    Matrix(std::vector<int> d){ 
        int size = 1;
        for (int i =0; i < d.size(); i++){ 
            size *= d[i]; }
        dims = d;
        arr = new T[size];
        for (int i = 0; i < size; i++){ 
            arr[i] = 0; }
    }
    Matrix(int d){ 
        dims.push_back(d);
        arr = new T[d];
        for (int i = 0; i < d; i++){
            arr[i] = 0;
        }
    }
    ~Matrix(){
        delete[] arr;
    }
    size_t index( int x, int y ) const { return (x + y*dims[0]); }
    size_t index( int x, int y, int z ) const { return (x + y*dims[0] + z*dims[0]*dims[1]); }
    size_t index( int x, int y, int z, int w) const { return (x + y*dims[0] + z*dims[0]*dims[1] + w*dims[0]*dims[1]*dims[2]); }
};

#endif
