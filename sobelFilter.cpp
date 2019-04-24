#include <cmath>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

const int x[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
const int y[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

int xGradient(cv::Mat image, int i, int j){
    
    return  (x[0][0]*(int)image.at<uchar>(j, i    )) + (x[0][2]*(int)image.at<uchar>(j + 2, i    )) +
            (x[1][0]*(int)image.at<uchar>(j, i + 1)) + (x[1][2]*(int)image.at<uchar>(j + 2, i + 1)) +
            (x[2][0]*(int)image.at<uchar>(j, i + 2)) + (x[2][2]*(int)image.at<uchar>(j + 2, i + 2));
}

int yGradient (cv::Mat image, int i, int j){

    return  (y[0][0]*(int)image.at<uchar>(j, i    )) + (y[0][1]*(int)image.at<uchar>(j + 1, i    ))  + (y[0][2]*(int)image.at<uchar>(j + 2, i    )) +
            (y[2][0]*(int)image.at<uchar>(j, i + 2)) + (y[2][1]*(int)image.at<uchar>(j + 1, i + 2))  + (y[2][2]*(int)image.at<uchar>(j + 2, i + 2));
}

cv::Mat sobelTransform(const cv::Mat& inputImage){

    cv::Mat filteredImage = cv::Mat::zeros(inputImage.size(), inputImage.type());
    
#pragma omp parallel for    
    for (int j = 0; j < inputImage.rows-2;  ++j) {
        for (int i = 0;  i < inputImage.cols-2;  ++i) {
            // Calculate X gradient of pixel
            int xValOfPixel = xGradient(inputImage, i, j);
            // Calculate Y gradient of pixel
            int yValOfPixel = yGradient(inputImage, i, j);
            // Calculate magnitude (absolute aproximation)
            int sum = std::clamp(std::abs(xValOfPixel) + std::abs(yValOfPixel), 0, 255);

            filteredImage.at<uchar>(j, i) = (uchar)sum;
        }
    }

    return filteredImage;
}


int main(int argc, char** argv){
    
    if (argc != 2) {
        std::cerr << "How to run: ./sobelFilter image" << std::endl;
        return 1;
    }

    //Load cats image in greyscale
    const cv::Mat initialImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    
    //Apply filter
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    const cv::Mat finalImage = sobelTransform(initialImage);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    
    //Calculate filter execution time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << duration << " miliseconds\n";
    
    //Display filtered image with OpenCV
    cv::namedWindow("Sobel Filter", cv::WINDOW_AUTOSIZE);
    cv::imshow("Sobel Filter", finalImage);
    
    //Save output file
    std::string fileName = argv[1];
    fileName  = fileName.substr(0, fileName.find_last_of(".")) + "Filtered" + fileName.substr(fileName.find_last_of("."));
    std::cout << "Saving filtered image as: " << fileName << std::endl;
    cv::imwrite(fileName, finalImage);
    
    cv::waitKey(0);
    
}
