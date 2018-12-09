#include <iostream>
#include <map>
#include <stdexcept>
#include "src/types/types.hpp"
#include "src/types/binary.hpp"
#include "src/types/fixed.hpp"
#include "src/types/matrix.hpp"
#include "src/binary/layer.hpp"
#include "src/ops/print.hpp"
#include "src/ops/op_wrappers.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include "src/construction/layer.hpp"
#include <vector>
#include <string>

int main(){
    //Initialize network
    std::vector<int> input_dimensions = {28,28,1};
    Input<float> input("train_images.npy", true);
    Layer<float> conv1(input_dimensions, CONV2D, std::vector<int>{5,5,1,32}, true);
    Layer<float> pool1(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv2(input_dimensions, CONV2D, std::vector<int>{5,5,32,64}, true);
    Layer<float> pool2(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> fc1(input_dimensions, MULTIPLY, std::vector<int>{1024}, true);
    Layer<float> fc2(input_dimensions, MULTIPLY, std::vector<int>{10}, true);

    //Load weights
    conv1.load_weights("full.npz", "arr_0");
    conv1.load_bias("full.npz", "arr_1");
    conv2.load_weights("full.npz", "arr_2");
    conv2.load_bias("full.npz", "arr_3");
    fc1.load_weights("full.npz", "arr_4");
    fc1.load_bias("full.npz", "arr_5");
    fc2.load_weights("full.npz", "arr_6");
    fc2.load_bias("full.npz", "arr_7");

    //Run operations
    conv2d_wrapper(input, conv1, true);
    pool_wrapper(conv1, pool1, true);

    print_2d_slice(pool1.output, 0);

    conv2d_wrapper(pool1, conv2, true);

    print_2d_slice(conv2.output, 0);

    pool_wrapper(conv2, pool2, true);

    print_2d_slice(pool2.output, 0);

    fc_wrapper(pool2, fc1, true);
    relu_wrapper(fc1, fc1, true);
    fc_wrapper(fc1, fc2, true);
    relu_wrapper(fc2, fc2, true);

    //Observe the output
    for (int i =0; i < 10; i++){
        std::cout << fc2.output->arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
