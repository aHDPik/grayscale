#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdint>

//void modifyImageGS(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {
	//std::memcpy(outputImage, inputImage, width * height * 3);
	
	//[b00 g00 r00 b10 g10 r10 b20 g20 r20 b01 g01 r01 b11 g11 r11 b21 g21 r21]
	//[0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17 ]

	//Для того, чтобы преобразовать цветное изображение в черно - белое, нужно найти среднее арифметическое значение B, G, R каналов пикселя.
	//Затем это значение присвоить BGR каналам этого же пикселя
	
	//int size = width * height * 3;
	//for (int i = 0; i < size; i++) {//перебираем в цикле все пиксели исходного изображения
		//int ovrll = (inputImage[i] + inputImage[i + 1] + inputImage[i + 2]) / 3;//Нахождение среднего арифметического значения B, G, R каналов пикселя
		//outputImage[i] = ovrll;//Присваивание среднего арифметического значения B, G, R каналам 
		//outputImage[i + 1] = ovrll;
		//outputImage[i + 2] = ovrll;
		//i += 2;//Переходим к следующим трем каналам 
	//}
//}

void modifyImage(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {

	int size = width * height * 3;
	
	for (int ind = 0; ind < size; ind+=3) {//перебираем в цикле все пиксели исходного изображения

		int u = (ind/3) % width;//начальная координата х 
		int v = (ind/3) / width;//начальная координата y

		int a = 0, b = -1, c = 0;
		int d = 1, e = 0, f = 0;// в этой функции удалось повернуть картинку на 90 градусов, но только проигнорировав ошибку 
		int g = 0, h = 0, i = 1;// (с картинкой, где разные высота и ширина получилось странно, а там где одинаковые - норм)
	    
		int x = (a * u + b * v + c) / (g * u + h * v + i);//формула для новых координат
		int y = (d * u + e * v + f) / (g * u + h * v + i);

		int indOutput = ((y * width + x)*3);//индекс для перевернутого изображения

		if (indOutput + 3 < size && ind + 3 < size && ind >= 0 && indOutput >= 0)//игнор ошибки, похоже выхожу за границы массива

			for (int z = 0; z < 3; z++) {
				outputImage[indOutput + z] = inputImage[ind + z];//копируем пиксели для трех каналов
			}
	}
}

void modifyImage1(std::uint8_t* inputImage, std::uint8_t* outputImage, int width, int height) {

	int size = width * height * 3;

	for (int v = (height /2 ); v > -(height /2 ); v--) {//v - координата y в исходной картинке
		for (int u = - (width / 2); u < width / 2; u++) {//u - координата x в исходной картинке
			int ind = (abs(v - (height / 2)) * width + (u + (width / 2)));//попробовал взять левый верхний угол не за (0,0), а за (-ширина, высота)

			int a = 1, b = 0, c = 0;
			int d = 0, e = 1, f = 0;//в этой ф-ии нифига не получилось, поэтому оставил единичную матрицу
			int g = 0, h = 0, i = 1;

			int x = (a * u + b * v + c) / (g * u + h * v + i);//формула для новых координат
			int y = (d * u + e * v + f) / (g * u + h * v + i);

			int indOutput = (abs(y - (height / 2)) * width + (x + (width / 2)));//индекс для перевернутого изображения

			if (indOutput + 3 < size && ind + 3 < size && ind >= 0 && indOutput >= 0)//игнор ошибки, похоже выхожу за границы массива

				for (int z = 0; z < 3; z++) {
					outputImage[indOutput + z] = inputImage[ind + z];//копируем пиксели для трех каналов
				}
		}
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
	//cv::imshow("gray", gray);
	cv::imshow("modified", moified);
	cv::waitKey();
	return 0;
}
