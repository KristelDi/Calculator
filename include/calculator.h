#ifndef _KCALCULATOR_H
#define _KCALCULATOR_H

#include <string>
#include <stdio.h>
#include <stack>

enum operationType{
	openBrace = 0,
	closeBrace = 1,
	mult = 2,
	divide = 3,
	plus = 4,
	minus = 5
};

enum symbolType {
	operand,
	operation,
	point,
	wrongType
};


class Calculator
{
private:
	std::stack<double> operands;
	std::stack<operationType> operations;

	void init();

	symbolType getType(char symbol);						// operation or operand
	void processOperand(char symbol, symbolType prevType);
	void processOperation(char symbol);
	void processPoint();
	double getResult();

	// functions for operations
	operationType identifyOperation(char symbol);			// plus, minus, mult or divide
	int getOperationsPriopitet(operationType type);			// for plus and minus: 1, for mult and divide: 2, for openBrace: -1
	bool canPopOperation(int curPriopitet);					
	void popOperation();
	double resultOfOperation(double operand1, double operand2, operationType operation);

	int processPointLevel;	// if we have a point (like 0.13), then we should know the power.
							// for example, for '3' we have processPointLevel = 2;


public:
	Calculator();
	~Calculator();

	double run(std::string expression);
	bool error;								// if something went wrong
	std::string errorMsg;					// message of error
};

#endif //_KCALCULATOR_H