#include <iostream>
#include <map>
#include <stdexcept>
#include "src/types/types.hpp"
#include "src/ops/conv.hpp"
#include "src/ops/print.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include "src/construction/network.hpp"
#include "src/ops/print.hpp"
//#include "src/ops/test.hpp"
#include <vector>
#include <string>

int main(){

    Network net("example.json");
    Input<float> input("train_images.npy");
    std::cout << input.data->dims[0] << "  ";
    std::cout << input.data->dims[1] << "  ";
    std::cout << input.data->dims[2] << "  ";
    std::cout << input.data->dims[3] << "  ";
    std::vector<int> conv1_dims = { input.data->dims[0], input.data->dims[1], 
                net.Layers[0].weights->dims[3]};
    Matrix<float> conv1(conv1_dims);
    for (int out=0; out<1; out++){//net.Layers[0].weights->dims[3]; i++){
        for (int in=0; in<1; in++){//net.Layers[0].weights->dims[3]; i++){
            conv2d(input.slice(in), input.data->dims[0], input.data->dims[1], conv1.slice(out), 
                    net.Layers[0].weights->slice(out), net.Layers[0].weights->dims[0], "zero");
        }
    }

    return 0;


    //Load images into img1 and img2. 
    /*
    cnpy::NpyArray img_npy = cnpy::npy_load("train_images.npy");
    for (int i = 0; i < img_npy.shape.size(); i++) {
        std::cout << img_npy.shape[i] << std::endl;
    }
    auto point = reinterpret_cast<std::vector<double>*>(&( img_npy.data_holder.get() )[0]);
    std::vector<double> images = *point;

    std::vector<std::vector<float>> img1(28);
    std::vector<std::vector<float>> img2(28);
    for (int i=0; i<28; i++) {
        img1[i].resize(28);
        img2[i].resize(28);
        for (int j=0; j<28; j++) {
            img1[i][j] = images[i*28 + j];
            std::cout << img1[i][j] << " " ;
            img2[i][j] = images[784 + i*28 + j];
        }
    }

    // Load filters into filter object.
    cnpy::npz_t filters_npy = cnpy::npz_load("full.npz");

    auto point1 = reinterpret_cast<std::vector<float>*>(&( filters_npy["arr_0"].data_holder.get() )[0]);
    std::vector<float> output = *point1;
    for (int i=0; i < output.size(); i++)
        std::cout << output[i] << "  ";

    std::map<int, std::vector<std::vector<std::vector<std::vector<float>>>>> conv_filters;
    std::map<int, std::vector<std::vector<float>>> fc_layers;
    std::map<int, std::vector<float>> biases;
    for (auto it = filters_npy.begin(); it!=filters_npy.end(); it++){
        if (it->second.word_size == 4){
            auto filter_pointer = reinterpret_cast<std::vector<float>*>(&( img_npy.data_holder.get() )[0]);
            std::vector<float> filter = *filter_pointer;
        } else {
            throw std::exception();
        }
        if (it->second.shape.size() == 4){
            std::vector<std::vector<std::vector<std::vector<float>>>> conv_filter(it->second.shape[0]);
            for (int i=0; i<it->second.shape[0]; i++) {
                conv_filter[i].resize(it->second.shape[1]);
                for (int j=0; j<it->second.shape[1]; j++) {
                    conv_filter[i][j].resize(it->second.shape[2]);
                    for (int k=0; k<it->second.shape[2]; k++) {
                        conv_filter[i][j][k].resize(it->second.shape[3]);
                    }
                }
            }
            //conv_filters[0] = 
        }


    


    std::vector<std::vector<int> > img(6);
    for(int i=0; i<6; i++)
    {
        img[i].resize(6);
        for(int j=0; j<6; j++)
            img[i][j] = 1;
    }
    img[3][3] = 4;
    img[4][4] = 4;
    img[0][2] = 0;
    std::cout << "The image \n";
    print_2_dim_vec(img);
    std::vector<std::vector<int> > filter(3);
    for(int i=0; i<3; i++)
    {
        filter[i].resize(3);
        for(int j=0; j<3; j++)
            filter[i][j] = 0;
    }
    filter[2][2] = 1;
    filter[2][1] = 1;
    filter[0][1] = 2;
    std::cout << "Filter \n";
    print_2_dim_vec(filter);
    std::vector<std::vector<int> > out1 = conv2d(img,filter,"zero");
    std::cout << "Zero padding \n";
    print_2_dim_vec(out1);
    std::vector<std::vector<int> > out2 = conv2d(img,filter,"none");
    std::cout << "No padding \n";
    print_2_dim_vec(out2);
    std::vector<std::vector<int> > out3 = conv2d(img,filter,"repeat");
    std::cout << "Repeat padding \n";
    print_2_dim_vec(out3);

    return 0;
}

28, 28
conv2d 64, 8X8 2 stride, SAME padding
Relu
Conv2d 128, 6X6, 2 stride VALID padding
Relu
Conv2d 128, 5x5, 1 stride, valid padding
Relu
Flatten
Linear
Softmax
*/

}
