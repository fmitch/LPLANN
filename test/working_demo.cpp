#include <iostream>
#include <map>
#include <stdexcept>
#include "src/types/types.hpp"
#include "src/types/binary.hpp"
#include "src/types/fixed.hpp"
#include "src/types/matrix.hpp"
#include "src/binary/layer.hpp"
#include "src/ops/print.hpp"
#include "src/binary/bin_wrappers.hpp"
#include "src/ops/op_wrappers.hpp"
#include "src/open_source/cnpy/cnpy.hpp"
#include "src/construction/layer.hpp"
#include <vector>
#include <string>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

#include <chrono>

template <typename T>
std::vector<int> argsort(const T* data, int size)
{
	std::vector<int> index(size, 0);
	for (int i = 0 ; i != index.size() ; i++) {
		index[i] = i;
	}
	sort(index.begin(), index.end(),
		[&](const int& a, const int& b) {
			return (data[a] < data[b]);
		}
	);
	return index;
}

int main(){
    cv::VideoCapture vCap(0);
    float fps = 2.0;
    std::vector<std::string> classes = {"clutter", "book", "cat",
                            "chair", "cord", "dog", "eyeglasses",
                            "laptop", "monitor", "pants", "person",
                            "shirt", "shoe", "table"};
    
    cv::Mat frame(256, 256, CV_8UC3);
    cv::Mat inFrame;

    std::vector<int> input_dimensions = {256,256,3};
    Input<float> input(input_dimensions, 1);
    std::vector<int> dims = input.output->dims;
	int num_classes = 14;

    // Initialize float network
    Layer<float> conv1(input_dimensions, CONV2D, std::vector<int>{3,3,3,32}, true);
    Layer<float> pool1(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv2(input_dimensions, CONV2D, std::vector<int>{3,3,32,64}, true);
    Layer<float> pool2(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv3(input_dimensions, CONV2D, std::vector<int>{3,3,64,64}, true);
    Layer<float> pool3(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv4(input_dimensions, CONV2D, std::vector<int>{3,3,64,64}, true);
    Layer<float> pool4(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv5(input_dimensions, CONV2D, std::vector<int>{3,3,64,64}, true);
    Layer<float> pool5(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> conv6(input_dimensions, CONV2D, std::vector<int>{3,3,64,64}, true);
    Layer<float> pool6(input_dimensions, POOL, std::vector<int>{2,2}, false);
    Layer<float> flat(input_dimensions, ACTIVATION, std::vector<int>{0}, false);

    Layer<float> fc1(input_dimensions, MULTIPLY, std::vector<int>{1024}, true);
    Layer<float> fc2(input_dimensions, MULTIPLY, std::vector<int>{num_classes}, true);

    // Load float weights
    conv1.load_weights("layer6_32_small_47.npz", "arr_0");
    conv1.load_bias("layer6_32_small_47.npz", "arr_1");
    conv2.load_weights("layer6_32_small_47.npz", "arr_2");
    conv2.load_bias("layer6_32_small_47.npz", "arr_3");
    conv3.load_weights("layer6_32_small_47.npz", "arr_4");
    conv3.load_bias("layer6_32_small_47.npz", "arr_5");
    conv4.load_weights("layer6_32_small_47.npz", "arr_6");
    conv4.load_bias("layer6_32_small_47.npz", "arr_7");
    conv5.load_weights("layer6_32_small_47.npz", "arr_8");
    conv5.load_bias("layer6_32_small_47.npz", "arr_9");
    conv6.load_weights("layer6_32_small_47.npz", "arr_10");
    conv6.load_bias("layer6_32_small_47.npz", "arr_11");
    fc1.load_weights("layer6_32_small_47.npz", "arr_12");
    fc1.load_bias("layer6_32_small_47.npz", "arr_13");
    fc2.load_weights("layer6_32_small_47.npz", "arr_14");
    fc2.load_bias("layer6_32_small_47.npz", "arr_15");



    while(1){
		auto start = std::chrono::high_resolution_clock::now();
        vCap >> inFrame; // get a new frame from camera
         
        // Press  ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if(c==27)
            break;

		//cv::Mat inFrame = cv::imread("dog.jpg", cv::IMREAD_COLOR);
        cv::resize(inFrame, frame, frame.size());
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

		Matrix<float>* input_img;
		int channels = frame.channels();

		int nRows = frame.rows;
		int nCols = frame.cols;
		input_img = new Matrix<float>(std::vector<int>{nRows, nCols, channels});

		uchar* p = frame.data;
		int count = 0;
        for (int j = 0; j < nRows; ++j){
            for(int i = 0; i < nCols; ++i){
                for (int k = 0; k < channels; ++k){
					input_img->arr[i+j*nCols+k*nRows*nCols] = p[count]/255.0;
					count++;
				}
			}
		}
        float * inp = input_img->arr;

		//Initialize network
		//cnpy::NpyArray labels_npy = cnpy::npy_load("train_labels.npy");
		//auto label_pointer = reinterpret_cast<std::vector<int>*>(&(labels_npy.data_holder.get())[0]);
		//std::vector<int> labels = *label_pointer;

		//input.load_data("train_images.npy", true);
		input.output = input_img;
        inp = input.output->arr;


        conv2d_wrapper(input, conv1);
        float * c1 = conv1.output->arr;
        pool_wrapper(conv1, pool1, MAX);
        relu_wrapper(pool1, pool1);

        conv2d_wrapper(pool1, conv2);
        float * c2 = conv2.output->arr;
        pool_wrapper(conv2, pool2, MAX);
        relu_wrapper(pool2, pool2);

        conv2d_wrapper(pool2, conv3);
        float * c3 = conv3.output->arr;
        pool_wrapper(conv3, pool3, MAX);
        relu_wrapper(pool3, pool3);

        conv2d_wrapper(pool3, conv4);
        float * c4 = conv4.output->arr;
        pool_wrapper(conv4, pool4, MAX);
        relu_wrapper(pool4, pool4);

        conv2d_wrapper(pool4, conv5);
        float * c5 = conv5.output->arr;
        pool_wrapper(conv5, pool5, MAX);
        relu_wrapper(pool5, pool5);

        conv2d_wrapper(pool5, conv6);
        float * c6 = conv6.output->arr;
        pool_wrapper(conv6, pool6, MAX);
        relu_wrapper(pool6, pool6);
        flatten_wrapper(pool6, flat);

        fc_wrapper(flat, fc1);
        relu_wrapper(fc1, fc1);
        
        fc_wrapper(fc1, fc2);
        softmax_wrapper(fc2,fc2);
        
		std::vector<int> ind = argsort(fc2.output->arr, num_classes);

		auto stop = std::chrono::high_resolution_clock::now(); 
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
        fps += 1.0/(duration.count()/1e6);
        fps /= 2.0;

        int y0 = 30;
        for (int i = 1; i < 4; i++){
            auto out_text = classes[ind[num_classes-i]] +" "+ 
                std::to_string(fc2.output->arr[ind[num_classes-i]]);
            cv::putText(inFrame, out_text, cv::Point(30,y0), 
                cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1);
            y0 += 20;
        }
        auto out_text = std::to_string(fps) + " FPS";
        cv::putText(inFrame, out_text, cv::Point(30,y0), 
            cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(0,255,0), 1);
        cv::imshow( "Frame", inFrame );
	}

    return 0;
}
