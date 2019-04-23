#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

const int x[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
const int y[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

int xGradient(cv::Mat image, int i, int j){
    
    return  (x[0][0]*(int)image.at<uchar>(j, i    )) + (x[0][1]*(int)image.at<uchar>(j + 1, i    ))  + (x[0][2]*(int)image.at<uchar>(j + 2, i    )) +
            (x[1][0]*(int)image.at<uchar>(j, i + 1)) + (x[1][1]*(int)image.at<uchar>(j + 1, i + 1))  + (x[1][2]*(int)image.at<uchar>(j + 2, i + 1)) +
            (x[2][0]*(int)image.at<uchar>(j, i + 2)) + (x[2][1]*(int)image.at<uchar>(j + 1, i + 2))  + (x[2][2]*(int)image.at<uchar>(j + 2, i + 2));
}

int yGradient (cv::Mat image, int i, int j){

    return  (y[0][0]*(int)image.at<uchar>(j, i    )) + (y[0][1]*(int)image.at<uchar>(j + 1, i    ))  + (y[0][2]*(int)image.at<uchar>(j + 2, i    )) +
            (y[1][0]*(int)image.at<uchar>(j, i + 1)) + (y[1][1]*(int)image.at<uchar>(j + 1, i + 1))  + (y[1][2]*(int)image.at<uchar>(j + 2, i + 1)) +
            (y[2][0]*(int)image.at<uchar>(j, i + 2)) + (y[2][1]*(int)image.at<uchar>(j + 1, i + 2))  + (y[2][2]*(int)image.at<uchar>(j + 2, i + 2));
}

cv::Mat sobelTransform(const cv::Mat& inputImage){

    cv::Mat filteredImage = cv::Mat::zeros(inputImage.size(), inputImage.type());
    
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
    
    const cv::Mat initialImage = cv::imread("Cats.jpg", cv::IMREAD_GRAYSCALE);
    const cv::Mat finalImage = sobelTransform(initialImage);
    cv::namedWindow("Sobel Filter", cv::WINDOW_AUTOSIZE);
    cv::imshow("Sobel Filter", finalImage);
    cv::imwrite("CatsBorders.jpg",finalImage);
    cv::waitKey(0);
    
}
