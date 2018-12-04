#include "input.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "src/open_source/cnpy/cnpy.hpp"
#include "src/types/types.hpp"

Input::Input(std::string filename){
    cnpy::NpyArray img_npy = cnpy::npy_load(filename);
    auto img_pointer = reinterpret_cast<std::vector<float>*>(&(img_npy.data_holder.get() )[0]);
        std::vector<float> img_vec = *img_pointer;
        for (int i=0; i<img_npy.shape.size(); i++){
            dims.push_back(img_npy.shape[i]);
        }
        for (int j=0; j<dims[0]; j++){ //Num of images
            for (int k=0; k<dims[1]; k++){ //X
                for (int l=0; l<dims[2]; l++){ //Y
                    for (int m=0; m<dims[3]; m++){ //Channels
                        img[index(j,k,l,m)] = 
                            filter[ j*dims[3]*dims[2] + k*dims[3]*dims[2]*dims[1] + l*dims[3] + m ];
                    }
                }
            }
        }
}

