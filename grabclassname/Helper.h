#pragma once
#include <list>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define HELPER_MAX_LINE_COUNTS 200000
#define HELPER_MAX_BUF_LEN 1000000
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
		//cout << pattern << endl;
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

	/*
		make sure buf has enough space to put (to-start) bytes
		example:

			buf = "111";
			start= "oneword";
			to = start+5;
			addbuf(buf,start,to);

		result:
			buf == "111onewo"
	*/
	static void addbuf(char* buf, char* start, char* to)
	{
		int len = strlen(buf);
		memcpy(buf + len, start, to - start);

	}

	/*
		example:
			buf  = "123";
			ret  = tailof(buf);
		result:
			ret  == buf+3
			*ret == 0
	*/
	static char* tailof(char* buf)
	{
		return buf + strlen(buf);
	}

	static void zerobuf(char* buf, int start, int len)
	{
		for (size_t i = start; i < start+len; i++)
		{
			buf[i] = 0;
		}
	}

	static bool strcmpIgnoreZero(char* buf, char* dst, int dstlen)
	{
		for (size_t i = 0; i < dstlen; i++)
		{
			if (buf[i] != dst[i])
			{
				return false;
			}
		}
		return true;
	}


	/*
		example:
			buf = "123123";
			zerobufWithPattern(buf,strlen(buf),"31");

		result:
			buf == "12\0\023"

	*/
	static void zerobufWithPattern(char* buf, int buflen, char* dst)
	{
		char *newbuf = new char[HELPER_MAX_BUF_LEN];
		memset(newbuf, 0, HELPER_MAX_BUF_LEN);
		strcpy(newbuf, buf);

		int len1 = buflen;

		char* p0 = newbuf;
		char* p1 = buf;
		char* p1_last = p1;
		char* p1_tail = buf + len1;

		//newbuf                                 buf

		//										        p1_last
		//										                   p1_tail
		//      p0									     p1_   p1
		//0000000000000000000000                 abasdfasdfasdfasff

		while (p1 < p1_tail)
		{
			p1 = strstr(p1, dst);
			if (p1 == NULL)
			{
				break;
			}
			else
			{
				zerobuf(newbuf, p1 - buf, strlen(dst));
				p1 = p1 + strlen(dst);
				p1_last = p1;
			}
		}
		memcpy(buf, newbuf, strlen(buf));
		delete[] newbuf;
		newbuf = NULL;
	}



	static void replace(char* buf, int buflen, char* from, char* to)
	{
		char *newbuf = new char[HELPER_MAX_BUF_LEN];
		memset(newbuf, 0, HELPER_MAX_BUF_LEN);

		int len1 = buflen;

		char* p0 = newbuf;
		char* p1 = buf;
		char* p1_last = p1;
		char* p1_tail = buf + len1;
		
		//newbuf                                 buf
		
		//										        p1_last
		//										                   p1_tail
		//      p0									     p1_   p1
		//0000000000000000000000                 abasdfasdfasdfasff

		while (p1 < p1_tail)
		{
			p1 = strstr(p1, from);
			if (p1 == NULL)
			{
				strcat(newbuf, p1_last);
				p1 += strlen(p1_last);
				p1_last = p1;
				p0 = tailof(newbuf);
				break;
			}
			else
			{
				addbuf(newbuf, p1_last, p1);
				strcat(newbuf, to);
				p0 = tailof(newbuf);
				p1 = p1 + strlen(from);
				p1_last = p1;
			}
		}


		memset(buf, 0, buflen);
		memcpy(buf, newbuf, strlen(newbuf));
		delete[] newbuf;
		newbuf = NULL;
	}


	static void show(std::list<string> l)
	{
		for each (string var in l)
		{
			cout << var << endl;
		}
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

