// P3_PostFixEvaluator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include "P3_PostFixEvaluator.h"
#include "PostFixEvaluator.h"

#ifdef _WIN32 || _WIN64
	#include <Windows.h>
	void sleep(unsigned milliseconds) { Sleep(milliseconds); }
	void pause() { system("pause"); }
#else
	#include <unistd.h>
	void sleep(unsigned milliseconds) { usleep(milliseconds * 1000); }
	void pause() { system("read -n1"); }
#endif

using namespace std;


atomic_bool anyKeyPressed(false);
void waitForAnyKey();
void doUntilAnyKeyPressed();


int main()
{
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

	cout << "Thank you for using the PostFix Evaluator!" << endl << endl;

	waitForAnyKey();

    return 0;
}

void waitForAnyKey()
{
	thread waitForKey = thread(doUntilAnyKeyPressed);
	pause();
	anyKeyPressed = true;
	waitForKey.join();
}

void doUntilAnyKeyPressed()
{
	while (!anyKeyPressed)
	{
		sleep(1000);
		cout << ". ";
	}
}