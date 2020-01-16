#include <iostream>
#include <torch/script.h>
#include <torch/torch.h>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc,char**argv)
{
    torch::jit::script::Module encoder = torch::jit::load("monodepth2/models/mono+stereo_1024x320/encoder.cpt");
    encoder.to(at::kCUDA);
    torch::jit::script::Module decoder = torch::jit::load("monodepth2/models/mono+stereo_1024x320/decoder.cpt");
    decoder.to(at::kCUDA);
    cv::Mat src=cv::imread("/home/arno/project/Py/monodepth2/assets/test_image.jpg");
    cv::Mat input_mat;
    cv::VideoCapture cap(argv[1]);
    int w=1024;
    int h=320;
    while (1) {
        if(!cap.read(src))
            break;
        cv::resize(src,input_mat,cv::Size(w,h));
        input_mat.convertTo(input_mat,CV_32FC3,1./255.);
        torch::Tensor tensor_image = torch::from_blob(input_mat.data, {1,input_mat.rows, input_mat.cols,3}, torch::kF32);
        tensor_image = tensor_image.permute({0,3,1,2});
        tensor_image = tensor_image.to(at::kCUDA);

        std::vector<torch::IValue> batch;
        batch.push_back(tensor_image);
        auto result_encoder = encoder.forward(batch);
    //    cout<<*result_encoder.type()<<endl;
        batch.clear();
        batch.push_back(result_encoder);
        auto result_decoder = decoder.forward(batch);
        auto tensor_result = result_decoder.toTensor().to(at::kCPU);
        tensor_result = tensor_result.permute({0,3,2,1});
//        cout<<tensor_result.sizes()<<endl;
        cv::Mat disp=cv::Mat(h,w,CV_32FC1,tensor_result.data_ptr());
        cv::resize(disp,disp,cv::Size(src.cols,src.rows));
        disp*=512;

        disp.convertTo(disp,CV_8UC1);
        cv::cvtColor(disp,disp,CV_GRAY2BGR);
        src.push_back(disp);
//        vector<cv::Mat> channels={disp,disp,disp};
//        cv::merge(channels,disp);
        cv::resize(src,src,cv::Size(),0.5,0.5);
//        cv::imshow("result",disp);
        cv::imshow("src",src);
        if(cv::waitKey(1)==27)
            break;
    }

    cout<<"hello"<<endl;
    return 0;
}
