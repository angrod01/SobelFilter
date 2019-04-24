# SobelFilter

Simple border detection inplementation on C++ using a Sobel filter. 
Uses OpenCV for reading, writing and displaying the images but not for the Sobel operator. Magnitude is aproximated with less complex and lighter formula using absolute sumation:  G = abs(Gx) + abs(Gy).

## How to build (Ubuntu 18.04)

sudo apt-get install libopencv-dev
sudo apt-get install libomp-dev
g++ -std=c++17 sobelFilter.cpp -o sobelFilter -fopenmp `pkg-config --cflags --libs opencv` -lgomp


## How to run

./sobelFilter imagePath

## Output example

./sobelF Cats.jpg
63 miliseconds
Saving filtered image as: CatsFiltered.jpg
