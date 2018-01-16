#include "../include/calculator.h"

#include <algorithm>


Calculator::Calculator() {

}


Calculator::~Calculator() {

}

symbolType Calculator::getType(char symbol) {
	if (symbol >= '0' && symbol <= '9') {
		return operand;
	} 
	else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')'){
		return operation;
	}
	else if (symbol == '.' || symbol == ',') {
		return point;
	}
	else {
		return wrongType;
	}
}

operationType Calculator::identifyOperation(char symbol) {
	switch (symbol)
	{
	case '+': {
		return plus;
		break;
	}
	case '-': {
		return minus;
		break;
	}
	case '*': {
		return mult;
		break;
	}
	case '/': {
		return divide;
		break;
	}
	case '(': {
		return openBrace;
		break;
	}
	case ')': {
		return closeBrace;
		break;
	}
	default:
		break;
	}
}


int Calculator::getOperationsPriopitet(operationType type) {
	switch (type)
	{
	case openBrace:
		return -1;
		break;
	case closeBrace:
		return 0;
		break;
	case mult:
		return 1;
		break;
	case divide:
		return 1;
		break;
	case plus:
		return 2;
		break;
	case minus:
		return 2;
		break;
	default:
		break;
	}


}

bool Calculator::canPopOperation(int curPriopitet) {
	if (operations.empty()) {
		return false;
	}
	int prevPriopitet = getOperationsPriopitet(operations.top());
	if (prevPriopitet == -1) {
		return false;
	}
	return (prevPriopitet <= curPriopitet);
}

void Calculator::processOperand(char symbol, symbolType prevType) {
	auto curValue = symbol - '0';
	if (processPointLevel > 0 && (!operands.empty())) {
		double prevValue = operands.top();
		operands.pop();
		operands.push(prevValue + curValue / pow(10, processPointLevel));
		processPointLevel++;
		return;
	}
	if (prevType == operand && (!operands.empty())) {
		double prevValue = operands.top();
		operands.pop();
		operands.push(prevValue * 10 + curValue);
		return;
	}
	operands.push(curValue);
}

double Calculator::resultOfOperation(double operand1, double operand2, operationType operation) {
	switch (operation)
	{
	case mult: {
		return operand2 * operand1;
		break;
	}
	case divide: {
		if (fabs(operand1) < 10e-30) {
			error = true;
			errorMsg = "На ноль делить нельзя!\n";
			return 0.;
		}		
		return operand2 / operand1;
		break;
	}
	case plus:	{
		return operand2 + operand1;
		break;
	}
	case minus:	{
		return operand2 - operand1;
		break;
	}
	default:
		break;
	}
	return 0.;
}

void Calculator::popOperation() {
	auto operand1 = operands.top();
	operands.pop();
	auto operand2 = operands.top();
	operands.pop();
	auto operation = operations.top();
	operations.pop();
	auto result = resultOfOperation(operand1, operand2, operation);
	operands.push(result);
}

void Calculator::processOperation(char symbol) {
	auto type = identifyOperation(symbol);
	int prioritet = getOperationsPriopitet(type);
	if (type == closeBrace) {
		auto prevType = operations.top();
		while (prevType != openBrace) {
			popOperation();
			prevType = operations.top();
		}
		operations.pop(); // óäàëèì îòêðûâàþùóþñÿ ñêîáêó
		return;
	}
	while (canPopOperation(prioritet) && (!operations.empty())) {
		prioritet = getOperationsPriopitet(operations.top());
		popOperation();
	}
	operations.push(type);
}

void Calculator::processPoint() {
	processPointLevel++;
}

double Calculator::getResult() {
	while (!operations.empty()) {
		popOperation();
	}
	return operands.top();
}

void Calculator::init() {
	processPointLevel = 0;
	error = false;
	errorMsg = "";
}

double Calculator::run(std::string expression) {

	// delete all spaces
	expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());

	// type of symbols (operation or operand)
	auto prevType = operation;
	auto type = operand;
	// if the first symbol is operation (like "-10+1"), then add 0 before
	auto firstSymbol = expression.at(0);
	if (getType(firstSymbol) == operation && identifyOperation(firstSymbol) != openBrace) {
		processOperand('0', prevType);
	}
	// proceed one symbol
	for (auto it = expression.begin(); it != expression.end(); ++it) {
		if (error) {
			return 0.;
		}
	 	type = getType(*it);
		switch (type)
		{
		case operand: {
				processOperand(*it, prevType);
			break;
		}
		case operation: {
				processOperation(*it);
				processPointLevel = 0;
			break;
		}
		case point: {
				processPoint();
			break;
		}
		case wrongType: {
			// read all wrong symbols and write it in errorMsg
			error = true;
			errorMsg = "Некорректный ввод, строка содержит недопустимое выражение ";
			auto itCur = it;
			while (itCur != expression.end() && getType(*itCur) == wrongType) {
				errorMsg += *itCur;
				itCur++;
			}
			return 0.;
			break;
		}
		default:
			break;
		}
		prevType = type;
	}
	return getResult();
}
