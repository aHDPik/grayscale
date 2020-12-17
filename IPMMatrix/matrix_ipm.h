#pragma once

#include <vector>

namespace matrixipm {

	struct Matr {
		double a;
		double b;
		double c;
		double d;
		double e;
		double f;
		double g;
		double h;
		double i;
	};

	struct ImagePoint
	{
		double x;
		double y;
	};

	void ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m);

	void ipm4Points(std::vector<ImagePoint> originalPoints, std::vector<ImagePoint> modifiedPoints, unsigned char* input, unsigned char* output, int width, int height);
}