#include "4PointAlg.h"
#include <memory>
#include <iostream>

void points(Matr m)
{
	m.i = 0;
	int u0 = 0, v0 = 0, u1 = 1, v1 = 0, u2 = 1, v2 = 1, u3 = 0, v3 = 1;
	int x0 = 0, y0 = 0, x1 = 1, y1 = 0, x2 = 1, y2 = 1, x3 = 0, y3 = 1;
	int del_x1 = x1 - x2, del_x2 = x3 - x2, del_y1 = y1 - y2, del_y2 = y3 - y2;
	int sum_x = x0 - x1 + x2 - x3, sum_y = y0 - y1 + y2 - y3;
	if (sum_x == 0 && sum_y == 0)
		m.a = x1 - x0, m.b = x2 - x1, m.c = x0, m.d = y1 - y0, m.e = y2 - y1, m.f = y0, m.g = 0, m.h = 0;
	else {
		m.g = (sum_x * del_y2 - del_x2 * sum_y) / (del_x1 * del_y2 - del_x2 * del_y1);
		m.h = (del_x1 * sum_y - sum_x * del_y1) / (del_x1 * del_y2 - del_x2 * del_y1);
		m.a = x1 - x0 + m.g * x1, m.b = x3 - x0 + m.h * x3, m.c = x0;
		m.d = y1 - y0 + m.g * y1, m.e = y3 - y0 + m.h * y3, m.f = y0;
	}
}
