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

	//��ȡ�ļ��е�����
	//app.runfilterWithFile("class.txt", ".cpp;.h;.lua");
	//��ָ���ļ��е�lua������ϵ�����Ϣ
	//app.runCreateDebuginfoFromFileForLua();
	//�Ӽ�������ӵ�����Ϣ
	app.genDebuginfoFromClipboardForCpp();
	//�Ӽ�����ȥ��������Ϣ
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
	char* buf = Helper::load("D:\\1.txt");
	cout << buf << endl;
#else
	
	TestRun t;
	t.replace();
	t.zerobufWithPattern();
	t.strcmpIgnoreZero();

#endif
	
	return 0;
}

