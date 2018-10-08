#ifndef CONV_HPP
#define CONV_HPP

#include "src/types/types.hpp"
#include <vector>
#include <string>
#include <math.h>

template <typename T>
void conv2d(T* input, int M, int N, T* output, T* filter, int K, std::string padding){
    int step = K/2;
    if (padding == "zero"){
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						if( ii >= 0 && ii < M && jj >= 0 && jj < N )
							output[i*N+j] += input[ii*N+jj] * filter[mm*K+nn];
							//out[i][j] += img[ii][jj] * filter[mm][nn];
					}
				}
			}
		}
    }
    /*
    else if (padding == "repeat"){
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						//if( ii >= 0 && ii < M && jj >= 0 && jj < N )
						//	out[i][j] += img[ii][jj] * filter[mm][nn];
                        if (ii < 0){
                            if (jj < 0)
                                out[i][j] += img[0][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[0][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[0][jj] * filter[mm][nn];
                        }
                        else if (ii >= M){
                            if (jj < 0)
                                out[i][j] += img[M-1][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[M-1][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[M-1][jj] * filter[mm][nn];
                        }
                        else {
                            if (jj < 0)
                                out[i][j] += img[ii][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[ii][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[ii][jj] * filter[mm][nn];
                        }

					}
				}
			}
		}
    }
    else 
    {
        out.resize(M-2);
        for( int i = 0 ; i < M-2 ; i++ )
            out[i].resize(N-2);
		for(int i=1; i < M-1; ++i)              // rows
		{
			for(int j=1; j < N-1; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						if( ii >= 0 && ii < M && jj >= 0 && jj < N )
							out[i-1][j-1] += img[ii][jj] * filter[mm][nn];
					}
				}
			}
		}
    }
    */
}



template <typename T>
std::shared_ptr<Matrix<T>> conv2d(std::shared_ptr<Matrix<T>> img, std::shared_ptr<Matrix<T>> filter, std::string padding="zero")
{   //Image should be 3d matrix and filter  be 4d matrix.
    std::shared_ptr<Matrix<T>> out;
    std::vector<int> dims;
    int input_channels = img->dims[2];
    int output_channels = filter->dims[3];
    int rows = img->dims[0];
    int cols = img->dims[1];
    int filter_size = filter->dims[0];
    if (padding == "zero"){
        dims.push_back(rows);
        dims.push_back(cols);
        dims.push_back(output_channels);
    }
    out = Matrix<T>(dims);
    for (int i=0; i<output_channels*rows*cols; i++) {
        out->arr[i] = 0;
    }
    for (int i=0; i<output_channels; i++){
        for (int j=0; j<img->intput_channels; j++){
            conv2d(img->arr + img->index(0,0,i) , rows, cols, out->arr + out->index(0,0,i),
                filter->arr + filter->index(0,0,j,i), filter_size, padding);
        }
    }
    return out;
}


