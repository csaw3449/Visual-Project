#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// resize to 32x32 has to be done before calling this function
Mat applyGaborFilter(const Mat& resizedImage) {

    // Convert to float
    resizedImage.convertTo(resizedImage, CV_32F);

    // Define Gabor filter parameters
    double ksize = 21; // Size of the filter
    double sigma = 5; // Standard deviation of the Gaussian envelope
    double gamma = 0.5; // Spatial aspect ratio
    double lambda = 10; // Wavelength of the sinusoidal factor
    double psi = 0; // Phase offset

    // Store results for maximum value combination
    Mat combinedImage = Mat::zeros(resizedImage.size(), CV_32F);

    // Loop over 4 orientations
    for (int orientation = 0; orientation < 4; ++orientation) {
        double theta = orientation * CV_PI / 4; // 0, 45, 90, 135 degrees
        
        // Create the Gabor kernel
        Mat gaborKernel = getGaborKernel(Size(ksize, ksize), sigma, theta, lambda, gamma, psi, CV_32F);
        
        // Apply Gabor filter
        Mat filteredImage;
        filter2D(resizedImage, filteredImage, CV_32F, gaborKernel);
        
        // Combine using the maximum value
        max(combinedImage, filteredImage, combinedImage);
    }

    // Normalize and convert back to 8-bit
    combinedImage.convertTo(combinedImage, CV_8U);

    // Display the results
    // imshow("Original Image", resizedImage);
    //imshow("Gabor Filtered Image", combinedImage);
    return combinedImage;
}


int main(int argc, char** argv) {

    // Load Images of dataset
    vector<Mat> images;

    vector<cv::String> fn;
    glob("./dataset/*.jpg", fn, false);
    size_t count = fn.size(); //number of png files in images folder
    Mat resizedImage;

    for (int i=0; i<count; i++) {      
        Mat image = imread(fn[i], IMREAD_COLOR);
        // imshow("Original Image", image);
        if (image.empty()) {
            cerr << "Error: Could not read image " << fn[i] << endl;
            continue;
        }        
        resize(image, resizedImage, Size(32, 32));
        images.push_back(resizedImage);
        fprintf(stdout, "Image %d loaded\n", i);
        imshow("Original Image", resizedImage);
    }
    // Apply Gabor filter to all images
    vector<Mat> gaborImages;
    //for (int i = 0; i < images.size(); i++) {
    //    gaborImages.push_back(applyGaborFilter(images[i]));
    //}

    return 0;
    
}

