#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>

void modifyImage(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {

}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Specify image name" << std::endl;
		return -1;
	}

	cv::Mat img = cv::imread(argv[1]);
	cv::Mat gray;
	cv::Mat moified(img.rows, img.cols, CV_8UC3);
	cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);
	modifyImage(img.data, moified.data, img.cols, img.rows);
	cv::imshow("original", img);
	cv::imshow("gray", gray);
	cv::imshow("modified", moified);
	cv::waitKey();
	return 0;
}