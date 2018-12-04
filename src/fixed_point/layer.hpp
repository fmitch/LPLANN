#ifndef FIXED_LAYER_HPP
#define FIXED_LAYER_HPP

#include <vector>
#include "src/types/types.hpp"
#include "src/construction/network.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include <string>
#include <map>
#include <math.h>
#include <cassert>

template <>
void Layer<fixed>::internal_load_weights(std::vector<float>* weight_pointer, std::vector<size_t> dims){
    std::vector<float> w = *weight_pointer;
    switch (op_int){
        case CONV2D:
            for (int m=0; m < dims[3]; m++){  //Output channels
                for (int l=0; l < dims[2]; l++){  //Input channels
                    for (int k=0; k < dims[1]; k++){ 
                        for (int j=0; j < dims[0]; j++){ 
                            fixed tmp = (fixed) round( w[j*dims[3]*dims[2]+k*dims[3]*dims[2]*dims[1]+l*dims[3]+m]  * (1 << this.remainder));
                            weights->arr[weights->index(j,k,l,m)] = tmp;
                        }
                    }
                }
            }
            break;
        case MULTIPLY:
            for (int k=0; k<dims[1]; k++){
                for (int j=0; j<dims[0]; j++){
                    bool bit = signbit(w[ j*dims[1] + k]);
                    fixed tmp = (fixed) round( w[k*weights->dims[0] + j] * (1 << this.remainder));
                    weights->arr[weights->index(j,k)] = tmp;
                }
            }
            break;
    }
}

template <>
void Layer<fixed>::load_weights(std::string filename){
    cnpy::NpyArray w_npy = cnpy::npy_load(filename);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(w_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer, w_npy.shape);
}

template <>
void Layer<fixed>::load_weights(std::string filename, std::string varname){
    cnpy::NpyArray w_npy = cnpy::npz_load(filename, varname);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(w_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer, w_npy.shape);
}

template <>
void Layer<fixed>::load_weights(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    internal_load_weights(weight_pointer, it->second.shape);
}

template <>
void Layer<fixed>::load_weights(std::shared_ptr<Matrix<fixed>> mat){
    weights = mat;
}

template <>
void Layer<fixed>::load_bias(std::string filename){
    cnpy::NpyArray bias_npy = cnpy::npy_load(filename);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = (fixed) round( b[j]  * (1 << this.remainder));
    }
}

template <>
void Layer<fixed>::load_bias(std::string filename, std::string varname){
    cnpy::NpyArray bias_npy = cnpy::npz_load(filename, varname);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = (fixed) round( b[j]  * (1 << this.remainder));
    }
}
template <>
void Layer<fixed>::load_bias(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = (fixed) round( b[j]  * (1 << this.remainder));
    }
}





#endif
