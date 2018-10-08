#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>


template <typename T>
struct Matrix 
{
    T* arr;
    std::vector<int> dims;
    T* slice(int index){
        return arr+index*dims[0]*dims[1]*dims[2];
    }
    Matrix(std::vector<int> d){ 
        int size = 1;
        for (int i =0; i < d.size(); i++){
            size *= d[i];
        }
        dims = d;
        arr = new T[size];
    }
    ~Matrix(){
        delete[] arr;
    }
    size_t index( int x, int y ) const { return x + y*dims[0]; }
    size_t index( int x, int y, int z ) const { return x + y*dims[0] + z*dims[0]*dims[1]; }
    size_t index( int x, int y, int z, int w) const { return x + y*dims[0] + z*dims[0]*dims[1] + w*dims[0]*dims[1]*dims[2]; }
};

#endif
