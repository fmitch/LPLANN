#ifndef ZERO_HPP
#define ZERO_HPP

template <typename T>
void zero(Layer<T> & in_layer){
    for (int i =0; i < in_layer.output->size; i++){
        in_layer.output->arr[i] = 0;
    }
}

#endif
