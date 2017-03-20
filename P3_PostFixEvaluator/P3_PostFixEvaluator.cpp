// P3_PostFixEvaluator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "P3_PostFixEvaluator.h"
#include "PostFixEvaluator.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int pause;
	cout << "Hello world!" << endl;

	PostFixEvaluator pfe;

	pfe.getInput();
	pfe.getInput();
	pfe.getInput();
	pfe.getInput();
	pfe.getInput();


	cin >> pause;
    return 0;
}

