#include "matrix_ipm.h"
#include <memory>

using namespace std;

namespace matrixipm {

	void ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
	{
		int size = width * height * 3;//размер картинки
		for (int indOut = 0; indOut < size; indOut += 3) {//проходим по всем пикселям изображения
			int x = (indOut / 3) % width;//координата x выходного изображения
			int y = (indOut / 3) / width;//координата y выходного изображения

			createInverseMatr(m);

			int u = (m.a * x + m.b * y + m.c) / (m.g * x + m.h * y + m.i);//координата x входного изображения
			int v = (m.d * x + m.e * y + m.f) / (m.g * x + m.h * y + m.i);//координата н входного изображения

			int indIn = ((v * width + u) * 3);//индекс для входного изображения
			if (indIn >= 0 && indIn < size) {//
				for (int k = 0; k < 3; k++) {
					output[indOut + k] = input[indIn + k];//копируем пиксели для трех каналов
				}
			}
			else {
				for (int k = 0; k < 3; k++) {
					output[indOut + k] = 0;//копируем черные пиксели для трех каналов
				}
			}
		}
	}

	void ipm4Points(vector<ImagePoint> originalPoints, vector<ImagePoint> modifiedPoints, unsigned char* input, unsigned char* output, int width, int height)
	{
		Matr ori = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
		Matr mod = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
		Matr res = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
		createMatr(originalPoints, ori);
		createInverseMatr(ori);
		createMatr(modifiedPoints, mod);
		multiplyMatr(mod, ori, res);
		ipm(input, output, width, height, res);
	}

	void createMatr(vector<ImagePoint> points, Matr &matr) 
	{
		double deltaX1 = points[1].x - points[2].x, deltaX2 = points[3].x - points[2].x,
			deltaY1 = points[1].y - points[2].y, deltaY2 = points[3].y - points[2].y,
			sumX = points[0].x - points[1].x + points[2].x - points[3].x,
			sumY = points[0].y - points[1].y + points[2].y - points[3].y;
		if (sumX == 0 && sumY == 0)
		{
			matr.a = points[1].x - points[0].x, matr.b = points[2].x - points[1].x, matr.c = points[0].x,
				matr.d = points[1].y - points[0].y, matr.e = points[2].y - points[1].y, matr.f = points[0].y,
				matr.g = 0, matr.h = 0; matr.i = 1;
		}
		else
		{
			matr.i = 1, matr.g = (sumX * deltaY2 - deltaX2 * sumY) / (deltaX1 * deltaY2 - deltaX2 * deltaY1),
				matr.h = (deltaX1 * sumY - sumX * deltaY1) / (deltaX1 * deltaY2 - deltaX2 * deltaY1),
				matr.a = points[1].x - points[0].x + matr.g * points[1].x,
				matr.b = points[3].x - points[0].x + matr.h * points[3].x,
				matr.c = points[0].x, matr.d = points[1].y - points[0].y + matr.g * points[1].y,
				matr.e = points[3].y - points[0].y + matr.h * points[3].y, matr.f = points[0].y;
		}
	}

	void createInverseMatr(Matr &matr) 
	{
		int a = matr.a, b = matr.b, c = matr.c;
		int d = matr.d, e = matr.e, f = matr.f;//матрица для преобразования
		int g = matr.g, h = matr.h, i = matr.i;

		matr.a = e * i - f * h, matr.b = c * h - b * i, matr.c = b * f - c * e;
		matr.d = f * g - d * i, matr.e = a * i - c * g, matr.f = c * d - a * f;//обратная матрица
		matr.g = d * h - e * g, matr.h = b * g - a * h, matr.i = a * e - b * d;
		
	}

	void multiplyMatr(Matr firstMatr, Matr secondMatr, Matr &resultMatr)
	{
		resultMatr.a = (firstMatr.a * secondMatr.a) + (firstMatr.b * secondMatr.d) + (firstMatr.c * secondMatr.g),
			resultMatr.b = (firstMatr.a * secondMatr.b) + (firstMatr.b * secondMatr.e) + (firstMatr.c * secondMatr.h),
			resultMatr.c = (firstMatr.a * secondMatr.c) + (firstMatr.b * secondMatr.f) + (firstMatr.c * secondMatr.i),
			resultMatr.d = (firstMatr.d * secondMatr.a) + (firstMatr.e * secondMatr.d) + (firstMatr.f * secondMatr.g),
			resultMatr.e = (firstMatr.d * secondMatr.b) + (firstMatr.e * secondMatr.e) + (firstMatr.f * secondMatr.h),
			resultMatr.f = (firstMatr.d * secondMatr.c) + (firstMatr.e * secondMatr.f) + (firstMatr.f * secondMatr.i),
			resultMatr.g = (firstMatr.g * secondMatr.a) + (firstMatr.h * secondMatr.d) + (firstMatr.i * secondMatr.g),
			resultMatr.h = (firstMatr.g * secondMatr.b) + (firstMatr.h * secondMatr.e) + (firstMatr.i * secondMatr.h),
			resultMatr.i = (firstMatr.g * secondMatr.c) + (firstMatr.h * secondMatr.f) + (firstMatr.i * secondMatr.i);
	}

}

	
