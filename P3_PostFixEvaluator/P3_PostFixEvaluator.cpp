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
	cout << "Hello world!" << endl;

	PostFixEvaluator pfe;

	pfe.testNumberRegex();

	//for (int i = 0; i < 4; i++)
	//{
	//	pfe.getInput();
	//	cout << "----------------------------------------------------------" << endl;
	//}


	cin >> pause;
    return 0;
}

