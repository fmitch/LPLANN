#ifndef BINFC_HPP
#define BINFC_HPP

#include "src/types/types.hpp"
#include "src/binary/layer.hpp"
#include <vector>
#include <string>
#include <math.h>

//Function flattens binary array in input_layer, then converts it to
void bin2reg_fc_prep(Layer<binary16> & in_layer){
    int flat_size = in_layer.output->dims[0];
    int sixteen_count = 0;
    int reg = 0;
    binary16* arr = in_layer.output->arr;
    binary16 tmp = 0;
    for (int k=0; k<flat_size; ++k){ //What if i reworked this to only accept mults of 16?
        binary16 a = in_layer.output->arr[k] << sixteen_count;
        tmp |= in_layer.output->arr[k] << sixteen_count;
        ++sixteen_count;
        if (sixteen_count == 16){
            in_layer.output->arr[reg] = tmp;
            tmp = 0;
            sixteen_count = 0;
            ++reg;
        }
    }
}

void reg2int_fc(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    binary16* A = in_layer.output->arr;
    binary16* B = out_layer.weights->arr;
    binary16* output = out_layer.output->arr;
    int M = 1;
    int N = out_layer.weights->dims[0];
    int P = out_layer.weights->dims[1];
    #pragma omp parallel for
    for (int i=0; i < M; ++i){
        for (int k=0; k < P; ++k){
            binary16 dot = 0;
            for (int j=0; j<N; ++j){
                binary16 a = 16 - 2*__builtin_popcount((uint16_t)(A[i*N+j] ^ B[j*P+ k]));
                dot += 16 - 2*__builtin_popcount((uint16_t)(A[i*N+j] ^ B[j*P+ k]));
            }
            output[i*P+ k] = dot - in_layer.remainder;
        }
    }
}

void int2bin_fc_prep(Layer<binary16> & layer){
    binary16* arr = layer.output->arr;
    for (int i=0; i<layer.output->dims[0]; ++i){
        layer.output->arr[i] = signbit(layer.output->arr[i]);
    }
}

#endif
