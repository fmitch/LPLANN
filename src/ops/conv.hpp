#ifndef CONV_HPP
#define CONV_HPP

#include "src/types/types.hpp"
#include <vector>
#include <string>
#include <math.h>

#include <iostream>

template <typename T1, typename T2>
void conv2d(T1* input, int M, int N, T2* output, T2* filter, int K, std::string padding){
    int step = K/2;
    if (padding == "zero"){
		for(int i=0; i < M; ++i) {             // rows
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
							output[i*N+j] = output[i*N+j] + input[ii*N+jj] * filter[mm*K+nn];
                        }
					}
				}
			}
		}
    }
    else if (padding == "repeat"){
		for(int i=0; i < M; ++i) {             // rows
			for(int j=0; j < N; ++j) {         // columns
				for(int m=0; m < K; ++m){     // kernel rows
					int mm = K - 1 - m;      // row index of flipped kernel
					for(int n=0; n < K; ++n){ // kernel columns
						int nn = K - 1 - n;  // column index of flipped kernel
						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);
						// repeat input samples which are out of bound
                        if (ii < 0){
                            if (jj < 0)
                                output[i*N+j] = output[i*N+j] +  input[0] * filter[mm*K+nn];
                            else if (jj >= N)
                                output[i*N+j] = output[i*N+j] +  input[N-1] * filter[mm*K+nn];
                            else
                                output[i*N+j] = output[i*N+j] +  input[jj] * filter[mm*K+nn];
                        }
                        else if (ii >= M){
                            if (jj < 0)
                                output[i*N+j] = output[i*N+j] +  input[(M-1)*N] * filter[mm*K+nn];
                            else if (jj >= N)
                                output[i*N+j] = output[i*N+j] +  input[(M-1)*N+N-1] * filter[mm*K+nn];
                            else
                                output[i*N+j] = output[i*N+j] +  input[(M-1)*N+jj] * filter[mm*K+nn];
                        }
                        else {
                            if (jj < 0)
                                output[i*N+j] = output[i*N+j] +  input[ii*N] * filter[mm*K+nn];
                            else if (jj >= N)
                                output[i*N+j] = output[i*N+j] +  input[ii*N+N-1] * filter[mm*K+nn];
                            else
                                output[i*N+j] = output[i*N+j] +  input[ii*N+jj] * filter[mm*K+nn];
                        }
					}
				}
			}
		}
    }
}

#endif
