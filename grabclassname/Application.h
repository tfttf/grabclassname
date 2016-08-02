#pragma once
#include "Helper.h"
#include "Assert.h"
#define APPLICATION_EXT ".cpp;.h;.lua"
typedef std::list<string> StringList;

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


	//generate info from clipboard
	void genDebuginfoFromClipboardForLua()
	{
		std::list<string> content = h.splitWithClipboard();

		for (std::list<string>::const_iterator ci = content.begin(); ci != content.end(); ++ci)
		{
			bool bFind = false;
			//if (strstr((*ci).c_str(), "::")){
			//	bFind = true;
			//}

			if (h.isBeginWithStringIgnoreBlanks((char*)((*ci).c_str()), "function")){
				bFind = true;
			}

			if (bFind)
			{
				std::string str = h.makeDebugInfoForLua((char*)((*ci).c_str()),"  ",true);
				content.insert(std::next(ci,1), str);
			}

		}
		std::string ret = h.mergeStringList(content,"\r\n");
		//h.show(content);
		h.setClipboardData(ret);
	}

	//generate info from clipboard
	void genDebuginfoFromClipboardForCpp()
	{
		std::list<string> content = h.splitWithClipboard();
		int counter = 0;
		for (std::list<string>::const_iterator ci = content.begin(); ci != content.end(); ++ci)
		{
			bool bFind = false;
			std::list<string>::const_iterator ni = std::next(ci, 1);
			//if (strstr((*ci).c_str(), "::")){
			//	bFind = true;
			//}
			//if (h.contains((char*)((*ci).c_str()), "::") && h.contains((char*)((*ci).c_str()), "(") && (!(h.contains((char*)((*ci).c_str()), "="))) && (!(h.contains((char*)((*ci).c_str()), "#DEBUG:  ")))){
			//	bFind = true;
			//}

			//one line
			if (ni == content.end())
			{
				bFind = h.isClassMethodOneline((char*)((*ci).c_str()));
			}
			//tow line
			else
			{
				bFind = h.isClassMethod((char*)((*ci).c_str()), (char*)((*ni).c_str()));
			}



			if (bFind)
			{
				cout << counter<<":";
				std::string str = h.makeDebugInfoForCpp((char*)((*ci).c_str()), "  ");
				content.insert(std::next(ci, 2), str);
			}

		}
		std::string ret = h.mergeStringList(content, "\r\n");
		//h.show(content);
		h.setClipboardData(ret);
	}

	//delete debug info from clipboard
	void deleteDebuginfoFromClipboardForCpp()
	{
		std::list<string> content = h.splitWithClipboard();

		for (std::list<string>::const_iterator ci = content.begin(); ci != content.end(); ++ci)
		{
			bool bFind = false;
			//if (strstr((*ci).c_str(), "::")){
			//	bFind = true;
			//}
			cout << (*ci).c_str() << 1 << endl;
			if (h.contains((char*)((*ci).c_str()), "::")){
				bFind = true;
			}
			cout << (*ci).c_str() << 2 << endl;

			if (bFind)
			{
				std::string str = h.makeDebugInfoForCpp((char*)((*ci).c_str()), "  ");
				content.insert(std::next(ci, 1), str);
			}
			cout << (*ci).c_str() << 3 << endl;

		}
		std::string ret = h.mergeStringList(content, "\r\n");
		//h.show(content);
		h.setClipboardData(ret);
	}



	//generate info from file
	std::string genDebuginfoFromFileForLua(char* filename)
	{
		cout << "handling file: " << filename << endl;
		char* file_buf = h.load(filename);
		std::list<string> content = h.split(file_buf);

		for (std::list<string>::const_iterator ci = content.begin(); ci != content.end(); ++ci)
		{
			bool bFind = false;
			//if (strstr((*ci).c_str(), "::")){
			//	bFind = true;
			//}

			if (h.isBeginWithStringIgnoreBlanks((char*)((*ci).c_str()), "function")){
				bFind = true;
			}

			if (bFind)
			{
				std::string str = h.makeDebugInfoForLua((char*)((*ci).c_str()),filename,true);
				content.insert(std::next(ci, 1), str);
			}

		}
		std::string ret = h.mergeStringList(content,"\r\n");
		//h.show(content);
		//h.setClipboardData(ret);
		h.deallocbuf(file_buf);
		return ret;
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

	bool isStringInList(std::string str, std::list<string> l)
	{
		for each (std::string var in l)
		{
			if (strcmp(str.c_str(), var.c_str()) == 0)
			{
				return true;
			}
		}
		return false;
	}

	void runCreateDebuginfoFromFileForLua()
	{
		a.assert_argc(argc);
		char* content_filelist = h.load("input_filelist.txt");
		char* content_excludelist = h.load("exclude_filelist.txt");
		std::list<string> filelist = h.getFileListWithExt(content_filelist, ".lua");
		std::list<string> excludelist = h.split(content_excludelist);

		for each (std::string var in filelist)
		{
			if (isStringInList(var, excludelist))
			{
				continue;
			}
			char* fname = (char*)(var.c_str());
			std::string result = genDebuginfoFromFileForLua(fname);
			h.writeStringToFile(result, fname);
		}
		//h.writelistToFile(result, "output.txt", "\r\n");
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

