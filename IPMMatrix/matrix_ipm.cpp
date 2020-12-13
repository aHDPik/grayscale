#include "matrix_ipm.h"
#include <memory>

void matrixipm::ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
{
	int size = width * height * 3;//размер картинки
	for (int indOut = 0; indOut < size; indOut += 3) {//проходим по всем пикселям изображения
		int x = (indOut / 3) % width;//координата x выходного изображения
		int y = (indOut / 3) / width;//координата y выходного изображения

		int a = m.a, b = m.b, c = m.c;
		int d = m.d, e = m.e, f = m.f;//матрица для преобразования
		int g = m.g, h = m.h, i = m.i;

		int A = e * i - f * h, B = c * h - b * i, C = b * f - c * e;
		int D = f * g - d * i, E = a * i - c * g, F = c * d - a * f;//обратная матрица
		int G = d * h - e * g, H = b * g - a * h, I = a * e - b * d;

		int u = (A * x + B * y + C) / (G * x + H * y + I);//координата x входного изображения
		int v = (D * x + E * y + F) / (G * x + H * y + I);//координата н входного изображения

		int indIn = ((v * width + u) * 3);//индекс для входного изображения
		if (indIn >= 0 && indIn < size) {
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
