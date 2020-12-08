#include "matrix_ipm.h"
#include <memory>

void matrixipm::ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
{
	int size = width * height * 3;
	for (int i = 0; i < size; i++) {//перебираем в цикле все пиксели исходного изображения
		int ovrll = (input[i] + input[i + 1] + input[i + 2]) / 3;//Нахождение среднего арифметического значения B, G, R каналов пикселя
		output[i] = ovrll;//Присваивание среднего арифметического значения B, G, R каналам 
		output[i + 1] = ovrll;
		output[i + 2] = ovrll;
		i += 2;//Переходим к следующим трем каналам 
	}
}
