#ifndef BIN_CONV_HPP
#define BIN_CONV_HPP

#include "src/types/types.hpp"
#include "src/binary/layer.hpp"
#include <vector>
#include <string>
#include <math.h>
#include <omp.h>

void reg2bin_conv(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    int M = out_layer.output->dims[0];
    int N = out_layer.output->dims[1];
    int O = out_layer.output->dims[2];
    int K = out_layer.remainder;
    binary16* filter = out_layer.weights->arr;
    int step = K/2;
    #pragma omp parallel for
    for (int out=0; out < O; ++out){
        binary16* output = out_layer.output->slice(out);
        for (int i=0; i<M; ++i){
            for (int j=0; j<N; j++){
                output[i*N+j] = 0;
            }
        }
        for (int in=0; in < in_layer.output->dims[2]; ++in){
            //conv2d Assumes you want zero padding, because I don't care about others yet.
            binary16* input = in_layer.output->slice(in);
            for(int i=0; i < M; ++i){              // rows 
                for(int j=0; j < N; ++j){          // columns 
                    int offset = 0;
                    binary16 fil = filter[out*O+in];
                    binary16 in_holder = input[i*N+j];
                    if (i == 0){ 
                        offset = K;
                        fil = fil & 0x003f;
                        in_holder = in_holder & 0x003f;
                        if (j == 0){
                            offset += K-1;
                            fil = fil & 0x00db;
                            in_holder = in_holder & 0x00db;
                        } else if (j == N-1){
                            offset += K-1;
                            fil = fil & 0x01b6;
                            in_holder = in_holder & 0x01b6;
                        }
                    } else if (i == M-1){
                        offset = K;
                        fil = fil & 0x01f8;
                        in_holder = in_holder & 0x01f8;
                        if (j == 0){
                            offset += K-1;
                            fil = fil & 0x00db;
                            in_holder = in_holder & 0x00db;
                        } else if (j == N-1){
                            offset += K-1;
                            fil = fil & 0x01b6;
                            in_holder = in_holder & 0x01b6;
                        }
                    } else if (j == 0){
                        offset = K;
                        fil = fil & 0x00db;
                        in_holder = in_holder & 0x00db;
                    } else if (j == N-1){
                        offset = K;
                        fil = fil & 0x01b6;
                        in_holder = in_holder & 0x01b6;
                    } 

                    output[i*N+j] += K*K-offset-2*__builtin_popcount(in_holder^fil);
                    //output[i*N+j] += K*K--2*__builtin_popcount(input[i*N+j]^filter[out*O+in]);
                }
            }
        }
        for(int i=0; i < M; ++i){              // rows 
            for(int j=0; j < N; ++j){          // columns 
                output[i*N+j] = signbit(output[i*N+j]);
            }
        }
    }
}

void float2bin_conv(Layer<float> & in_layer, Layer<binary16> & out_layer, int slice){
    int M = in_layer.output->dims[0];
    int N = in_layer.output->dims[1];
    int K = out_layer.weights->dims[0];
    int step = K/2;
    #pragma omp parallel for
    for (int out=0; out<out_layer.output->dims[2]; out++){
        binary16* output = out_layer.output->slice(out);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                output[i*N+j] = 0;
            }
        }
        for (int in=0; in<in_layer.output->dims[2]; in++){
    //        conv2d_bin_first(in_layer.output->slice(in), M, N, hold_output, out_layer.weights->slice(in, out), K, "zero");
            binary16* filter = out_layer.weights->slice(in, out);
            float* input = in_layer.output->slice(in, slice);
            int step = K/2;
            for(int i=0; i < M; ++i){              // rows 
                for(int j=0; j < N; ++j){          // columns 
                    for(int m=0; m < K; ++m){     // kernel rows 
                        int mm = K - 1 - m;      // row index of flipped kernel
                        for(int n=0; n < K; ++n){ // kernel columns 
                            int nn = K - 1 - n;  // column index of flipped kernel
                            // index of input signal, used for checking boundary
                            int ii = i + (m - step);
                            int jj = j + (n - step);
                            // ignore input samples which are out of bound
                            if( ii >= 0 && ii < M && jj >= 0 && jj < N ) {
                                output[i*N+j] += (binary16)(input[ii*N+jj] *(1<<10))*filter[mm*K+nn];
                            }
                        }
                    }
                }
            }
        }
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                output[i*N+j] = signbit(output[i*N+j]);
            }
        }
    }
}


void float2bin_conv(Layer<float> & in_layer, Layer<binary16> & out_layer){
    int M = in_layer.output->dims[0];
    int N = in_layer.output->dims[1];
    int K = out_layer.weights->dims[0];
    int step = K/2;
    #pragma omp parallel for
    for (int out=0; out<out_layer.output->dims[2]; out++){
        binary16* output = out_layer.output->slice(out);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                output[i*N+j] = 0;
            }
        }
        for (int in=0; in<in_layer.output->dims[2]; in++){
    //        conv2d_bin_first(in_layer.output->slice(in), M, N, hold_output, out_layer.weights->slice(in, out), K, "zero");
            binary16* filter = out_layer.weights->slice(in, out);
            float* input = in_layer.output->slice(in);
            int step = K/2;
            for(int i=0; i < M; ++i){              // rows 
                for(int j=0; j < N; ++j){          // columns 
                    for(int m=0; m < K; ++m){     // kernel rows 
                        int mm = K - 1 - m;      // row index of flipped kernel
                        for(int n=0; n < K; ++n){ // kernel columns 
                            int nn = K - 1 - n;  // column index of flipped kernel
                            // index of input signal, used for checking boundary
                            int ii = i + (m - step);
                            int jj = j + (n - step);
                            // ignore input samples which are out of bound
                            if( ii >= 0 && ii < M && jj >= 0 && jj < N ) {
                                output[i*N+j] += (binary16)(input[ii*N+jj] *(1<<10))*filter[mm*K+nn];
                            }
                        }
                    }
                }
            }
        }
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                output[i*N+j] = signbit(output[i*N+j]);
            }
        }
    }
}

void bin2reg_conv_prep(Layer<binary16> & in_layer, Layer<binary16> & out_layer){
    int M = in_layer.output->dims[0];
    int N = in_layer.output->dims[1];
    int O = in_layer.output->dims[2];
    int K = out_layer.remainder;
    int step = K/2;
    binary16* hold_output = new binary16[M*N];
    //#pragma omp parallel for
    for (int out=0; out<O; ++out){
        binary16* slice = in_layer.output->slice(out);
        for (int i=0; i<M; ++i){
            for (int j=0; j<N; ++j){
                int bit_counter = K*K-1;
                hold_output[i*N+j] = 0;
                for (int m=0; m<K; ++m){
                    for (int n=0; n<K; ++n){
                        int mm = i + m - step;
                        int nn = j + n - step;
                        if (mm >= 0 && nn >= 0 && mm < M && nn < N){
                            hold_output[i*N+j] |= slice[mm*N+nn] << bit_counter;
                        }
                        --bit_counter;
                    }
                }
            }
        }
        for (int i=0; i<M; ++i){
            for (int j=0; j<N; ++j){
                slice[i*N+j] = hold_output[i*N+j];
            }
        }
    }
    delete[] hold_output;
}

#endif
