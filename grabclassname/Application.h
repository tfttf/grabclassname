#pragma once
#include "Helper.h"
#include "Assert.h"
#define APPLICATION_EXT ".cpp;.h;.lua"

class Application
{
public:
	static Helper h;
	static Assert a;
	char** argv;
	int argc;

	Application();
	~Application();
	void init(int _argc, char* _argv[])
	{
		argv = _argv;
		argc = _argc;

	}

	void run()
	{
		a.assert_argc(argc);

		string cmd = h.makeCmd(argv[1]);
		bool success = h.listfile(cmd.c_str());
		a.assert_load_file_success(success);

		std::list<string> filelist = dofile("tmp.txt");
		//h.show(filelist);

		cout << endl;
		cout << endl;
		cout << "begin list files" << endl;

		std::list<string> allcontent;
		for each (string var in filelist)
		{
			// this statement is an example of absolute file scan
			// std::list<string> l = h.dofile("d:/1.txt");
			// this statement will search any file
			// std::list<string> l = h.dofile(const_cast<char*>(var.c_str()));
			// this statement will search certain type specified with APPLICATION_EXT
			std::list<string> l = dofileWithExtName(const_cast<char*>(var.c_str()), APPLICATION_EXT);
			//h.show(l);
			allcontent.push_back(var);
			for each (string var1 in l)
			{
				allcontent.push_back(var1);
			}
		}

		//h.show(allcontent);
	}



	/*
		example:
			pointers[100]={"a.cpp","b.h","c.obj"};
			runfilterWithFile("class.txt", ".cpp;.h"
		result:
			ret = {"a.cpp","b.h"}
	*/
	void runfilterWithFile(char* source, char* pattern)
	{
		a.assert_argc(argc);

		//string cmd = h.makeCmd(argv[1]);
		//bool success = h.listfile(cmd.c_str());
		
		//a.assert_load_file_success(success);

		std::list<string> rawlist = dofile(source);
		std::list<string> filelist = h.strssub(rawlist, 0, sizeof(int));
		std::list<string> result;
		//h.show(filelist);

		cout << endl;
		cout << endl;
		cout << "begin list files" << endl;

		std::list<string> patterns = h.splitWith(pattern, ";");
		//	static bool isEndWithString(char* buf, std::list<string> dst)

		for each (string var in filelist)
		{
			if (h.isEndWithString(const_cast<char*>(var.c_str()), patterns))
			{
				result.push_back(var);
			}
		}
		h.show(result);
		h.writelistToFile(result,"output.txt","\r\n");
	}





	static std::list<string> dofile(char* filename)
	{
		char* tmp = h.load(filename);
		if (tmp == NULL)
		{
			std::list<string> null_list;
			return null_list;
		}

		std::list<string> ret = h.split(tmp);
		delete[]tmp;
		tmp = NULL;
		return ret;
	}


	static std::list<string> dofileWithExtName(char* filename, char* optionExt)
	{

		std::list<string> listext = h.splitWith(optionExt, ";");
		bool bFind = false;
		for each (string var in listext)
		{
			if (h.isEndWithString(filename, const_cast<char*>(var.c_str())))
			{
				bFind = true;
			}

		}

		if (bFind)
		{
			char* tmp = h.load(filename);
			if (tmp == NULL)
			{
				std::list<string> null_list;
				return null_list;
			}

			std::list<string> ret = h.split(tmp);
			delete[]tmp;
			tmp = NULL;
			return ret;
		}
		else
		{
			std::list<string> ret;
			return ret;
		}

	}


};

