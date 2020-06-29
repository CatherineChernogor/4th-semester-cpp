#include <iostream>
#include "complex.h"
#include <math.h>

using namespace std;

int main()
{
	cout << "Enter a, b, c for ax^2 + bx + c = 0\n";
	float a, b, c;
	cin >> a >> b >> c;
	float D = b * b - 4 * a * c;
	if (D > 0) {
		float x1 = (-b + sqrt(D)) / (2 * a);
		float x2 = (-b - sqrt(D)) / (2 * a);
		cout << "x1: " << x1 << '\n' << "x2: " << x2;
	}
	else if (D == 0) {
		float x = -b / (2 * a);
		cout << "x1,x2: " << x;
	}
	else {
		float d = sqrt(-D);
		
		Complex<double> x1(-b / (2 * a), d / (2 * a));
		Complex<double> x2(-b / (2 * a), -d / (2 * a));
		cout << "x1: " << x1 << '\n' << "x2: " << x2;
	}

	return 0;
}
