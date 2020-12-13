#include "matrix_ipm.h"
#include <memory>

void matrixipm::ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
{
	int size = width * height * 3;

	for (int ind = 0; ind < size; ind += 3) {//перебираем в цикле все пиксели исходного изображения

		int u = (ind / 3) % width;//начальная координата х 
		int v = (ind / 3) / width;//начальная координата y

		int a = m.a, b = m.b, c = m.c;
		int d = m.d, e = m.e, f = m.f;// в этой функции удалось повернуть картинку на 90 градусов, но только проигнорировав ошибку 
		int g = m.g, h = m.h, i = m.i;// (с картинкой, где разные высота и ширина получилось странно, а там где одинаковые - норм)

		int x = (a * u + b * v + c) / (g * u + h * v + i);//формула для новых координат
		int y = (d * u + e * v + f) / (g * u + h * v + i);

		int indOutput = ((y * width + x) * 3);//индекс для перевернутого изображения

		if (indOutput + 3 < size && ind + 3 < size && ind >= 0 && indOutput >= 0)//игнор ошибки, похоже выхожу за границы массива

			for (int z = 0; z < 3; z++) {
				output[indOutput + z] = input[ind + z];//копируем пиксели для трех каналов
			}
	}
}
