#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "PostFixEvaluator.h"


PostFixEvaluator::PostFixEvaluator()
{
}


PostFixEvaluator::~PostFixEvaluator()
{
}

void PostFixEvaluator::getInput()
{
	string value;

	cin >> value;

	//if (!isDouble(value))
	if (value == "+" || value == "-" || value == "*" || value == "/")
	{
		//evaluate(m_Operands, value);
		cout << "Valid operand " << value << endl;
	}
	else if (isNumber(value))
	{
		cout << "Valid number " << value << endl;
		parseTypes(value);
		cout << endl;
	}
	else
	{
		cout << "Not a valid operator or operand" << endl;
	}
}

void PostFixEvaluator::parseTypes(string value)
{
	int int1 = parseNumber<int>(value);
	cout << "\t  as int: " << int1 << endl;

	long long1 = parseNumber<long>(value);
	cout << "\t  as long: " << long1 << endl;

	unsigned long long2 = parseNumber<unsigned long>(value);
	cout << "\t  as unsigned long: " << long2 << endl;

	float float1 = parseNumber<float>(value);
	cout << "\t  as float: " << float1 << endl;

	double double1 = parseNumber<double>(value);
	cout << "\t  as double: " << double1 << endl;
}

// function I created to parse string to see if a valid number exists;
// checks for first character sign (-) or decimal point (.);
// only allows one decimal point character
bool PostFixEvaluator::isNumber(string value)
{
	int startingIndex = 0;
	bool decimalExists = false;

	// check for dash only (minus sign instead of negative sign)
	if (value[0] == '-')
	{
		if (value.length() > 1) { startingIndex = 1; }
		else { return false; }
	}

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
























































