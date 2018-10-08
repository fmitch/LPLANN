#ifndef RELU_HPP
#define RELU_HPP

#include <vector>
#include <algorithm>

template <typename T>
std::vector<std::vector<T> > relu(std::vector<std::vector<T> > input){
    std::vector<std::vector<T> > output;
    output.resize(input.size());

    for( int i = 0; i < output.size(); i++)
        output[i].resize(input[0].size());

    for( int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[0].size(); j++){
            output[i][j] = std::max(input[i][j], 0);
        }
    }
    return output;
}

template <typename T>
std::vector<std::vector<T> > leaky_relu(std::vector<std::vector<T> > input, int a=100){
    std::vector<std::vector<T> > output;
    output.resize(input.size());

    for( int i = 0; i < output.size(); i++)
        output[i].resize(input[0].size());

    for( int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[0].size(); j++){
            output[i][j] = std::max(input[i][j]/a, input[i][j]);
        }
    }
    return output;
}

#endif
