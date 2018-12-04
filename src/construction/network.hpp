#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "src/types/types.hpp"
#include "src/types/matrix.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include <string>
#include <map>

template <typename T>
class Layer {
  public:
    int op_int;
    bool has_bias;
    int remainder;
    //void (*operation)(Layer<inT, inT>&, Layer<T, T>&, bool);
    std::shared_ptr<Matrix<T>> output;
    std::shared_ptr<Matrix<T>> weights;
    std::shared_ptr<Matrix<T>> bias;
    void internal_load_weights(std::vector<float>* weight_pointer, std::vector<size_t> dims);
    void load_weights(std::string filename);
    void load_weights(std::string filename, std::string varname);
    void load_weights(std::map<std::string, cnpy::NpyArray>::iterator it);
    void load_weights(std::shared_ptr<Matrix<T>> mat);
    void load_bias(std::string filename);
    void load_bias(std::string filename, std::string varname);
    void load_bias(std::map<std::string, cnpy::NpyArray>::iterator it);
    void load_bias(std::shared_ptr<Matrix<T>> mat);
    Layer(std::vector<int> &prev_dimensions, int op, std::vector<int> op_dimensions, bool is_bias=true);
    Layer(){}
};

template <typename T>
void Layer<T>::internal_load_weights(std::vector<float>* weight_pointer, std::vector<size_t>dims){
    std::vector<float> w = *weight_pointer;
    switch (op_int){
        case CONV2D:
            for (int m=0; m<weights->dims[3]; m++){ 
                for (int l=0; l<weights->dims[2]; l++){ 
                    for (int k=0; k<weights->dims[1]; k++){ 
                        for (int j=0; j<weights->dims[0]; j++){ 
                            weights->arr[weights->index(j,k,l,m)] = w[j*weights->dims[3]*weights->dims[2] + k*weights->dims[3]*weights->dims[2]*weights->dims[1] + l*weights->dims[3] + m];
                        }
                    }
                }
            }
            break;
        case MULTIPLY:
            for (int k=0; k<weights->dims[1]; k++){ 
                for (int j=0; j<weights->dims[0]; j++){ 
                    weights->arr[weights->index(j,k)] = w[ k*weights->dims[0] + j];
                }
            }
            break;
    }
}

template <typename T>
void Layer<T>::load_weights(std::string filename){
    cnpy::NpyArray weights_npy = cnpy::npy_load(filename);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(weights_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer, weights_npy.shape);
}
template <typename T>
void Layer<T>::load_weights(std::string filename, std::string varname){
    cnpy::NpyArray weights_npy = cnpy::npz_load(filename, varname);
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(weights_npy.data_holder.get())[0]);
    internal_load_weights(weight_pointer, weights_npy.shape);
}

template <typename T>
void Layer<T>::load_weights(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto weight_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    internal_load_weights(weight_pointer, it->second.shape);
}

template <typename T>
void Layer<T>::load_weights(std::shared_ptr<Matrix<T>> mat){
    weights  = mat;
}

template <typename T>
void Layer<T>::load_bias(std::string filename){
    cnpy::NpyArray bias_npy = cnpy::npy_load(filename);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}

template <typename T>
void Layer<T>::load_bias(std::string filename, std::string varname){
    cnpy::NpyArray bias_npy = cnpy::npz_load(filename, varname);
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(bias_npy.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}
template <typename T>
void Layer<T>::load_bias(std::map<std::string, cnpy::NpyArray>::iterator it){
    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get())[0]);
    std::vector<float> b = *bias_pointer;
    for (int j=0; j<weights->dims.back(); j++){ 
        bias->arr[j] = b[j];
    }
}

template <typename T>
void Layer<T>::load_bias(std::shared_ptr<Matrix<T>> mat){
    bias.reset(mat);
}

