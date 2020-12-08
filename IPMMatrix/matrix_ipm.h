#pragma once

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

	void ipm(unsigned char* input, unsigned char* output, int width, int height, Matr m);
}