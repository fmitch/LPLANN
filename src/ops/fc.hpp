#ifndef FC_HPP
#define FC_HPP

#include "src/construction/network.hpp"

template <typename T1>
void flatten_3d(Layer <T1> & in_layer, Layer <T1> & out_layer){
    int flat_size = in_layer.output->dims[0]*in_layer.output->dims[1]*in_layer.output->dims[2];
    int count = 0; 
    for (int y=0; y<in_layer.output->dims[1]; ++y){
        for (int x=0; x<in_layer.output->dims[0]; ++x){
            for (int z=0; z<in_layer.output->dims[2]; ++z){
                out_layer.output->arr[count] = in_layer.output->arr[in_layer.output->index(x,y,z)];
                ++count;
            }
        }
    }
}

#endif
