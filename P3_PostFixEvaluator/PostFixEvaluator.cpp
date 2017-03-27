#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "PostFixEvaluator.h"

#include <regex>

void PostFixEvaluator::getInput()
{
	string expression;

	system("cls");
	cout << endl;

	cout << "Enter an expression to evaluate:" << endl << endl;
	getline(cin, expression);

	system("cls");
	cout << endl;

	if (isValidExpression(expression))
	{
		cout << "Valid expression:" << endl << endl;
		cout << expression << " = " << evaluateExpression(expression) << endl;
	}
	else
	{
		cout << "Invalid expression!" << endl << endl;
		cout << "Please try again!" << endl;
	}
}

// function I created to parse string to see if a valid number exists (without using regex)
// using this number format: (+|-)#.#(e|E(+|-)#)
bool PostFixEvaluator::isNumber(string value)
{
	int size = value.length();
	int start;
	bool decimalExists = false;
	bool exponentExists = false;
	int exponentIndex = -1;
	int lastNumberIndex = -1;

	// check for empty string or these characters
	if (value == "" || value == "+." || value == "-.") return false;

	// check if first character decimal point or sign symbol
	switch (value[0])
	{
	case '.':
		decimalExists = true;
	case '+':
	case '-':
		// all three above cases fall through to check if only character
		if (size == 1) return false;

		// start looping through characters at second index
		start = 1;
		break;
	default:
		// start looping through characters at first index
		start = 0;
	}

	for (int i = start; i < size; i++)
	{
		switch (value[i])
		{
		case '.': // character is decimal point
			// no post-exponent decimal point allowed
			if (exponentExists) return false;

			// only one decimal point allowed
			if (decimalExists) return false;

			// decimal now exists
			decimalExists = true;
			break;
		case 'e':
		case 'E': // character is exponent symbol
			// only one exponent symbol allowed
			if (exponentExists) return false;

			// pre-exponent number must exist
			if (lastNumberIndex == -1) return false;

			// exponent now exists at specified index
			exponentExists = true;
			exponentIndex = i;
			break;
		case '+':
		case '-': // character is sign symbol
			// only post-exponent sign symbol allowed
			if (!exponentExists) return false;

			// only immediately post-exponent allowed
			if (exponentIndex != i - 1) return false;

			// cannot be the last character
			if (i == size - 1) return false;
			break;
		default:  // character is digit or not
			if (!isdigit(value[i])) return false;

			// last number exists at index
			lastNumberIndex = i;
			break;
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

void PostFixEvaluator::isNumberMethodsTest()
{
	cout << "Testing all possible number combinations with the isNumber() and isNumberRegex() methods:" << endl;

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

							if (number.length() <= 5) tabs += "\t";

							cout << "'" << number << "'";
							if (isNumber(number))
								cout << tabs << "CODE - VALID!" << endl;
							else
								cout << tabs << "CODE - NaN!!!!!!!!!!!!!!!!!!!" << endl;

							cout << "'" << number << "'";
							if (isNumberRegex(number))
								cout << tabs << "REGX - VALID!" << endl << endl;
							else
								cout << tabs << "REGX - NaN!!!!!!!!!!!!!!!!!!!" << endl << endl;
						}
					}
				}
			}
		}
	}
}

double PostFixEvaluator::parseNumber(string value)
{
	return parseNumberType<double>(value, false);
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
}

bool PostFixEvaluator::isValidExpression(string value)
{
	istringstream expressionValues(value);
	int numberOfOperands = 0;
	bool lastIsOperator = false;

	while (expressionValues)
	{
		string value;
		expressionValues >> value;
		if (value != "")
			if (isNumber(value))
			{ 
				numberOfOperands++;
				lastIsOperator = false;
			}
			else if (isOperator(value))
			{
				// operator must follow at least 2 operands
				if (numberOfOperands >= 2)
				{
					lastIsOperator = true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
	}
	if (!lastIsOperator) return false;

	return true;
}

double PostFixEvaluator::evaluateExpression(string value)
{
	double calculatedValue;

	if (!isValidExpression(value)) return 0;

	istringstream expressionValues(value);

	while (expressionValues)
	{
		string value;
		expressionValues >> value;

		if (isNumber(value))
			m_Operands.push(parseNumber(value));

		if (isOperator(value))
		{
			calculatedValue = calculateExpression(m_Operands, parseOperator(value));
			m_Operands.push(calculatedValue);
		}
	}
	return calculatedValue;
}

double PostFixEvaluator::calculateExpression(stack<double>& operands, Operator op)
{
	double number1, number2;
	number1 = operands.top();
	operands.pop();
	number2 = operands.top();
	operands.pop();

	switch (op)
	{
	case Add:
		return number2 + number1;
	case Subtract:
		return number2 - number1;
	case Multiply:
		return number2 * number1;
	case Divide:
		return number2 / number1;
	}
}

/*
// EXAMPLES TO PASS:

	Infix:  (3 * 3) + 1 * (2 + 6)

	Postfix : 3 3 * 1 + 2  6 + *

	Evaluates to 80

	--------------------------

	Infix : (3 * 3) + 1 + (2 + 6)

	Postfix : 3 3 * 1 + 2  6 + +

	Evaluates to 18

	--------------------------

	Infix : (3 + 2) + (6 + 4) * 2

	Postfix : 3 2 + 2 6 4 + *+

	Evaluates to 25
*/



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
