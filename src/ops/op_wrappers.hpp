#ifndef OPWRAPPERS_HPP
#define OPWRAPPERS_HPP

#include <vector>
#include <string>
#include <memory>
#include "src/construction/network.hpp"
#include "src/ops/conv.hpp"
#include "src/ops/fc.hpp"
#include "src/ops/pooling.hpp"
#include "src/ops/relu.hpp"
#include "src/linalg/parmatop.hpp"
#include "src/linalg/matop.hpp"
#include <omp.h>

#include "src/ops/print.hpp"

template <typename T1, typename T2>
void conv2d_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer, int slice, std::string padding = "zero"){
    std::vector<int> d = out_layer.output->dims; //Delete
    #pragma omp parallel for
    for (int out=0; out<out_layer.output->dims[2]; out++){
        for (int in=0; in<in_layer.output->dims[2]; in++){
            conv2d(in_layer.output->slice(in, slice), in_layer.output->dims[0], in_layer.output->dims[1], out_layer.output->slice(out), out_layer.weights->slice(in, out), out_layer.weights->dims[0], padding);
        }
    }
    if (out_layer.has_bias){
        #pragma omp parallel for
        for (int out=0; out<out_layer.output->dims[2]; out++){
            matAddScalarInPlace(out_layer.output->slice(out), out_layer.output->dims[0], out_layer.output->dims[1], out_layer.bias->arr[out]);
        }
    }
}

template <typename T1, typename T2>
void conv2d_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer, std::string padding="zero"){
    #pragma omp parallel for
    for (int out=0; out<out_layer.output->dims[2]; out++){
        for (int in=0; in<in_layer.output->dims[2]; in++){
            conv2d(in_layer.output->slice(in), in_layer.output->dims[0], in_layer.output->dims[1], out_layer.output->slice(out), out_layer.weights->slice(in, out), out_layer.weights->dims[0], padding);
        }
    }
    if (out_layer.has_bias){
        #pragma omp parallel for
        for (int out=0; out<out_layer.output->dims[2]; out++){
            matAddScalarInPlace(out_layer.output->slice(out), out_layer.output->dims[0], out_layer.output->dims[1], out_layer.bias->arr[out]);
        }
    }
}

template <typename T1, typename T2>
void pool_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer, int pool_type){
    int a = in_layer.output->dims[1];
    int b = out_layer.output->dims[1];
    std::vector<int> d = out_layer.output->dims; //Delete
    pool(in_layer.output, in_layer.output->dims[0] / out_layer.output->dims[0],
            in_layer.output->dims[1] / out_layer.output->dims[1], out_layer.output, pool_type);
}

template <typename T1, typename T2>
void flatten_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer){
    flatten_3d(in_layer, out_layer);
}

template <typename T1, typename T2>
void fc_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer){
    if (in_layer.output->dims.size() != 1){ //If not a flat matrix, flatten.
        int flat_size = in_layer.output->dims[0]*in_layer.output->dims[1]*in_layer.output->dims[2];
        std::shared_ptr<Matrix<T1>> flat(new Matrix<T1>(flat_size));
        int count = 0;
        for (int y=0; y<in_layer.output->dims[1]; y++){
            for (int x=0; x<in_layer.output->dims[0]; x++){
                for (int z=0; z<in_layer.output->dims[2]; z++){
                    flat->arr[count] = in_layer.output->arr[in_layer.output->index(x,y,z)];
                    count++;
                }
            }
        }
        in_layer.output = flat;
    }
    parMatMul(in_layer.output->arr, out_layer.weights->arr, 1, in_layer.output->dims[0], 
            out_layer.output->dims[0], out_layer.output->arr);
    if (out_layer.has_bias){
        matAdd(out_layer.output->arr, out_layer.bias->arr, 1, out_layer.output->dims[0], out_layer.output->arr);
    }
}

template <typename T1, typename T2>
void relu_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer){
    relu(in_layer.output, out_layer.output);
}

template <typename T1, typename T2>
void leaky_wrapper(Layer<T1> & in_layer, Layer<T2> & out_layer, T1 a=100){
    leaky_relu(in_layer.output, out_layer.output, a);
}

#endif 
