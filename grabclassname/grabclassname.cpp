// grabclassname.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Helper.h"
#include "Assert.h"
#include <iostream>
using namespace std;




int _tmain(int argc, _TCHAR* argv[])
{
	Helper h;
	Assert a;
	a.assert_argc(argc);

	string cmd = h.makeCmd(argv[1]);
	bool success = h.listfile(cmd.c_str());
	a.assert_load_file_success(success);
	
	std::list<string> filelist = h.dofile("tmp.txt");
	h.show(filelist);

	cout << endl;
	cout << endl;
	cout << "begin list files" << endl;
	for each (string var in filelist)
	{
		//std::list<string> l = h.dofile("d:/1.txt");
		std::list<string> l = h.dofile(const_cast<char*>(var.c_str()));
		h.show(l);
	}
	
	return 0;
}

