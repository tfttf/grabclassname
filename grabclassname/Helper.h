#pragma once
#include <list>
#include <string>
#include <iostream>
using namespace std;

#define HELPER_MAX_LINE_COUNTS 50000
#define HELPER_EVERY_LINE_LENGTH 300
#define HELPER_GET_INDEX_NOT_CHAR_NOT_FOUND -1
#define HELPER_LANGUAGE_C	0
#define HELPER_LANGUAGE_CPP 1

class Helper
{
public:

	Helper::Helper()
	{
	}

	~Helper();


public:
	static std::list<string> split(char* buf)
	{
		char* tmpbuf = copyBuf(buf, 2);
		int cline = getLineCounts(tmpbuf);
		int buflen = strlen(tmpbuf);
		std::list<string> lines;
		replace(tmpbuf, buflen, '\r', 0);
		replace(tmpbuf, buflen, '\n', 0);

		char* pointers[HELPER_MAX_LINE_COUNTS] = { NULL };
		int linecount = 0;
		for (int i = 0; i < buflen;)
		{
			if (tmpbuf[i] != 0)
			{
				pointers[linecount] = tmpbuf + i;
				lines.push_back(pointers[linecount]);
				linecount++;
				i += strlen(tmpbuf + i);
			}
			else
			{
				i += 1;
			}
		}

		delete[] tmpbuf;
		tmpbuf = NULL;
		return lines;
	}

	static char* copyBuf(char* buf, int extlen)
	{
		if (extlen < 0)
		{
			cout << "error: extlen < 0 !" << endl;
			return NULL;
		}
		int len = strlen(buf);
		char* ret = new char[len + extlen];
		memset(ret, 0, len + extlen);
		strcpy(ret, buf);
		return ret;
	}

	static char* copyBuf(char* buf, int len, int extlen)
	{
		if (extlen < 0)
		{
			cout << "error: extlen < 0 !" << endl;
			return NULL;
		}
		char* ret = new char[len + extlen];
		memset(ret, 0, len + extlen);
		strcpy(ret, buf);
		return ret;
	}

	//sample: bool success = listfile("dir \"d:/*\" /s /b > tmp.txt");
	static bool listfile(const char * pattern)
	{
		cout << pattern << endl;
		system(pattern);
		return true;
	}

	static bool isEndWithChar(char* buf, char ch)
	{
		return buf[strlen(buf) - 1] == ch;
	}

	static void ensureEndWithChar(char* buf, char ch)
	{
		if (!isEndWithChar(buf, ch))
		{
			int len = strlen(buf);
			buf[len] = ch;
			buf[len+1] = 0;
		}
	}

	static void endWithChar(char* buf, char ch)
	{
		int len = strlen(buf);
		buf[len] = ch;
		buf[len + 1] = 0;
	}


	static string makeCmd(char* dir)
	{
		char buf[1000] = "";
		if (strcmp(dir, ".") != 0 && strcmp(dir, "..") != 0)
		{
			//normal path like d:/dir_1/
			sprintf(buf, "dir \"%s\" /s /b > tmp.txt", dir);
			ensureEndWithChar(dir, '/');
		}
		else
		{
			//path like . or ..
			sprintf(buf, "dir \"%s\" /s /b > tmp.txt", dir);
		}

		sprintf(buf, "dir \"%s\" /s /b > tmp.txt", dir);
		return string(buf);
	}


	static int getIndexNotChar(char* buf, int len, int start, char ch)
	{
		for (int i = start; i <len; i++)
		{
			if (buf[i] != ch)
				return i;
		}

		return HELPER_GET_INDEX_NOT_CHAR_NOT_FOUND;
	}

	static void replace(char* buf, int buflen, char from, char to)
	{
		for (size_t i = 0; i < buflen; i++)
		{
			if (buf[i] == from)
			{
				buf[i] = to;
			}
		}
	}

	static void show(std::list<string> l)
	{
		for each (string var in l)
		{
			cout << var << endl;
		}
	}

	static std::list<string> dofile(char* filename)
	{
		char* tmp = load(filename);
		if (tmp == NULL)
		{
			std::list<string> null_list;
			return null_list;
		}

		std::list<string> ret = split(tmp);
		delete[]tmp;
		tmp = NULL;
		return ret;
	}

	static bool isEndWithString(char* buf, char* dst)
	{
		int len_buf = strlen(buf);
		int len_dst = strlen(dst);
		if (strcmp(buf+len_buf - len_dst, dst) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static char* load(char* filename)
	{
		if (isFileExist(filename))
		{
			int filesize = Helper::getFileSize(filename);
			FILE *fp = fopen(filename, "r+b");
			char* filedata = new char[filesize + 1];
			memset(filedata, 0, filesize + 1);
			fread(filedata, 1, filesize, fp);
			fclose(fp);
			filedata[filesize] = 0;
			return filedata;
		}
		return NULL;
	}


	static bool contains(char* src, char* target)
	{
		return strstr(src, target) != NULL;
	}


	static int getLineCounts(char* buf)
	{
		int len = strlen(buf);
		int ret = 1;
		for (int i = 0; i < len; i++)
		{
			if (buf[i] == '\n')
			{
				ret++;
			}
		}

		return ret;
	}


	static bool isFileExist(char* filename)
	{
		FILE* fp = fopen(filename, "r+b");
		if (!fp)
		{
			return false;
		}
		else
		{
			fclose(fp);
			fp = NULL;
			return true;
		}
	}



	static int getFileSize(char* filename)
	{
		FILE* fp = fopen(filename, "r+b");
		if (!fp)
		{
			return false;
		}

		fseek(fp, 0, SEEK_END);
		int ret = ftell(fp);
		fclose(fp);
		fp = NULL;

		return ret;
	}



private:
	void _extract()
	{

	}
};

