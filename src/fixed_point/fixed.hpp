#ifndef FIXED_HPP
#define FIXED_HPP

#include <math.h>

void switch_precision(Layer<fixed> & in_layer, Layer<fixed> & out_layer){
    if (in_layer.remainder > out_layer.remainder){
        int shift = in_layer.remainder - out_layer.remainder;
        int flat_size = 1;
        for (int i = 0; i < in_layer.output->dims.size(); i++){
            flat_size *= in_layer.output->dims[i];
        }
        for (int i = 0; i < flat_size; i++){
            out_layer.output->arr[i] = in_layer.output->arr[i] >> shift;
        }
    } else if (out_layer.remainder > in_layer.remainder){
        int shift = out_layer.remainder - in_layer.remainder;
        int flat_size = 1;
        for (int i = 0; i < in_layer.output->dims.size(); i++){
            flat_size *= in_layer.output->dims[i];
        }
        for (int i = 0; i < flat_size; i++){
            out_layer.output->arr[i] = in_layer.output->arr[i] << shift;
        }
    }
}

void adjust_precision(Layer<float> & in_layer, Layer<fixed> & out_layer){
    int shift = out_layer.remainder 
    int flat_size = 1;
    for (int i = 0; i < in_layer.output->dims.size(); i++){
        flat_size *= in_layer.output->dims[i];
    }
    for (int i = 0; i < flat_size; i++){
        out_layer.output->arr[i] = (float) in_layer.output->arr[i] / (float) (1 << shift);
    }
}

void adjust_precision(Layer<fixed> & in_layer, Layer<float> & out_layer){
    int shift = in_layer.remainder 
    int flat_size = 1;
    for (int i = 0; i < in_layer.output->dims.size(); i++){
        flat_size *= in_layer.output->dims[i];
    }
    for (int i = 0; i < flat_size; i++){
        out_layer.output->arr[i] = (fixed) round(in_layer.output->arr[i] *  (1 << shift));
    }
}

#endif
