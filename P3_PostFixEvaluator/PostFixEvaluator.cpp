#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "PostFixEvaluator.h"


void PostFixEvaluator::getInput()
{
	string expression;

	cout << "Enter an expression to evaluate:" << endl;
	cin >> expression;

	if (isValidExpression(expression))
		cout << "Valid expression!" << endl;
	else
		cout << "Invalid expression!" << endl;

}

// function I created to parse string to see if a valid number exists;
// checks for first character sign (-) or decimal point (.);
// only allows one decimal point character
bool PostFixEvaluator::isNumber(string value)
{
	int startingIndex = 0;
	bool decimalExists = false;

	// check if starts with dash (negative sign)
	if (value[0] == '-')
	{
		if (value.length() > 1) { startingIndex = 1; }
		else { return false; }
	}

	// check if starts with decimal point
	if (value[0] == '.' && value.length() > 1)
	{
		decimalExists = true;
		startingIndex = 1;
	}

	for (int i = startingIndex; i < value.length(); i++)
	{
		// find one decimal point only
		if (value[i] == '.')
		{
			if (decimalExists) { return false; }
			else { decimalExists = true; }
		}
		// find if character is a digit
		else if (!isdigit(value[i])) { return false; }
	}
	return true;
}

double PostFixEvaluator::parseNumber(string value)
{
	return parseNumberType<double>(value);
}

bool PostFixEvaluator::isOperator(string value)
{
	return value == "+" || value == "-" || value == "*" || value == "/" || value == "%";
}

Operator PostFixEvaluator::parseOperator(string value)
{
	if (!isOperator(value)) throw invalid_argument("Not a valid operator!");

	if (value == "+") return Add;
	if (value == "-") return Subtract;
	if (value == "*") return Multiply;
	if (value == "/") return Divide;
	if (value == "%") return Modulo;
}

bool PostFixEvaluator::isValidExpression(string operands)
{
	istringstream expressionValues(operands);

	while (expressionValues)
	{
		string value;
		expressionValues >> value;
		if (value != "")
			if (!isNumber(value) && !isOperator(value))
				return false;
	}
	return true;
}


	////if (!isDouble(value))
	//if (value == "+" || value == "-" || value == "*" || value == "/")
	//{
	//	//evaluate(m_Operands, value);
	//	//cout << "Valid operand " << value << endl;
	//}
	//else
	//{
	//	auto number = parseNumber<double>(value);

	//	if (number)
	//		//cout << "Valid number " << number << endl;
	//		if (m_Operands.size() < 2)
	//			m_Operands.push(parseNumber<double>(value));
	//		else
	//			cout << "Error: two operands already entered!" << endl;
	//	else
	//		cout << "Not a valid operator or operand" << endl;

	//	//cout << "Valid number " << value << endl;
	//	//parseTypes(value);
	//	//cout << endl;
	//}


//void PostFixEvaluator::parseTypes(string value)
//{
//	int int1 = parseNumber<int>(value);
//	cout << "\t  to int: " << int1 << endl;
//
//	long long1 = parseNumber<long>(value);
//	cout << "\t  to long: " << long1 << endl;
//
//	unsigned long long2 = parseNumber<unsigned long>(value);
//	cout << "\t  to unsigned long: " << long2 << endl;
//
//	float float1 = parseNumber<float>(value);
//	cout << "\t  to float: " << float1 << endl;
//
//	double double1 = parseNumber<double>(value);
//	cout << "\t  to double: " << double1 << endl;
//}
