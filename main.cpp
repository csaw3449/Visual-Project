#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace cv;
using namespace std;

/* Random number generator for transformations
std::random_device rd;
std::mt19937 gen(rd());

// Function for rotation
Mat rotateImage(const Mat& image, double angle) {
    Mat rotated;
    Point2f center(image.cols / 2.0, image.rows / 2.0);
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(image, rotated, rotationMatrix, image.size());
    return rotated;
}

// Function for flipping
Mat flipImage(const Mat& image, int flipCode) {
    Mat flipped;
    flip(image, flipped, flipCode);
    return flipped;
}

// Function for color transformations (brightness and contrast adjustment)
Mat adjustBrightnessContrast(const Mat& image, double alpha, int beta) {
    Mat adjusted;
    image.convertTo(adjusted, -1, alpha, beta);
    return adjusted;
}

// Function for blurring
Mat blurImage(const Mat& image, int kernelSize) {
    Mat blurred;
    GaussianBlur(image, blurred, Size(kernelSize, kernelSize), 0);
    return blurred;
}

// Function for sharpening
Mat sharpenImage(const Mat& image) {
    Mat sharpened, kernel = (Mat_<float>(3, 3) << 
        0, -1, 0, 
        -1, 5, -1, 
        0, -1, 0);
    filter2D(image, sharpened, -1, kernel);
    return sharpened;
}

// Augmentation pipeline
vector<Mat> augmentImage(const Mat& image) {
    vector<Mat> augmentedImages;

    // Generate random transformations
    uniform_real_distribution<> angleDist(-30, 30);
    uniform_int_distribution<> flipDist(0, 1);
    uniform_real_distribution<> alphaDist(0.8, 1.2);
    uniform_int_distribution<> betaDist(-50, 50);
    uniform_int_distribution<> blurKernelDist(1, 5);

    // Rotate
    augmentedImages.push_back(rotateImage(image, angleDist(gen)));

    // Flip
    augmentedImages.push_back(flipImage(image, flipDist(gen)));

    // Adjust brightness and contrast
    augmentedImages.push_back(adjustBrightnessContrast(image, alphaDist(gen), betaDist(gen)));

    // Blur
    int kernelSize = blurKernelDist(gen) * 2 + 1; // Ensure odd kernel size
    augmentedImages.push_back(blurImage(image, kernelSize));

    // Sharpen
    augmentedImages.push_back(sharpenImage(image));

    return augmentedImages;
}

// Function to process the dataset
void createAugmentedDataset(const string& inputPath, const string& outputPath, int augmentationsPerImage) {
    // Create a vector to store the image file paths
    vector<String> imagePaths;

    // Use cv::glob to get all PNG and JPG files in the input directory
    glob(inputPath + "/*.png", imagePaths, false);  // Find all .png files
    glob(inputPath + "/*.jpg", imagePaths, false);  // Find all .jpg files
    Mat image;

        image = imread(imagePaths.front(), IMREAD_GRAYSCALE);
        if (image.empty()) {
            cerr << "Failed to load image: " << imagePaths.front() << endl;
        }

        // Image processing and augmentation logic goes here
        cout << "Loaded image: " << imagePaths.front() << endl;
    

    Mat resizedImage;
    resize(image, resizedImage, Size(32, 32));
    // Generate and save augmentations
    vector<Mat> total_augmentedImages;
    for (int i = 0; i < augmentationsPerImage; ++i) {
        vector<Mat> augmented_5 = augmentImage(resizedImage);
        for (int j = 0; j < augmented_5.size(); ++j) {
            total_augmentedImages.push_back(augmented_5[j]);
        }
    }
    for (int j = 0; j < total_augmentedImages.size(); ++j) {
        string augPath = outputPath + "/" + "_aug" + to_string(j) + ".png";
        imwrite(augPath, total_augmentedImages[j]);
        }
}

// Main function*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void savePathsToCSV(const std::string& filename, const std::vector<std::string>& imagePaths, const std::vector<string>& labels) {
    // Open the file in truncate mode to clear its content
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Write header (optional)
    file << "Path,Label\n";

    // Write image paths and labels to the file
    for (size_t i = 0; i < imagePaths.size(); ++i) {
        file << imagePaths[i] << "," << labels[i] << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}


int main() {
    // Paths to the 5 images
    std::vector<std::string> imagePaths = {
        "dataset/hand_1/checazzo.jpg",
        "dataset/hand_2/peace.jpg",
        "dataset/hand_3/thumbup.jpg",
        "dataset/hand_4/ok.jpg",
        "dataset/hand_5/flat.jpg"
    };

    // Corresponding labels
    std::vector<string> labels = {"checazzo", "peace", "thumbup", "ok", "flat"};

    // Save the paths and labels to a CSV file
    savePathsToCSV("images.csv", imagePaths, labels);

    return 0;
}


