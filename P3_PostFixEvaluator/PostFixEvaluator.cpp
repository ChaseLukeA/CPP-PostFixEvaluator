#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "PostFixEvaluator.h"

#include <regex>

void PostFixEvaluator::getInput()
{
	string expression;

	cout << "Enter an expression to evaluate:" << endl;
	getline(cin, expression);

	if (isValidExpression(expression))
		cout << "Valid expression!" << endl;
		// evaluate expression
	else
		cout << "Invalid expression!" << endl;
		// alert only
}

// function I created to parse string to see if a valid number exists (without using regex)
// using these valid number formats: '#' || '#.#' || '.#' || '-#' || '-#.#' || '-.#'
bool PostFixEvaluator::isNumber(string value)
{
	int startingIndex = 0;
	bool decimalExists = false;

	// check if starts with a dash (negative sign)
	if (value[0] == '-')
	{
		if (value.length() > 1)
			startingIndex = 1;
		else
			return false;
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
			if (!decimalExists)
				decimalExists = true;
			else
				return false;
		}
		// find if character is a digit
		else if (!isdigit(value[i]))
		{
			return false;
		}
	}
	// valid number
	return true;
}

bool PostFixEvaluator::isNumberRegex(string value)
{
	//    +/-     (      .### / ###       /               ###.###               )      e/E      +/-         ###  
	// (\\+|-)?   ( ((\.)?([[:digit:]]+)) | (([[:digit:]]+)(\.)([[:digit:]]+)?) )   ( (e|E)  (\\+|-)?  ([[:digit:]]+) )?
	regex number("(\\+|-)?(((\.)?([[:digit:]]+))|(([[:digit:]]+)(\.)([[:digit:]]+)?))((e|E)(\\+|-)?([[:digit:]]+))?");
	return regex_match(value, number);
}

void PostFixEvaluator::testNumberRegex()
{
	for (int sign = 0; sign < 3; sign++) // signs '', '+', '-'
	{
		for (int firstNum = 0; firstNum < 2; firstNum++) // first number '', '#'
		{
			for (int decimalPoint = 0; decimalPoint < 2; decimalPoint++) // decimal point '', '.'
			{
				for (int secondNum = 0; secondNum < 2; secondNum++) // second number '', '#'
				{
					for (int exponentSymbol = 0; exponentSymbol < 3; exponentSymbol++) // exponent symbol '', 'e', 'E'
					{
						for (int exponentSign = 0; exponentSign < 3; exponentSign++) // exponent sign '', '+', '-'
						{
							string number;
							string tabs = "\t";
							if (sign == 1) number += "+";
							if (sign == 2) number += "-";
							if (firstNum == 1) number += "12";
							if (decimalPoint == 1) number += ".";
							if (secondNum == 1) number += "34";
							if (exponentSymbol == 1) number += "e";
							if (exponentSymbol == 2) number += "E";
							if (exponentSymbol > 0)
							{
								if (exponentSign == 1) number += "+";
								if (exponentSign == 2) number += "-";
								number += "56";
							}

							cout << number;
							if (number.length() < 8) tabs += "\t";

							if (isNumberRegex(number))
								cout << tabs << "VALID!" << endl;
							else
								cout << tabs << "NaN!!!!!!!!!!!!!!!!!!!" << endl;
						}
					}
				}
			}
		}
	}
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
