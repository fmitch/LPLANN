#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "src/open_source/jsoncpp/json.h"
#include "src/open_source/jsoncpp/json-forwards.h"
#include "src/open_source/jsoncpp/jsoncpp.cpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include "src/types/types.hpp"



<template T, template prevT>
Layer::Layer(int operation, std::vector<int> dims, Layer<prevT> prev_layer){
    cnpy::npz_t weights_npy = cnpy::npz_load(model_file);

        //Set number of layers
        int num_layers = val["network"]["layers"].size();
        // SHOULD CHECK IF NUM LAYERS == NPZ SIZE
        Layers.resize(num_layers);
        
        //Layers
        auto it = weights_npy.begin();
        for( int i = 0; i < num_layers; i++){
            int id = val["network"]["layers"][i]["id"].asInt();
            int input_id = val["network"]["layers"][i]["input_id"].asInt();
            int input_precision = val["network"]["layers"][i]["input_precision"].asInt();
            int output_precision = val["network"]["layers"][i]["output_precision"].asInt();
            std::string operation = val["network"]["layers"][i]["operation"].asString();
            Layers[i].set_params(id, input_id, input_precision, output_precision, operation);
            //Accept layer parameters

            //WRITE CODE TO READ IN PARAMETERS. ASSUME I'VE SET UP SOME BORING BINARY STUFF.
            if (operation == "conv"){
                std::string padding = val["network"]["layers"][i]["args"]["padding"].asString();
                Layers[i].add_string_arg("padding", padding);
                int filterX = val["network"]["layers"][i]["args"]["filterX"].asInt();
                Layers[i].add_int_arg("filterX", filterX);
                int filterY = val["network"]["layers"][i]["args"]["filterY"].asInt();
                Layers[i].add_int_arg("filterY", filterY);
                int num_filters = val["network"]["layers"][i]["args"]["num_filters"].asInt();
                Layers[i].add_int_arg("num_filters", num_filters);
                bool bias = val["network"]["layers"][i]["args"]["bias"].asBool();
                Layers[i].add_int_arg("bias", bias);
                auto filter_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                std::vector<float> filter = *filter_pointer;
                std::vector<int> dims;
                dims.push_back(it->second.shape[0]); //Filter x
                dims.push_back(it->second.shape[1]); //Filter y
                dims.push_back(it->second.shape[2]); //Input channels
                dims.push_back(it->second.shape[3]); //Output channels
                std::shared_ptr<Matrix<T>> new_weights(new Matrix<T>(dims));
                char* arr_pointer = (char*) new_weights->arr;
                for (int m=0; m<dims[3]; m++){ //Output channels
                    for (int l=0; l<dims[2]; l++){//Input channels
                        for (int k=0; k<dims[1]; k++){ //Filter y
                            for (int j=0; j<dims[0]; j++){ //Filter x
                                new_weights->arr[new_weights->index(j,k,l,m)] = 
                                    filter[ j*dims[3]*dims[2] + k*dims[3]*dims[2]*dims[1] + l*dims[3] + m ];
                            }
                        }
                    }
                }
                Layers[i].set_weights(new_weights);

                std::vector<int> out_dims = {input_width, input_height, dims[3] };
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(out_dims);
                Layers[i].set_output(out);
                
                if (bias){
                    it++;
                    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                    std::vector<float> bias_vec = *bias_pointer;
                    std::vector<int> bias_dims; 
                    bias_dims.push_back(it->second.shape[0]);
                    std::shared_ptr<Matrix<T>> new_bias(new Matrix<T>(bias_dims));
                    for (int j=0; j<bias_dims[0]; j++){
                        new_bias->arr[j] = bias_vec[j];
                    }
                    Layers[i].set_bias(new_bias);
                }
                it++;
            }
            else if(operation == "pool"){
                std::string pooling = val["network"]["layers"][i]["args"]["pooling"].asString();
                Layers[i].add_string_arg("pooling", pooling);
                int pool_size = val["network"]["layers"][i]["args"]["pool_size"].asInt();
                Layers[i].add_int_arg("filterX", pool_size);
                input_width /= pool_size;
                input_height /= pool_size;
                int stride = val["network"]["layers"][i]["args"]["stride"].asInt();
                Layers[i].add_int_arg("stride", stride);
                std::vector<int> out_dims = {input_width, input_height, Layers[i-1].output->dims.back()};
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(out_dims);
                Layers[i].set_output(out);
            }
            else if(operation == "relu"){
            }
            else if(operation == "softmax"){
            }
            else if(operation == "multiply"){
                bool bias = val["network"]["layers"][i]["args"]["bias"].asBool();
                Layers[i].add_int_arg("bias", bias);
                auto fc_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                std::vector<float> fc = *fc_pointer;
                std::vector<int> dims;
                dims.push_back(it->second.shape[0]); //x
                dims.push_back(it->second.shape[1]); //y
                std::shared_ptr<Matrix<T>> new_fc(new Matrix<T>(dims));
                for (int k=0; k<dims[1]; k++){ //5
                    for (int j=0; j<dims[0]; j++){ //5
                        new_fc->arr[new_fc->index(j,k)] = fc[ k*dims[0] + j];
                    }
                }
                Layers[i].set_weights(new_fc);
                if (bias){
                    it++;
                    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                    std::vector<float> bias_vec = *bias_pointer;
                    std::shared_ptr<Matrix<T>> new_bias(new Matrix<T>(it->second.shape[0]));
                    for (int j=0; j<bias_dims[0]; j++){
                        new_bias->arr[j] = bias_vec[j];
                    }
                    Layers[i].set_bias(new_bias);
                }
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(it->second.shape[0]);
                Layers[i].set_output(out);
                it++;
            }
        }

<template T>
UniformNetwork::UniformNetwork(std::string filename){
    std::ifstream config_doc(filename, std::ifstream::binary);
    Json::Value val;
    Json::Reader reader;
    bool b = reader.parse(config_doc, val);
    if (b){
        //Set input 
        std::string model_file = val["network"]["model_file"].asString();
        int input_width = val["network"]["input"]["width"].asInt();
        int input_height = val["network"]["input"]["height"].asInt();
        int input_channels = val["network"]["input"]["channels"].asInt();
        int num_classes = val["network"]["num_classes"].asInt();
        std::string data_type = val["network"]["input"]["data_type"].asString();
        //input.set_params(data_type);

        cnpy::npz_t weights_npy = cnpy::npz_load(model_file);

        //Set number of layers
        int num_layers = val["network"]["layers"].size();
        // SHOULD CHECK IF NUM LAYERS == NPZ SIZE
        Layers.resize(num_layers);
        
        //Layers
        auto it = weights_npy.begin();
        for( int i = 0; i < num_layers; i++){
            int id = val["network"]["layers"][i]["id"].asInt();
            int input_id = val["network"]["layers"][i]["input_id"].asInt();
            int input_precision = val["network"]["layers"][i]["input_precision"].asInt();
            int output_precision = val["network"]["layers"][i]["output_precision"].asInt();
            std::string operation = val["network"]["layers"][i]["operation"].asString();
            Layers[i].set_params(id, input_id, input_precision, output_precision, operation);
            //Accept layer parameters

            //WRITE CODE TO READ IN PARAMETERS. ASSUME I'VE SET UP SOME BORING BINARY STUFF.
            if (operation == "conv"){
                std::string padding = val["network"]["layers"][i]["args"]["padding"].asString();
                Layers[i].add_string_arg("padding", padding);
                int filterX = val["network"]["layers"][i]["args"]["filterX"].asInt();
                Layers[i].add_int_arg("filterX", filterX);
                int filterY = val["network"]["layers"][i]["args"]["filterY"].asInt();
                Layers[i].add_int_arg("filterY", filterY);
                int num_filters = val["network"]["layers"][i]["args"]["num_filters"].asInt();
                Layers[i].add_int_arg("num_filters", num_filters);
                bool bias = val["network"]["layers"][i]["args"]["bias"].asBool();
                Layers[i].add_int_arg("bias", bias);
                auto filter_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                std::vector<float> filter = *filter_pointer;
                std::vector<int> dims;
                dims.push_back(it->second.shape[0]); //Filter x
                dims.push_back(it->second.shape[1]); //Filter y
                dims.push_back(it->second.shape[2]); //Input channels
                dims.push_back(it->second.shape[3]); //Output channels
                std::shared_ptr<Matrix<T>> new_weights(new Matrix<T>(dims));
                char* arr_pointer = (char*) new_weights->arr;
                for (int m=0; m<dims[3]; m++){ //Output channels
                    for (int l=0; l<dims[2]; l++){//Input channesl
                        for (int k=0; k<dims[1]; k++){ //Filter y
                            for (int j=0; j<dims[0]; j++){ //Filter x
                                new_weights->arr[new_weights->index(j,k,l,m)] = filter[ 
                                    j*dims[3]*dims[2] + k*dims[3]*dims[2]*dims[1] + l*dims[3] + m ];
                            }
                        }
                    }
                }
                Layers[i].set_weights(new_weights);

                std::vector<int> out_dims = {input_width, input_height, dims[3] };
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(out_dims);
                Layers[i].set_output(out);
                
                if (bias){
                    it++;
                    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                    std::vector<float> bias_vec = *bias_pointer;
                    std::vector<int> bias_dims; 
                    bias_dims.push_back(it->second.shape[0]);
                    std::shared_ptr<Matrix<T>> new_bias(new Matrix<T>(bias_dims));
                    for (int j=0; j<bias_dims[0]; j++){
                        new_bias->arr[j] = bias_vec[j];
                    }
                    Layers[i].set_bias(new_bias);
                }
                it++;
            }
            else if(operation == "pool"){
                std::string pooling = val["network"]["layers"][i]["args"]["pooling"].asString();
                Layers[i].add_string_arg("pooling", pooling);
                int pool_size = val["network"]["layers"][i]["args"]["pool_size"].asInt();
                Layers[i].add_int_arg("filterX", pool_size);
                input_width /= pool_size;
                input_height /= pool_size;
                int stride = val["network"]["layers"][i]["args"]["stride"].asInt();
                Layers[i].add_int_arg("stride", stride);
                std::vector<int> out_dims = {input_width, input_height, Layers[i-1].output->dims.back()};
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(out_dims);
                Layers[i].set_output(out);
            }
            else if(operation == "relu"){
            }
            else if(operation == "softmax"){
            }
            else if(operation == "multiply"){
                bool bias = val["network"]["layers"][i]["args"]["bias"].asBool();
                Layers[i].add_int_arg("bias", bias);
                auto fc_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                std::vector<float> fc = *fc_pointer;
                std::vector<int> dims;
                dims.push_back(it->second.shape[0]); //x
                dims.push_back(it->second.shape[1]); //y
                std::shared_ptr<Matrix<T>> new_fc(new Matrix<T>(dims));
                for (int k=0; k<dims[1]; k++){ //5
                    for (int j=0; j<dims[0]; j++){ //5
                        new_fc->arr[new_fc->index(j,k)] = fc[ k*dims[0] + j];
                    }
                }
                Layers[i].set_weights(new_fc);
                if (bias){
                    it++;
                    auto bias_pointer = reinterpret_cast<std::vector<float>*>(&(it->second.data_holder.get() )[0]);
                    std::vector<float> bias_vec = *bias_pointer;
                    std::shared_ptr<Matrix<T>> new_bias(new Matrix<T>(it->second.shape[0]));
                    for (int j=0; j<bias_dims[0]; j++){
                        new_bias->arr[j] = bias_vec[j];
                    }
                    Layers[i].set_bias(new_bias);
                }
                std::shared_ptr<Matrix<T>> out(new Matrix<T>(it->second.shape[0]);
                Layers[i].set_output(out);
                it++;
            }
        }
    }
    else{
        std::cout << "Error: Could not read config file.\n";
        exit(0);
    }
}
