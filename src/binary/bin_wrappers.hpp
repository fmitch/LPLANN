#ifndef BINWRAPPERS_HPP
#define BINWRAPPERS_HPP

#include <vector>
#include <memory>
#include <math.h>
#include "src/construction/layer.hpp"
#include "src/binary/conv.hpp"
#include "src/binary/fc.hpp"

#include "src/ops/print.hpp"

//In general, we always assume a function has binary input and output, not reg

template <typename T1>
void conv2d_wrapper(Layer<T1> & in_layer, Layer<binary16> & out_layer, int slice){
    float2bin_conv(in_layer, out_layer, slice);
}

template <typename T1>
void conv2d_wrapper(Layer<T1> & in_layer, Layer<binary16> & out_layer){
    float2bin_conv(in_layer, out_layer);
}

void conv2d_wrapper(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    bin2reg_conv_prep(in_layer, out_layer);
    reg2bin_conv(in_layer, out_layer);
}

void fc_wrapper(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    binary16 * arr = out_layer.output->arr;
    binary16 * in = in_layer.output->arr;
    bin2reg_fc_prep(in_layer);
    reg2int_fc(in_layer, out_layer);
    int2bin_fc_prep(out_layer);
}

void fc_output_wrapper(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    bin2reg_fc_prep(in_layer);
    reg2int_fc(in_layer, out_layer);
}

void bin2float_wrapper(Layer<binary16> & in_layer, Layer<float> & out_layer){
    int size = 1;
    for (int i=0; i < in_layer.output->dims.size(); i++){
        size *= in_layer.output->dims[i];
    }
    for (int i = 0; i < size; i++){
        out_layer.output->arr[i] = in_layer.output->arr[i] * -2 + 1.0;
    }
}


#endif 
