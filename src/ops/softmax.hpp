#ifndef SOFTMAX_HPP
#define SOTFMAX_HPP

#include <vector>
#include <math.h>

template <typename T>
std::vector<float> softmax(std::vector<T> input){
    std::vector<float> output;
    T ymax = input.max();
    output.resize(input.size());
    for(int i = 0; i < input.size(); i++)
    {
          output[i] = exp(y(i) - ymax);
          output /= output.sum();
    }
}
