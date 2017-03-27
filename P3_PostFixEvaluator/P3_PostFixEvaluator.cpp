// P3_PostFixEvaluator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "P3_PostFixEvaluator.h"
#include "PostFixEvaluator.h"

using namespace std;

int main()
{
	int pause;
	string more = "y";

	PostFixEvaluator pfe;
	//pfe.isNumberMethodsTest();

	while (more == "y" || more == "Y")
	{
		pfe.getInput();

		cout << endl << "----------------------------------------------------------";
		cout << endl << "Continue evaluating PostFix expressions? (y/n): ";
		getline(cin, more);
		cout << endl;
	}

	cout << "Thank you for using the PostFix Evaluator!" << endl << endl << "Press any key to exit";
	getchar();
    return 0;
}

