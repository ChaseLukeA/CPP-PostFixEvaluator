#pragma once
#include <stack>
#include <string>
#include <typeinfo>

using namespace std;

class PostFixEvaluator
{
public:
	PostFixEvaluator();
	virtual ~PostFixEvaluator();

	void getInput();

	void parseTypes(string value);

private:
	stack<double> m_Operands;
	double m_Number;

	float evaluate(stack<double>& operands, string _operator);
	bool isNumber(string value);

	template<class NUMBER_TYPE>
	NUMBER_TYPE parseNumber(string value);
};


template<class NUMBER_TYPE>
inline NUMBER_TYPE PostFixEvaluator::parseNumber(string value)
{
	if (!isNumber(value)) return 0;

	string numberType = string(typeid(NUMBER_TYPE).name());

	if (numberType == "int") return stoi(value);
	if (numberType == "long") return stol(value);
	if (numberType == "unsigned long") return stoul(value);
	if (numberType == "long long") return stoll(value);
	if (numberType == "unsigned long long") return stoull(value);
	if (numberType == "long double") return stold(value);
	if (numberType == "float") return stof(value);
	if (numberType == "double") return stod(value);
	
	return 0;
}
