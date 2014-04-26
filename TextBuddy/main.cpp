//main.cpp
//Defines the entry point for the console application. 

#include "stdafx.h"
#include "TextBuddy.h"

using namespace std;

int main(int argc, char* argv[])
{
	TextBuddy app;
	app.initWithFileNamed(argv[1]);

	return 0;
}