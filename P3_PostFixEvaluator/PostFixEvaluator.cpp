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
	else if (isNumber<double>(value))
	{
		cout << "Valid number " << value << endl;
	}
	else
	{
		cout << "Not a valid operator or operand" << endl;
	}

}


bool PostFixEvaluator::isDouble(string value)
{
	stringstream ss;
	double num;

	ss << value;
	ss >> num;

	return ss.good();
}

