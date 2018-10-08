#ifndef POOLING_HPP
#define POOLING_HPP

#include <vector>
#include <algorithm>
#include <limits>

template <typename T>
std::vector<std::vector<T> > max_pooling(std::vector<std::vector<T> > input,  int pool_size, int stride){
    std::vector<std::vector<T> > output;
    output.resize(input.size()/stride);

    for( int i = 0; i < output.size(); i++)
        output[i].resize(input[0].size()/stride);

    for( int i = 0; i < input.size(); i= i + stride){
        for(int j = 0; j < input[0].size(); j = j + stride){
            T max = std::numeric_limits<T>::min();
            for( int m = 0; m < pool_size; m++){
                for( int n = 0; n < pool_size; n++){
                    max = std::max(max, input[i+m][j+n]);
                }
            }
            output[i/stride][j/stride] = max;
        }
    }
    return output;
}

template <typename T>
std::vector<std::vector<T> > average_pooling(std::vector<std::vector<T> > input,  int pool_size, int stride){
    std::vector<std::vector<T> > output;
    output.resize(input.size()/stride);

    for( int i = 0; i < output.size(); i++)
        output[i].resize(input[0].size()/stride);

    for( int i = 0; i< input.size(); i= i + stride){
        for(int j = 0; j < input[0].size(); j = j + stride){
            T sum = 0;
            for( int m = 0; m < pool_size; m++){
                for( int n = 0; n < pool_size; n++){
                    sum += input[i+m][j+n];
                }
            }
            output[i/stride][j/stride] = sum / (stride * stride);
        }
    }
    return output;
}

#endif
