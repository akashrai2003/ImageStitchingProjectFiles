#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void selectImages(vector<String>& img_names) {
    int num_images;
    cout << "Enter the number of images you want to stitch: ";
    cin >> num_images;

    img_names.clear();
    cin.ignore(); // Ignore newline character after reading the number
    for (int i = 0; i < num_images; ++i) {
        string img_name;
        cout << "Enter the filename of image " << i + 1 << ": ";
        getline(cin, img_name);
        img_names.push_back(img_name);
    }
}

void stitchImages(const vector<String>& img_names) {
    if (img_names.empty()) {
        cerr << "Error: No images selected." << endl;
        return;
    }

    // Read input images
    vector<Mat> images;
    for (const auto& img_name : img_names) {
        Mat img = imread(img_name);
        if (img.empty()) {
            cerr << "Error: Unable to read image " << img_name << endl;
            return;
        }
        images.push_back(img);
    }

    // Set parameters for image stitching
    Stitcher::Mode mode = Stitcher::PANORAMA;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);

    // Perform image stitching
    Mat result;
    Stitcher::Status status = stitcher->stitch(images, result);

    // Check if stitching is successful
    if (status != Stitcher::OK) {
        cerr << "Error: Stitching failed with status code " << status << endl;
        return;
    }

    // Save the result
    imwrite("output.jpg", result);

    cout << "Stitching completed successfully. Output saved as output.jpg" << endl;
}

int main() {
    vector<String> img_names;
    int choice;
    do {
        cout << "\nImage Stitching Menu:" << endl;
        cout << "1. Select Images" << endl;
        cout << "2. Stitch Images" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            selectImages(img_names);
            break;
        case 2:
            stitchImages(img_names);
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}