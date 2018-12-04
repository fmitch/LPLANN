#ifndef INPUT_HPP
#define INPUT_HPP

template <typename T>
class Input{
    T* img;
    std::vector<int> dims;
    void set_dims(std::vector<int> d){
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
        dims = d;
    }
    ~Input(){
        delete[] arr;
    }
    T& operator[] (int index){
        return arr[index * dims[1]*dims[2]];
    }
    size_t index(int x, int y, int z, int w) const { return x + y*dims[0] + z*dims[0]*dims[1] + w*dims[0]*dims[1]*dims[2];}
};

Input::Input(std::string filename){
    cnpy::NpyArray img_npy = cnpy::npy_load(filename);
    auto img_pointer = reinterpret_cast<std::vector<float>*>(&(img_npy.data_holder.get() )[0]);
    std::vector<float> img_vec = *img_pointer;
    std::vector<int> d;
    for (int i=0; i<img_npy.shape.size(); i++){
        d.push_back(img_npy.shape[i]);
    }
    set_dims(d);
    int size = 1;
    for (int i=0; i < dims.size(); i++){
        size *= dims[i];
    }
    arr = new T[size];
    for (int j=0; j<dims[0]; j++){ //Num of images
        for (int k=0; k<dims[1]; k++){ //X
            for (int l=0; l<dims[2]; l++){ //Y
                for (int m=0; m<dims[3]; m++){ //Channels
                    img[index(j,k,l,m)] = img_vec[index(j,k,l,m)];
                }
            }
        }
    }
}


#endif
