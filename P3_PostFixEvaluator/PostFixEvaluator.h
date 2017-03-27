#pragma once
#include <stdexcept>
#include <stack>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

// friendly names for the 4 common arithmetic operators
enum Operator
{
	Add = 1,
	Subtract = 2,
	Multiply = 3,
	Divide = 4
};

class PostFixEvaluator
{
public:
	PostFixEvaluator() {}
	virtual ~PostFixEvaluator() {}

	void getInput();
	bool isNumberRegex(string value);
	void isNumberMethodsTest();

private:
	stack<double> m_Operands;

	bool isValidExpression(string value);
	double evaluateExpression(string value);
	double calculateExpression(stack<double>& operands, Operator op);

	bool isNumber(string value);
	double parseNumber(string value);

	bool isOperator(string value);
	Operator parseOperator(string value);

	template<class NUMBER_TYPE>
	NUMBER_TYPE parseNumberType(string value, bool useNewMethods);
};

// generic function I wrote to parse any specified number type
// from a string using the STL functions; can use the new C++11 'sto?'
// methods by specifying 'true' after the value; default behavior
// uses the STL 'ato?' functions
template<class NUMBER_TYPE>
inline NUMBER_TYPE PostFixEvaluator::parseNumberType(string value, bool useNewMethods = false)
{
	if (!isNumber(value)) throw std::invalid_argument("Not a number!");

	// add '0' before decimal point if none exists;
	// this prevents crash when converting to int/etc
	if (value[0] == '.' && value.length() > 1)
		value.replace(0, 1, "0.");
	if (value[0] == '-' && value[1] == '.' && value.length() > 2)
		value.replace(1, 1, "0.");

	string numberType = typeid(NUMBER_TYPE).name();

	if (useNewMethods) // use C++11 methods
	{
		if (numberType == "int") return stoi(value);
		if (numberType == "long") return stol(value);
		if (numberType == "unsigned long") return stoul(value);
		if (numberType == "long long") return stoll(value);
		if (numberType == "unsigned long long") return stoull(value);
		if (numberType == "long double") return stold(value);
		if (numberType == "float") return stof(value);
		if (numberType == "double") return stod(value);
	}
	else // use pre C++11 methods
	{
		if (numberType == "int") return atoi(value.c_str());
		if (numberType == "long") return atol(value.c_str());
		if (numberType == "long long") return atoll(value.c_str());
		if (numberType == "double") return atof(value.c_str());
	}
	
	throw std::invalid_argument("No valid numeric type was provided!");
}
