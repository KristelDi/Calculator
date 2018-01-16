#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

#include "./include/calculator.h"


int main(int argc, char* argv[]) {
	if (argc > 1) {
		Calculator calc;
		double result = calc.run(argv[1]);
		if (calc.error) {
			printf("%s\n", calc.errorMsg.c_str());
		}
		else {
			printf("%.2f\n", result);
		}
	}
	return 0;
}
