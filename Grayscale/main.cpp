#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>

void modifyImage(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {
	std::memcpy(outputImage, inputImage, width * height * 3);
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
	//{}
	//double matrShift[3][3] = { {1,0,-img.cols/2},{0,1,-img.rows/2},{0,0,1} };
	//double matrRot[3][3] = { {0,-1,0},{1,0,0},{0,0,1} };
	//double matrBackshift[3][3] = { {1,0,img.cols / 2},{0,1,img.rows / 2},{0,0,1} };

	//cv::Mat cvMatrShift(3, 3, CV_64F, matrShift);
	//cv::Mat cvMatrRot(3, 3, CV_64F, matrRot);
	//cv::Mat cvMatrBackshift(3, 3, CV_64F, matrBackshift);

	//cv::Mat resultMatr = cvMatrBackshift * cvMatrRot * cvMatrShift;

	//cv::warpPerspective(img, moified, resultMatr, img.size());
	modifyImage(img.data, moified.data, img.cols, img.rows);
	cv::imshow("original", img);
	cv::imshow("gray", gray);
	cv::imshow("modified", moified);
	cv::waitKey();
	return 0;
}