template <typename T>
Layer<T>::Layer(std::vector<int> & prev_dimensions, int op, std::vector<int> op_dimensions, bool is_bias){
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

            weight_dims.push_back(op_dimensions[0]);
            weight_dims.push_back(op_dimensions[1]);
            weight_dims.push_back(prev_dimensions[2]);
            weight_dims.push_back(op_dimensions.back());
            weights.reset(new Matrix<T>(weight_dims));
            if (is_bias){
                bias.reset(new Matrix<T>(output_dims.back()));
            }
            break;
        case POOL:
            output_dims.push_back(prev_dimensions[0]/op_dimensions[0]);
            output_dims.push_back(prev_dimensions[1]/op_dimensions[1]);
            output_dims.push_back(prev_dimensions.back());
            //operation = pool_wrapper; //WRAPPER
            break;
        case MULTIPLY:
        {
            int flat_size;
            if (prev_dimensions.size() != 1){ //If not a flat matrix, flatten.
                flat_size = prev_dimensions[0]*prev_dimensions[1]*prev_dimensions[2];
            } else {
                flat_size = prev_dimensions[0];
            }
            output_dims.push_back(op_dimensions[0]);
            //operation = fc_wrapper; //WRAPPER
            weight_dims.push_back(flat_size);
            weight_dims.push_back(op_dimensions[0]);
            weights.reset(new Matrix<T>(weight_dims));
            if (is_bias){
                bias.reset(new Matrix<T>(output_dims.back()));
            }
            break;
        }
        case FLATTEN:
        {
            int flat_size;
            if (prev_dimensions.size() != 1){
                flat_size = prev_dimensions[0]*prev_dimensions[1]*prev_dimensions[2];
            } else {
                flat_size = prev_dimensions[0];
            }
            output_dims.push_back(flat_size);
            break;
        }
        case ACTIVATION:
            for (int i=0; i < prev_dimensions.size(); i++){
                output_dims.push_back(prev_dimensions[i]);
            }
            //operation = relu_wrapper; //WRAPPER
            break;
    }
    output.reset(new Matrix<T>(output_dims));
    prev_dimensions = output_dims;
    return;
}

template <typename T>
class Input: public Layer<T> {
  public:
    void fix_dims(std::vector<int> &d){
        if (d.size() == 2){
            d.insert( d.begin(), 1);
            d.push_back(1);
        }
        else if (d.size() == 3){
            if (d.back() < 4){ //This assumes image input is larger than 3 by 3, and at most 3
                d.insert( d.begin(), 1);
            }
            else{
                d.push_back(1);
            }
        } 
    }

    T* slice(int index){
        return this->output->slice(index);
    }

    Input(std::vector<int> dims, int num_images):Layer<T>(){
        std::vector<int> dis = {dims[0],dims[1],dims[2], num_images};
        this->output.reset(new Matrix<T>(dis));
    }

    void load_data(std::string filename, bool is_bias){
        cnpy::NpyArray img_npy = cnpy::npy_load(filename);
        auto img_pointer = reinterpret_cast<std::vector<float>*>(&(img_npy.data_holder.get() )[0]);
        std::vector<float> img_vec = *img_pointer;
        std::vector<int> d = this->output->dims;
        if (is_bias){
            this->bias.reset(new Matrix<T>(this->output->dims.back()));
        }
        for (int j=0; j<d[0]; j++){ //Num of images
            for (int k=0; k<d[1]; k++){ //X
                for (int l=0; l<d[2]; l++){ //Y
                    for (int m=0; m<d[3]; m++){ //Channels
                        this->output->arr[this->output->index(j,k,l,m)] = img_vec[this->output->index(j,k,l,m)];
                    }
                }
            }
        }
    }
    /*
    Input(std::string filename, bool is_bias):Layer<T>(){
        cnpy::NpyArray img_npy = cnpy::npy_load(filename);
        auto img_pointer = reinterpret_cast<std::vector<float>*>(&(img_npy.data_holder.get() )[0]);
        std::vector<float> img_vec = *img_pointer;
        std::vector<int> d;
        for (int i=0; i<img_npy.shape.size(); i++){
            d.push_back(img_npy.shape[i]);
        }
        fix_dims(d);
        this->output.reset(new Matrix<T>(d));
        if (is_bias){
            this->bias.reset(new Matrix<T>(d.back()));
        }
        for (int j=0; j<d[0]; j++){ //Num of images
            for (int k=0; k<d[1]; k++){ //X
                for (int l=0; l<d[2]; l++){ //Y
                    for (int m=0; m<d[3]; m++){ //Channels
                        this->output->arr[this->output->index(j,k,l,m)] = img_vec[this->output->index(j,k,l,m)];
                    }
                }
            }
        }
        this->output->dims = {d[1],d[2],d[3],d[0]};
    }
    */
};

/*
template <typename T>
class UniformNetwork {
    //std::vector<Layer> Layers;
    void initialize_output();
  public:
    void load_weights();
    std::vector<Layer<T>> Layers; //SHOULD BE PRIVATE
    Input
    void forward(Input);
    UniformNetwork(std::string);
};
*/

class NetworkBuilder{
    std::vector<int> current_input_dims;
    int prev_dtype;
};


#endif
