#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include "src/types/types.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include <string>
#include <map>
#define uchar int

class Layer {
    //std::map<std::string, std::string> string_args;
    //std::map<std::string, int> int_args;
  public:
    uchar id;
    uchar input_id;
    uchar input_precision;
    uchar output_precision;
    std::string operation;
    std::shared_ptr<Matrix<float>> weights;
    std::shared_ptr<Matrix<float>> bias;
    std::shared_ptr<Matrix<float>> fc_weights;
    std::map<std::string, std::string> string_args;
    std::map<std::string, int> int_args;
    void set_weights(std::shared_ptr<Matrix<float>> new_weights){ weights = new_weights; }
    void set_bias(std::shared_ptr<Matrix<float>> new_bias){ bias = new_bias; }
    void set_fc_weights(std::shared_ptr<Matrix<float>> new_fc_weights){ fc_weights = new_fc_weights;}
    void set_params(int _id, int _in_id, int _i_p, int _o_p, std::string op){
        id = _id;
        input_id = _in_id;
        input_precision = _i_p;
        output_precision = _o_p;
        operation = op;;
    }
    void add_string_arg(std::string label, std::string value){
        string_args[label] = value;
    }
    void add_int_arg(std::string label, int value){
        int_args[label] = value;
    }
};

template <typename T>
class Input {
    //uchar input_precision;
  public:
    std::string data_type;
    std::shared_ptr<Matrix<T>> data;
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
        return data->slice(index);
    }

    Input(std::string filename){
        cnpy::NpyArray img_npy = cnpy::npy_load(filename);
        auto img_pointer = reinterpret_cast<std::vector<T>*>(&(img_npy.data_holder.get() )[0]);
        std::vector<T> img_vec = *img_pointer;
        std::vector<int> d;
        for (int i=0; i<img_npy.shape.size(); i++){
            d.push_back(img_npy.shape[i]);
        }
        fix_dims(d);
        std::shared_ptr<Matrix<T>> new_data(new Matrix<T>(d));
        for (int j=0; j<d[0]; j++){ //Num of images
            for (int k=0; k<d[1]; k++){ //X
                for (int l=0; l<d[2]; l++){ //Y
                    for (int m=0; m<d[3]; m++){ //Channels
                        new_data->arr[new_data->index(j,k,l,m)] = img_vec[new_data->index(j,k,l,m)];
                    }
                }
            }
        }
        new_data->dims = {d[1],d[2],d[3],d[0]};
        data = new_data;
    }
    void set_params(std::string _d_t){
        data_type = _d_t; 
    }
};

class Network {
    //std::vector<Layer> Layers;
  public:
    uchar num_classes;
    void load_weights();
    std::vector<Layer> Layers; //SHOULD BE PRIVATE
    Network(std::string);
};


#endif
