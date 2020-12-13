#include "matrix_ipm.h"
#include <memory>

void matrixipm::ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
{
	int size = width * height * 3;

	for (int ind = 0; ind < size; ind += 3) {//���������� � ����� ��� ������� ��������� �����������

		int u = (ind / 3) % width;//��������� ���������� � 
		int v = (ind / 3) / width;//��������� ���������� y

		int a = m.a, b = m.b, c = m.c;
		int d = m.d, e = m.e, f = m.f;// � ���� ������� ������� ��������� �������� �� 90 ��������, �� ������ �������������� ������ 
		int g = m.g, h = m.h, i = m.i;// (� ���������, ��� ������ ������ � ������ ���������� �������, � ��� ��� ���������� - ����)

		int x = (a * u + b * v + c) / (g * u + h * v + i);//������� ��� ����� ���������
		int y = (d * u + e * v + f) / (g * u + h * v + i);

		int indOutput = ((y * width + x) * 3);//������ ��� ������������� �����������

		if (indOutput + 3 < size && ind + 3 < size && ind >= 0 && indOutput >= 0)//����� ������, ������ ������ �� ������� �������

			for (int z = 0; z < 3; z++) {
				output[indOutput + z] = input[ind + z];//�������� ������� ��� ���� �������
			}
	}
}
