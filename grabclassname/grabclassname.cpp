// grabclassname.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Helper.h"
#include "Assert.h"
#include "TestRun.h"
#include "Application.h"
#include <iostream>
using namespace std;

#define IS_RELEASE 1



int _tmain(int argc, _TCHAR* argv[])
{
#if IS_RELEASE
	Application app;
	app.init(argc, argv);
	//app.run();

	app.runfilterWithFile("class.txt", ".cpp;.h;.lua");

#else
	
	TestRun t;
	t.replace();
	t.zerobufWithPattern();
	t.strcmpIgnoreZero();

#endif
	
	return 0;
}

