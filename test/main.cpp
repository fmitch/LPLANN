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
#include "src/construction/network.hpp"
#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>


#include <chrono>

int main(){
    //cv::VideoCapture vCap(0);
    
    cv::Mat frame(416, 416, CV_8UC3);
    while(1){
		auto start = std::chrono::high_resolution_clock::now();
/*
        vCap >> frame; // get a new frame from camera
        cv::imshow( "Frame", frame );
         
        // Press  ESC on keyboard to exit
        //char c = (char)cv::waitKey(25);
        //if(c==27)
        //    break;
*/
		cv::Mat inFrame = cv::imread("dog.jpg", cv::IMREAD_COLOR);
        cv::resize(inFrame, frame, frame.size());

		std::shared_ptr<Matrix<float>> input_img;
		int channels = frame.channels();

		int nRows = frame.rows;
		int nCols = frame.cols;
		input_img.reset(new Matrix<float>(std::vector<int>{nRows, nCols, channels}));

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
		cnpy::NpyArray labels_npy = cnpy::npy_load("train_labels.npy");
		auto label_pointer = reinterpret_cast<std::vector<int>*>(&(labels_npy.data_holder.get())[0]);
		std::vector<int> labels = *label_pointer;

		std::vector<int> input_dimensions = {416,416,3};
		Input<float> input(input_dimensions, 1);
		//input.load_data("train_images.npy", true);
		input.output = input_img;
		float * in = input.output->arr;
		std::vector<int> dims = input.output->dims;

		// Initialize float network
		Layer<float> conv1(input_dimensions, CONV2D, std::vector<int>{3,3,3,16}, true);
		Layer<float> pool1(input_dimensions, POOL, std::vector<int>{2,2}, false);
		Layer<float> conv2(input_dimensions, CONV2D, std::vector<int>{3,3,16,32}, true);
		Layer<float> pool2(input_dimensions, POOL, std::vector<int>{2,2}, false);
		Layer<float> conv3(input_dimensions, CONV2D, std::vector<int>{3,3,32,64}, true);
		Layer<float> pool3(input_dimensions, POOL, std::vector<int>{2,2}, false);
		Layer<float> conv4(input_dimensions, CONV2D, std::vector<int>{3,3,64,128}, true);
		Layer<float> pool4(input_dimensions, POOL, std::vector<int>{2,2}, false);
		Layer<float> conv5(input_dimensions, CONV2D, std::vector<int>{3,3,128,256}, true);
		Layer<float> pool5(input_dimensions, POOL, std::vector<int>{2,2}, false);
		Layer<float> conv6(input_dimensions, CONV2D, std::vector<int>{3,3,256,512}, true);
		Layer<float> pool6(input_dimensions, POOL, std::vector<int>{1,1}, false);
		Layer<float> conv7(input_dimensions, CONV2D, std::vector<int>{3,3,512,1024}, true);
		Layer<float> conv8(input_dimensions, CONV2D, std::vector<int>{3,3,1024,1024}, true);
		Layer<float> conv9(input_dimensions, CONV2D, std::vector<int>{1,1,1024,125}, true);

		// Load float weights
		conv1.load_weights("yolov2_flipped.npz", "arr_0");
		conv1.load_bias("yolov2_flipped.npz", "arr_1");
		float * w1 = conv1.weights->arr;
		float * b1 = conv1.bias->arr;
		conv2.load_weights("yolov2_flipped.npz", "arr_2");
		conv2.load_bias("yolov2_flipped.npz", "arr_3");
		conv3.load_weights("yolov2_flipped.npz", "arr_4");
		conv3.load_bias("yolov2_flipped.npz", "arr_5");
		conv4.load_weights("yolov2_flipped.npz", "arr_6");
		conv4.load_bias("yolov2_flipped.npz", "arr_7");
		conv5.load_weights("yolov2_flipped.npz", "arr_8");
		conv5.load_bias("yolov2_flipped.npz", "arr_9");
		conv6.load_weights("yolov2_flipped.npz", "arr_10");
		conv6.load_bias("yolov2_flipped.npz", "arr_11");
		conv7.load_weights("yolov2_flipped.npz", "arr_12");
		conv7.load_bias("yolov2_flipped.npz", "arr_13");
		conv8.load_weights("yolov2_flipped.npz", "arr_14");
		conv8.load_bias("yolov2_flipped.npz", "arr_15");
		conv9.load_weights("yolov2_flipped.npz", "arr_16");
		conv9.load_bias("yolov2_flipped.npz", "arr_17");

        float leaky_param = 10.0;
        conv2d_wrapper(input, conv1);
		float * out = conv1.output->arr;
        pool_wrapper(conv1, pool1, MAX);
		out = pool1.output->arr;
        leaky_wrapper(pool1, pool1, leaky_param);

        conv2d_wrapper(pool1, conv2);
		out = conv2.output->arr;
        pool_wrapper(conv2, pool2, MAX);
		out = pool2.output->arr;
        leaky_wrapper(pool2, pool2, leaky_param);

        conv2d_wrapper(pool2, conv3);
		out = conv3.output->arr;
        pool_wrapper(conv3, pool3, MAX);
        leaky_wrapper(pool3, pool3, leaky_param);

        conv2d_wrapper(pool3, conv4);
		out = conv4.output->arr;
        pool_wrapper(conv4, pool4, MAX);
        leaky_wrapper(pool4, pool4, leaky_param);

        conv2d_wrapper(pool4, conv5);
		out = conv5.output->arr;
        pool_wrapper(conv5, pool5, MAX);
        leaky_wrapper(pool5, pool5, leaky_param);

        conv2d_wrapper(pool5, conv6);
		out = conv6.output->arr;
        pool_wrapper(conv6, pool6, MAX);
        leaky_wrapper(pool6, pool6, leaky_param);

        conv2d_wrapper(pool6, conv7);
		out = conv7.output->arr;
        leaky_wrapper(conv7, conv7, leaky_param);
        
        conv2d_wrapper(conv7, conv8);
		out = conv8.output->arr;
        leaky_wrapper(conv8, conv8, leaky_param);

        conv2d_wrapper(conv8, conv9);
		out = conv9.output->arr;

		auto stop = std::chrono::high_resolution_clock::now(); 
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
		std::cout << duration.count() << std::endl; 
	}

    return 0;
}
