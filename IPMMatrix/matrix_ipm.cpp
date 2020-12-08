#include "matrix_ipm.h"
#include <memory>

void matrixipm::ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m)
{
	int size = width * height * 3;
	for (int i = 0; i < size; i++) {//���������� � ����� ��� ������� ��������� �����������
		int ovrll = (input[i] + input[i + 1] + input[i + 2]) / 3;//���������� �������� ��������������� �������� B, G, R ������� �������
		output[i] = ovrll;//������������ �������� ��������������� �������� B, G, R ������� 
		output[i + 1] = ovrll;
		output[i + 2] = ovrll;
		i += 2;//��������� � ��������� ���� ������� 
	}
}
