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
#if IS_RELEASE==1
	Application app;
	app.init(argc, argv);
	//app.run();

	//获取文件中的类名
	//app.runfilterWithFile("class.txt", ".cpp;.h;.lua");
	app.runCreateDebuginfoFromClipboardForLua();
#elif IS_RELEASE==2
	// test std::next()
	/*
	std::list<int> v{ 3, 1, 4 };

	auto it = v.begin();
	auto nx = it;
	//auto nx = std::next(it, 2);

	std::cout << *it << ' ' << *nx << '\n';

	*/


	// test Helper::getFileNameFromFullPath()
	//cout<<Helper::getFileNameFromFullPath("D:\\work\\mobile\\prj.plane01\\2_develop\\client\\scripts\\config.lua")<<endl;


#else
	
	TestRun t;
	t.replace();
	t.zerobufWithPattern();
	t.strcmpIgnoreZero();

#endif
	
	return 0;
}