template <typename T>
std::vector<std::vector<T> > conv2d(std::vector<std::vector<T> > img, std::vector<std::vector<T> > filter, T bias, std::string padding="zero")
{
    int M = img.size();
    int N = img[0].size();
    int K = filter.size();
    int step = K/2;
    std::vector<std::vector<T> > out;
    if (padding == "zero"){
        out.resize(M);
        for( int i = 0 ; i < M ; i++ )
            out[i].resize(N);
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						if( ii >= 0 && ii < M && jj >= 0 && jj < N )
							out[i][j] += img[ii][jj] * filter[mm][nn];
					}
				}
                out[i][j] += bias;
			}
		}
    }
    else if (padding == "repeat"){
        out.resize(M);
        for( int i = 0 ; i < M ; i++ )
            out[i].resize(N);
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						//if( ii >= 0 && ii < M && jj >= 0 && jj < N )
						//	out[i][j] += img[ii][jj] * filter[mm][nn];
                        if (ii < 0){
                            if (jj < 0)
                                out[i][j] += img[0][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[0][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[0][jj] * filter[mm][nn];
                        }
                        else if (ii >= M){
                            if (jj < 0)
                                out[i][j] += img[M-1][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[M-1][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[M-1][jj] * filter[mm][nn];
                        }
                        else {
                            if (jj < 0)
                                out[i][j] += img[ii][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[ii][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[ii][jj] * filter[mm][nn];
                        }

					}
				}
                out[i][j] += bias;
			}
		}
    }
    else 
    {
        out.resize(M-2*step);
        for ( int i =0 ; i < M-2*step ; i++ )
            out[i].resize(N-2*step);
        for (int i = K / 2; i < M  - K / 2; ++i) // iterate through image
        {
          for (int j = K / 2; j < N - K / 2; ++j)
          {
            int sum = 0; // sum will be the sum of input data * coeff terms

            for (int ii = - K / 2; ii <= K / 2; ++ii) // iterate over kernel
            {
              for (int jj = - K / 2; jj <= K / 2; ++jj)
              {
                int data = img[i + ii][j +jj];
                int coeff = filter[ii + K / 2][jj + K / 2];

                sum += data * coeff;
              }
            }
            out[i-step][j-step] = sum + bias; // scale sum of convolution products and store in output
          }
        }
    }
    return out;
}


template <typename T>
std::vector<std::vector<T> > conv2d(std::vector<std::vector<std::vector<T> > > img, std::vector<std::vector<std::vector<T> > > filter, std::string padding="zero")
{
    int L = img.size();
    int M = img[0].size();
    int N = img[0][0].size();
    int K = filter.size();
    int step = K/2;
    std::vector<std::vector<T> > out(M, std::vector<T>(N, 0));
    if (padding == "zero"){
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);


						// ignore input samples which are out of bound
						if( ii >= 0 && ii < M && jj >= 0 && jj < N )
							out[i][j] += img[ii][jj] * filter[mm][nn];
					}
				}
			}
		}
    }
    else if (padding == "repeat"){
        out.resize(M);
        for( int i = 0 ; i < M ; i++ )
            out[i].resize(N);
		for(int i=0; i < M; ++i)              // rows
		{
			for(int j=0; j < N; ++j)          // columns
			{
				for(int m=0; m < K; ++m)     // kernel rows
				{
					int mm = K - 1 - m;      // row index of flipped kernel

					for(int n=0; n < K; ++n) // kernel columns
					{
						int nn = K - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
						int ii = i + (m - step);
						int jj = j + (n - step);

						// ignore input samples which are out of bound
						//if( ii >= 0 && ii < M && jj >= 0 && jj < N )
						//	out[i][j] += img[ii][jj] * filter[mm][nn];
                        if (ii < 0){
                            if (jj < 0)
                                out[i][j] += img[0][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[0][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[0][jj] * filter[mm][nn];
                        }
                        else if (ii >= M){
                            if (jj < 0)
                                out[i][j] += img[M-1][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[M-1][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[M-1][jj] * filter[mm][nn];
                        }
                        else {
                            if (jj < 0)
                                out[i][j] += img[ii][0] * filter[mm][nn];
                            else if (jj >= N)
                                out[i][j] += img[ii][N-1] * filter[mm][nn];
                            else
                                out[i][j] += img[ii][jj] * filter[mm][nn];
                        }

					}
				}
			}
		}
    }
    else 
    {
        out.resize(M-2*step);
        for ( int i =0 ; i < M-2*step ; i++ )
            out[i].resize(N-2*step);
        for (int i = K / 2; i < M  - K / 2; ++i) // iterate through image
        {
          for (int j = K / 2; j < N - K / 2; ++j)
          {
            int sum = 0; // sum will be the sum of input data * coeff terms

            for (int ii = - K / 2; ii <= K / 2; ++ii) // iterate over kernel
            {
              for (int jj = - K / 2; jj <= K / 2; ++jj)
              {
                int data = img[i + ii][j +jj];
                int coeff = filter[ii + K / 2][jj + K / 2];

                sum += data * coeff;
              }
            }
            out[i-step][j-step] = sum; // scale sum of convolution products and store in output
          }
        }
    }
    return out;
}

#endif
