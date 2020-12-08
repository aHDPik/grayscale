#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>

void modifyImage(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {
	std::memcpy(outputImage, inputImage, width * height * 3);
	
	//[b00 g00 r00 b10 g10 r10 b20 g20 r20 b01 g01 r01 b11 g11 r11 b21 g21 r21]
	//[0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17 ]

	//Для того, чтобы преобразовать цветное изображение в черно - белое, нужно найти среднее арифметическое значение B, G, R каналов пикселя.
	//Затем это значение присвоить BGR каналам этого же пикселя
	
	int size = width * height * 3;
	for (int i = 0; i < size; i++) {//перебираем в цикле все пиксели исходного изображения
		int ovrll = (inputImage[i] + inputImage[i + 1] + inputImage[i + 2]) / 3;//Нахождение среднего арифметического значения B, G, R каналов пикселя
		outputImage[i] = ovrll;//Присваивание среднего арифметического значения B, G, R каналам 
		outputImage[i + 1] = ovrll;
		outputImage[i + 2] = ovrll;
		i += 2;//Переходим к следующим трем каналам 
	}
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
