#pragma once
#include <stack>

using namespace std;

class PostFixEvaluator
{
public:
	PostFixEvaluator();
	virtual ~PostFixEvaluator();

	void getInput();

private:
	stack<double> m_Operands;
	double m_Number;

	float evaluate(stack<double>& operands, string _operator);
	bool isDouble(string value);

	template<class NUMBER_TYPE>
	bool isNumber(string value);

	template<class NUMBER_TYPE>
	NUMBER_TYPE parseNumber(string value);
};

template<class NUMBER_TYPE>
inline bool PostFixEvaluator::isNumber(string value)
{
	bool decimalFound = false;

	// check first position for sign or a digit
	if ((value[0] == '-' && value.length() > 1) || isdigit(value[0]))
	{
		cout << "is a number" << endl;
	}

	for (int i = 1; i < value.length(); i++)
	{
		if (value[i] == '.')  // find one decimal point only
			if (decimalFound)
				return false;
			else
				decimalFound = true;
		else // find first number sign or 
			if (value[0] != '-' || !isdigit(value[i]))
				return false;
	}
	return true;
}

template<class NUMBER_TYPE>
inline NUMBER_TYPE PostFixEvaluator::parseNumber(string value)
{
	stringstream ss;
	NUMBER_TYPE number;

	ss << value;
	ss >> number;

	return number;
}
