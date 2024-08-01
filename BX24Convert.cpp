#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

int main(){
    string filename = "./frame.bin";
    
    // height and width of image (with colors merged)
    int height = 1216;
    int width = 1936;

    ifstream file(filename, ios::binary);
    if (!file){
        cerr << "Error opening file" << endl;
        return -1;
    }

    // Get file length
    file.seekg(0, ios::end);
    size_t length = file.tellg();
    file.seekg(0, ios::beg);

    // Read binary data into buffer
    vector<char> buffer(length);
    file.read(buffer.data(), length);
    file.close();

    vector<char> r;
    vector<char> g;
    vector<char> b;

    for (int i=0; i < buffer.size(); i++){
        if (i % 4 == 1){
            r.push_back(buffer[i]);
        }
        else if (i % 4 == 2){
            g.push_back(buffer[i]);
        }
        else if (i % 4 == 3){
            b.push_back(buffer[i]);
        }
    }

    cv::Mat red(height, width, CV_8UC1, r.data());
    cv::Mat green(height, width, CV_8UC1, g.data());
    cv::Mat blue(height, width, CV_8UC1, b.data());

    vector<cv::Mat> channels;
    channels.push_back(blue);
    channels.push_back(green);
    channels.push_back(red);

    cv::Mat image;
    cv::merge(channels, image);

    string filenameOut = "frame.jpg";
    if (cv::imwrite(filenameOut, image)){
        cout << "Image saved" << endl;
    }
    else {
        cerr << "Error saving image" << endl;
    }

    cv::imshow("Image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}