#ifndef BINARY_HPP
#define BINARY_HPP

#include <vector>
#include "src/types/types.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include <string>
#include <map>
#include <math.h>
#include <cassert>

typedef uint16_t binary16;
typedef uint64_t binary64;

template <>
class Layer<binary16> {
  public:
    int op_int;
    bool has_bias;
    std::shared_ptr<Matrix<binary16>> output;
    std::shared_ptr<Matrix<binary16>> weights;
    std::shared_ptr<Matrix<binary16>> bias;
    void internal_load_weights(std::vector<float>* weight_pointer);
    void load_weights(std::string filename);
    void load_weights(std::string filename, std::string varname);
    void load_weights(std::map<std::string, cnpy::NpyArray>::iterator it);
    void load_weights(std::shared_ptr<Matrix<binary16>> mat);
    void load_bias(std::string filename);
    void load_bias(std::string filename, std::string varname);
    void load_bias(std::map<std::string, cnpy::NpyArray>::iterator it);
    void load_bias(std::shared_ptr<Matrix<binary16>> mat);
    Layer(std::vector<int> &prev_dimensions, int op, std::vector<int> op_dimensions, bool is_bias=true);
};

template <>
void Layer<binary16>::internal_load_weights(std::vector<float>* weight_pointer){
    std::vector<float> w = *weight_pointer;
    switch (op_int){
        case CONV2D:
            std::vector<int> dims = {w_npy.shape[0], w_npy.shape[1], w_npy.shape[2], w_npy.shape[3]}; 
            for (int m=0; m < dims[3]; m++){  //Output channels
                for (int l=0; l < dims[2]; l++){  //Input channels
                    int count = 0; 
                    for (int k=0; k < dims[1]; k++){ 
                        for (int j=0; j < dims[0]; j++){ 
                            bool bit = signbit( w[j*dims[3]*dims[2]+k*dims[3]*dims[2]*dims[1]+l*dims[3]+m] );
                            // 0 bit represents positive 1, 1 bit represents -1
                            weights->arr[weights->index(l,m)] |= bit << count;
                            count++; //Row major, LSB is first (top left)
                        }
                    }
                }
            }
            break;
        case MULTIPLY:
            for (int k=0; k<weights->dims[1]; k++){ 
                int sixteen_count = 0; //Every new column starts over
                for (int j=0; j<weights->dims[0]; j++){ 
                    bool bit = signbit(w[ k*weights->dims[0] + j]);
                    weights->arr[weights->index(j,k)] = bit << sixteen_count; //LSB is first
                    sixteen_count = (sixteen_count + 1) % 16;
                }
            }
            break;
    }
}

template <>
void Layer<binary16>::load_weights(std::string filename){
    cnpy::NpyArray w_npy = cnpy::npy_load(filename);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(w_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer)
}

template <>
void Layer<binary16>::load_weights(std::string filename, std::string varname){
    cnpy::NpyArray w_npy = cnpy::npz_load(filename, varname);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(w_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer)
}

template <binary16>
void Layer<binary16>::load_weights(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    internal_load_weights(weight_pointer)
}

template <>
void Layer<binary16>::load_weights(std::shared_ptr<Matrix<binary16>> mat){
    weights = mat;
}

template <>
void Layer<binary16>::load_bias(std::string filename){
    cnpy::NpyArray bias_npy = cnpy::npy_load(filename);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}

template <>
void Layer<binary16>::load_bias(std::string filename, std::string varname){
    cnpy::NpyArray bias_npy = cnpy::npz_load(filename, varname);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}
template <>
void Layer<binary16>::load_bias(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}
template <>
void Layer<binary16>::load_bias(std::shared_ptr<Matrix<binary16>> mat){
    bias.reset(mat);
}

template <>
Layer<binary16>::Layer(std::vector<int> & prev_dimensions, int op, std::vector<int> op_dimensions, bool is_bias){
    assert(op_dimensions[0] * op_dimensions[1] < 16);
    has_bias = is_bias;
    op_int = op;
    std::vector<int> output_dims;
    std::vector<int> weight_dims;
    switch (op_int){
        case CONV2D:
            output_dims.push_back(prev_dimensions[0]);
            output_dims.push_back(prev_dimensions[1]);
            output_dims.push_back(op_dimensions.back());
            //operation = conv2d_wrapper; //WRAPPER

            weight_dims.push_back(prev_dimensions[2]);
            weight_dims.push_back(op_dimensions.back());
            weights.reset(new Matrix<binary16>(weight_dims));
            if (is_bias){
                bias.reset(new Matrix<binary16>(output_dims.back()));
            }
            break;
        case POOL:
            output_dims.push_back(prev_dimensions[0]/op_dimensions[0]);
            output_dims.push_back(prev_dimensions[1]/op_dimensions[1]);
            output_dims.push_back(prev_dimensions.back());
            //operation = pool_wrapper; //WRAPPER
            break;
        case MULTIPLY:
            int flat_size;
            if (prev_dimensions.size() != 1){ 
                flat_size = prev_dimensions[0]*prev_dimensions[1]*prev_dimensions[2];
            } else {
                flat_size = prev_dimensions[0];
            }
            int shorts_per_column = (flat_size + 16 - 1) / 16; //Fast ceiling
            output_dims.push_back(op_dimensions[0]);
            weight_dims.push_back(shorts_per_column);
            weight_dims.push_back(op_dimensions[0]);
            weights.reset(new Matrix<binary16>(weight_dims));
            if (is_bias){
                bias.reset(new Matrix<binary16>(output_dims.back()));
            }
            break;
            /*
        case RELU:
            for (int i=0; i < prev_dimensions.size(); i++){
                output_dims.push_back(prev_dimensions[i]);
            }
            break;
            */
    }
    output.reset(new Matrix<binary16>(output_dims));
    prev_dimensions = output_dims;
    return;
}

#endif
