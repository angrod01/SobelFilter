#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


int xGradient(cv::Mat image, int i, int j){
    //TODO
    return  0;

}
int yGradient (cv::Mat image, int i, int j){
    //TODO
    return 0;
}

cv::Mat sobelTransform(const cv::Mat& inputImage)
{
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


int main(int argc, char** argv)
{
    const cv::Mat initialImage = cv::imread("Cats.jpg", cv::IMREAD_GRAYSCALE);
    const cv::Mat finalImage = sobelTransform(initialImage);
    cv::imwrite("CatsBorders.jpg",finalImage);
}
