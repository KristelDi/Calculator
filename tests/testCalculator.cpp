#define CATCH_CONFIG_MAIN 
#include "catchUnitLib/catch.hpp"

#include "../include/calculator.h"

#include <algorithm>

double eps0 = 1e-15; // for double comparing


TEST_CASE("Simple actions", "[calculator]") {
	Calculator calc;
	REQUIRE(calc.run("1+2") == 3.);
	REQUIRE(!calc.error);

	REQUIRE(calc.run("1-2") == -1.);
	REQUIRE(!calc.error);

	REQUIRE(calc.run("1*2") == 2.);
	REQUIRE(!calc.error);

	REQUIRE(fabs(calc.run("1./2.") - 0.5) < eps0);
	REQUIRE(!calc.error);
}

TEST_CASE("Actions with null", "[calculator]") {
	Calculator calc;
	REQUIRE(calc.run("3 * 0") == 0.);
	REQUIRE(!calc.error);

	REQUIRE(calc.run("0 / 4") == 0.);
	REQUIRE(!calc.error);

	calc.run("4 / 0");
	REQUIRE(calc.error);
}

TEST_CASE("Wrong symbols", "[calculator]") {
	Calculator calc;

	calc.run("5 + abs");
	REQUIRE(calc.error);

	calc.run("cbs  + 1");
	REQUIRE(calc.error);
}

TEST_CASE("More complicated tests", "[calculator]") {
	Calculator calc;
	REQUIRE(calc.run("((1+2))") == 3.);
	REQUIRE(!calc.error);

	double result = calc.run("(10021231 * 12312 / 129837)");
	REQUIRE(fabs(std::round(result * 100) / 100. - 950279.17) < eps0);
	REQUIRE(!calc.error);
}


TEST_CASE("Examples from the task", "[calculator]") {
	Calculator calc;

	REQUIRE((calc.run("-1 + 5 - 3") == 1.));
	REQUIRE(!calc.error);

	REQUIRE(calc.run("-10 + (8 * 2.5) - (3/1,5)") == 8.);
	REQUIRE(!calc.error);

	REQUIRE(calc.run("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)") == 11.);
	REQUIRE(!calc.error);

	calc.run("1.1 + 2.1 + abc");
	REQUIRE(calc.error);
}


