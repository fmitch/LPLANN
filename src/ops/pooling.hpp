#ifndef POOLING_HPP
#define POOLING_HPP

#include <algorithm>
#include <limits>
#include <memory>
#include <string>

template <typename T>
void pool(std::shared_ptr<Matrix<T>> input,  int pool_size, int stride, std::shared_ptr<Matrix<T>> output, int pool_type){
    switch (pool_type){
        case MAX:
            max_pooling(input, pool_size, stride, output);
            break;
        case ZERO:
            zero_pooling(input, pool_size, stride, output);
            break;
        case AVERAGE:
            average_pooling(input, pool_size, stride, output);
            break;
    }
}

template <typename T>
void max_pooling(std::shared_ptr<Matrix<T>> input, int pool_size, int stride, std::shared_ptr<Matrix<T>> output){
    for( int h = 0; h < input->dims[2]; h++){
        for( int i = 0; i < input->dims[0]; i= i + stride){
            for(int j = 0; j < input->dims[1]; j = j + stride){
                T max = std::numeric_limits<T>::lowest();
                for( int m = 0; m < pool_size; m++){
                    for( int n = 0; n < pool_size; n++){
                        max = std::max(max, input->arr[input->index(i+m,j+n, h)]);
                    }
                }
                output->arr[output->index(i/stride, j/stride, h)] = max;
            }
        }
    }
}

template <typename T>
void zero_pooling(std::shared_ptr<Matrix<T>> input, int pool_size, int stride, std::shared_ptr<Matrix<T>> output){
    for( int h = 0; h < input->dims[2]; h++){
        for( int i = 0; i < input->dims[0]; i= i + stride){
            for(int j = 0; j < input->dims[1]; j = j + stride){
                T min = 1; //Assume values are 1 or 0, with 0 being kept
                for( int m = 0; m < pool_size; m++){
                    for( int n = 0; n < pool_size; n++){
                        min = input->arr[input->index(i+m,j+n, h)]*min; //If value is 0, store;
                    }
                }
                output->arr[output->index(i/stride, j/stride, h)] = min;
            }
        }
    }
}

template <typename T>
void average_pooling(std::shared_ptr<Matrix<T>> input,  int pool_size, int stride, std::shared_ptr<Matrix<T>> output){
    for( int h = 0; h < input->dims[2]; h++){
        for( int i = 0; i< input->dims[0]; i= i + stride){
            for(int j = 0; j < input->dims[1]; j = j + stride){
                T sum = 0;
                for( int m = 0; m < pool_size; m++){
                    for( int n = 0; n < pool_size; n++){
                        sum = sum +  input->arr[input->index(i+m,j+n,h)];
                    }
                }
                output->arr[output->index(i/stride, j/stride, h)] =  sum / (stride * stride);

            }
        }
    }
}

#endif
