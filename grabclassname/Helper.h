#pragma once
#include <windows.h>
#include <list>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

using namespace std;

#define HELPER_MAX_LINE_COUNTS 200000
#define HELPER_MAX_BUF_LEN 1000000
#define HELPER_EVERY_LINE_LENGTH 300
#define HELPER_GET_INDEX_NOT_CHAR_NOT_FOUND -1
#define HELPER_LANGUAGE_C	0
#define HELPER_LANGUAGE_CPP 1
#define HELPER_NORMAL_BUF_LEN 2000


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

	static char* allocbuf(int len)
	{
		char* buf = new char[len];
		memset(buf, 0, len);
		return buf;
	}

	static void deallocbuf(char* & buf)
	{
		if (buf)
		{
			delete[] buf;
			buf = NULL;
		}
	}

	static char* zerobuf(char* buf)
	{
		int len = strlen(buf);
		memset(buf, 0, len);
		return buf;
	}

	static char* zerobuf(char* buf, int len)
	{
		memset(buf, 0, len);
		return buf;
	}

	static char* zerobufof(char* buf, int start, int size)
	{
		memset(buf + start, 0, size);
		return buf;
	}

	static std::list<string> strssub(std::list<string> l, int start, int size)
	{
		char buf[100000] = "";
		std::list<string> ret;
		for each (string var in l)
		{
			zerobuf(buf, 100000);
			strcpy(buf, var.c_str());
			strsub(buf, start, size);
			ret.push_back(buf);
		}
		return ret;
	}

	static void strsub(char* buf, int start, int size)
	{
		int len = strlen(buf);
		if (len < start + size)
		{
			cout << "error: start + size is larger than buf len" << endl;
			return;
		}

		char* handlebuf = allocbuf(len+1);
		if (start > 0)
		{
			memcpy(handlebuf, buf, start);
			strcat(handlebuf, buf + start + size);
		}
		else if (start==0)
		{
			strcat(handlebuf, buf+size);
		}
		else
		{
			cout << "error: start < 0 !" << endl;
			return;
		}

		zerobuf(buf);
		strcpy(buf, handlebuf);
		delete[] handlebuf;
		handlebuf = NULL;

	}

	static void writelistToFile(std::list<string> l, char* filename, char* split)
	{
		FILE *fp = fopen(filename,"w+b");
		assert(fp);
		for each (string var in l)
		{
			fwrite(var.c_str(), 1, strlen(var.c_str()), fp);
			if (split)
			{
				fwrite(split, 1, strlen(split), fp);
			}
		}
		fclose(fp);
	}


	static bool writeStringToFile(std::string str, char* filename)
	{
		FILE *fp = fopen(filename, "w+b");
		if (!fp)
		{
			cout << "error: writeStringToFile() failed." << endl;
			return false;
		}
		assert(fp);
		fwrite(str.c_str(), 1, strlen(str.c_str()), fp);
		fclose(fp);
		return true;
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

	static bool isEndWithString(char* buf, std::list<string> dst)
	{
		bool bFind = false;

		for each (string var in dst)
		{
			int len_buf = strlen(buf);
			int len_dst = strlen(var.c_str());
			if (strcmp(buf + len_buf - len_dst, var.c_str()) == 0)
			{
				return true;
			}
		}
		return false;
	}

	// split with string
	static std::list<string> splitWith(char* buf, char* pattern)
	{
		char* tmpbuf = copyBuf(buf, 2);
		int cline = getLineCounts(tmpbuf);
		int buflen = strlen(tmpbuf);
		std::list<string> lines;
		zerobufWithPattern(tmpbuf, buflen, pattern);

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


	//split with '\r' or '\n'
	static std::list<string> split(char* buf)
	{
		char* tmpbuf = copyBuf(buf, 2);
		int cline = getLineCounts(tmpbuf);
		int buflen = strlen(tmpbuf);
		std::list<string> lines;
		replace(tmpbuf, buflen, '\r', 0);
		replace(tmpbuf, buflen, '\n', 0);

		char** pointers = new char*[HELPER_MAX_LINE_COUNTS];
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

	static bool contains(char* src, char c)
	{
		int len = strlen(src);
		for (int i = 0; i < len; i++)
		{
			if (src[i] == c)
				return true;
		}
		return false;
	}

	static bool isReturnExist(char* buf)
	{
		bool r = contains(buf, '\r');
		if (r == true)
			return true;
		bool n = contains(buf, '\n');
		if (n == true)
			return true;
		return false;
	}

	static bool isReturnAllRs(char* buf)
	{
		int len = strlen(buf);
		bool n = contains(buf, '\n');
		if (n == true)
			return false;
		bool r = contains(buf, '\r');
		if (r == true)
			return true;
		return false;
	}

	static bool isReturnAllNs(char* buf)
	{
		int len = strlen(buf);
		bool r = contains(buf, '\r');
		if (r == true)
			return false;
		bool n = contains(buf, '\n');
		if (n == true)
			return true;
		return false;
	}

	static bool isReturnAllRNs(char* buf)
	{
		bool allr = isReturnAllRs(buf);
		if (allr == true)
			return false;

		bool alln = isReturnAllNs(buf);
		if (alln == true)
			return false;

		std::list<int> list_r = getIndexesMatchChar(buf, '\r');
		std::list<int> list_n = getIndexesMatchChar(buf, '\n');
		bool match = isListEqual(list_r, list_n);
		return match;
	}

	static std::list<int> getIndexesMatchChar(char* buf, char c)
	{
		std::list<int> ret;
		int len = strlen(buf);
		for (size_t i = 0; i < len; i++)
		{
			if (buf[i]==c)
			{
				ret.push_back(i);
			}
		}
		return ret;
	}



	static bool isListEqual(std::list<int> la, std::list<int> lb)
	{
		if (la.size() != lb.size())
			return false;
		std::list<int>::const_iterator cj = lb.begin();
		for (std::list<int>::const_iterator ci = la.begin(); ci != la.end(); ci++,cj++)
		{
			int a = (*ci);
			int b = (*cj);
			if (a != b-1)
				return false;
		}
		return true;
	}




	static bool isReturnClean(char* buf)
	{
		bool e = isReturnExist(buf);
		if (!e)
			return false;
		bool r = isReturnAllRs(buf);
		bool n = isReturnAllNs(buf);
		bool rn = isReturnAllRNs(buf);
		return r || n || rn;
	}

	static std::string replaceAll(std::string src, std::string from, std::string to){
		size_t index = 0;
		std::string ret = src;
		while ((index = ret.find(from, index)) != std::string::npos)
		{
			ret.replace(index, from.length(), to);
			index += to.length();
		}
		return ret;
	}

	static std::string makeReturnsClean(char* buf)
	{
		int len0 = strlen(buf);
		string ret = buf;
		ret = replaceAll(ret, "\r\n", "\n");
		ret = replaceAll(ret, "\r", "\n");
		ret = replaceAll(ret, "\n", "\r\n");

		return ret;
	}



	//split with '\r' or '\n' and return every char including '\r' or '\n'
	static std::list<string> splitRaw(char* buf)
	{
		char* tmpbuf = copyBuf(buf, HELPER_MAX_BUF_LEN);
		int cline = getLineCounts(tmpbuf);
		int buflen = strlen(tmpbuf);
		std::list<string> lines;
		bool containsRNClean = isReturnClean(buf);
		bool containsRN = contains(buf, "\r\n");
		bool containsR = contains(buf, "\r");
		bool containsN = contains(buf, "\n");
		bool oneline = (containsR == false && containsN == false) ? true : false;
		replace(tmpbuf, buflen, '\r', 0);
		replace(tmpbuf, buflen, '\n', 0);


		char** pointers = new char*[HELPER_MAX_LINE_COUNTS];

		if (oneline)
		{
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
		}
		else if (containsRNClean)
		{
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
					lines.push_back("\r\n");
					i += 2;
				}
			}
		}
		else if (containsN)
		{
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
					lines.push_back("\n");
					i += 1;
				}
			}
		}
		else if (containsR)
		{
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
					lines.push_back("\r");
					i += 1;
				}
			}
		}
		else
		{
			int linecount = 0;
			string returnClean = makeReturnsClean(tmpbuf);
			zerobuf(tmpbuf);
			strcpy(tmpbuf, returnClean.c_str());
			int newlen = strlen(tmpbuf);
			replace(tmpbuf, newlen, '\r', 0);
			replace(tmpbuf, newlen, '\n', 0);

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
					lines.push_back("\r\n");
					i += 2;
				}
			}
		}

		delete[] pointers;
		delete[] tmpbuf;
		tmpbuf = NULL;
		return lines;
	}



	//split with clipboard info

	static std::list<string> splitWithClipboard()
	{
		std::string content = getClipboardData();
		const char* poriginal = content.c_str();
		char* buf = copyBuf((char*)(poriginal), 1);
		std::list<string> ret = split(buf);



		delete[]buf;
		buf = NULL;

		return ret;
	}

	//split raw with clipboard info(this method contains \r\n)
	static std::list<string> splitRawWithClipboard()
	{
		std::string content = getClipboardData();
		const char* poriginal = content.c_str();
		char* buf = copyBuf((char*)(poriginal), 1);
		std::list<string> ret = splitRaw(buf);



		delete[]buf;
		buf = NULL;

		return ret;
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

	static bool isFile(char* filename)
	{
		FILE *fp = fopen(filename,"r+b");
		if (!fp)
		{
			return false;
		}
		fclose(fp);
		fp = NULL;
		return true;
	}

	static std::list<string> getFilesFromList(std::list<string> l)
	{
		std::list<string> ret;
		for each (string var in l)
		{
			if (isFile((char*)(var.c_str())))
			{
				ret.push_back(var);
			}
		}

		return ret;
	}


	static std::list<string> getFileListWithExt(char* buf, char* ext)
	{
		std::list<string> filepathlist_raw = split(buf);
		std::list<string> filepathlist = getFilesFromList(filepathlist_raw);
		std::list<string> ret;
		for (std::list<string>::const_iterator ci = filepathlist.begin(); ci != filepathlist.end(); ++ci)
		{
			if (isEndWithString((char*)(ci->c_str()), ext))
			{
				ret.push_back(*ci);
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

	static bool setClipboardData(std::string text)
	{
		if (OpenClipboard(NULL))
		{
			HGLOBAL clipbuffer;
			char * buffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_DDESHARE, text.length() + 1);
			buffer = (char*)GlobalLock(clipbuffer);
			strcpy(buffer, LPCSTR(text.c_str()));
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_TEXT, clipbuffer);
			CloseClipboard();
			return true;
		}
		cout << "error: OpenClipboard() failed." << endl;
		return false;
	}

	static std::string getClipboardData()
	{
		// Try opening the clipboard
		if (!OpenClipboard(nullptr))
		{
			cout << "error: can't open clipboard" << endl; // error
			return "";
		}

		// Get handle of clipboard object for ANSI text
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData == nullptr)
		{
			cout << "error: GetClipboardData(CF_TEXT) failed." << endl; // error
			return "";
		}

		// Lock the handle to get the actual text pointer
		char * pszText = static_cast<char*>(GlobalLock(hData));
		if (pszText == nullptr)
		{
			cout << "error: GlobalLock(hData) failed." << endl;
		}


		// Save text in a string class instance
		std::string text(pszText);

		// Release the lock
		GlobalUnlock(hData);

		// Release the clipboard
		CloseClipboard();

		return text;

	}

	static bool isAllCharsOfStringIn(char *src, char* tofind)
	{
		int len = strlen(src);
		int len_tofind = strlen(tofind);

		for (int i = 0; i < len;i++)
		{
			bool bFind = false;
			for (int j = 0; j < len_tofind; j++)
			{
				if (src[i] == tofind[j])
				{
					bFind = true;
					break;
				}
			}
			if (bFind == false)
			{
				return false;
			}
		}

		return true;
	}

	static bool isBeginWithStringIgnoreBlanks(char* src, char* tofind)
	{
		char* head = strstr(src, tofind);
		if (head)
		{
			char* newbuf = allocbuf(strlen(src)+1);
			memcpy(newbuf, src, head - src);

			bool isclean = isAllCharsOfStringIn(newbuf, " \t");

			delete[] newbuf;
			newbuf = NULL;

			return isclean;
		}
		else
		{
			return false;
		}
	}

	static std::string mergeStringList(std::list<string> l,char* split)
	{
		std::string ret;
		for each (string var in l)
		{
			ret += var;
			if (split)
				ret += split;
		}
		return ret;
	}

	static std::string getFileNameFromFullPath(char* fullpath)
	{
		std::string str = fullpath;
		std::string ret = "";
		int index0 = str.find_last_of("/");
		int index1 = str.find_last_of("\\");
		if (index0 != -1)
		{
			char* buf = allocbuf(HELPER_NORMAL_BUF_LEN);
			strcpy(buf, str.c_str() + index0+1);
			ret = buf;
			deallocbuf(buf);
			return ret;
		}

		if (index1 != -1)
		{
			char* buf = allocbuf(HELPER_NORMAL_BUF_LEN);
			strcpy(buf, str.c_str() + index1+1);
			ret = buf;
			deallocbuf(buf);
			return ret;
		}

		return "";
	}



	static std::string getLuaFunctionName(char* str)
	{
		char* p = strstr(str, "(");


		return "";
	}


	static std::string getLuaFunctionParams(char* str)
	{
		char* p0 = strstr(str, "(");
		char* p1 = strstr(str, ")");
		char* buf = allocbuf(HELPER_NORMAL_BUF_LEN);
		memcpy(buf, p0 + 1, p1 - p0 - 1);
		std::string ret = buf;
		deallocbuf(buf);
		return ret;
	}

	static bool isStringNoBlanks(std::string str)
	{
		int len = str.length();
		const char* buf = str.c_str();
		for (int i = 0; i < len;i++)
		{
			if (buf[i] == ' ')
			{
				return false;
			}
		}
		return true;
	}

	static std::string makeDebugInfoForLua(char* src,char* filename,bool printparam)
	{
		char* buf = allocbuf(HELPER_NORMAL_BUF_LEN);
		char* buffilename = allocbuf(HELPER_NORMAL_BUF_LEN);
		char* bufprint = allocbuf(HELPER_NORMAL_BUF_LEN);


		sprintf(buf, "%s", src);
		strcpy(buffilename, getFileNameFromFullPath(filename).c_str());
		std::string luaparams = getLuaFunctionParams(src);

		if (printparam && luaparams.length()>0 && isStringNoBlanks(luaparams))
		{
			sprintf(bufprint, "    print(\"%-20s\" .. \"   %s\")\n    dump(%s)", buffilename, buf, luaparams.c_str());
		}
		else
		{
			sprintf(bufprint, "    print(\"%-20s\" .. \"   %s\")", buffilename, buf, luaparams.c_str());
		}
		std::string ret = bufprint;

		deallocbuf(buf);
		deallocbuf(buffilename);
		deallocbuf(bufprint);
		return ret;
	}

	static bool contains(char* buf, char c0, char c1)
	{
		int len = strlen(buf);
		for (size_t i = 0; i < len; i++)
		{
			if (buf[i] == c0 || buf[i] == c1)
				return true;
		}
		return false;
	}

	static bool isLastCharBlank(char* buf)
	{
		char comp[HELPER_NORMAL_BUF_LEN] = " \t\r\n\p";
		int len = strlen(buf);
		for (size_t i = 0; i < len; i++)
		{
			if (buf[len - 1] == comp[i])
			{
				return true;
			}
		}
		return false;
	}

	static bool isFirstCharBlankOrSymbol(char* buf)
	{
		char comp[HELPER_NORMAL_BUF_LEN] = " \t\r\n(){}[],.!-_=+`~@#$%^&*|\\\p<>/?;:'\"";
		int len = strlen(buf);
		for (size_t i = 0; i < len; i++)
		{
			if (buf[len-1]==comp[i])
			{
				return true;
			}
		}
		return false;
	}

	static bool isFirstCharBlank(char* buf)
	{
		char comp[HELPER_NORMAL_BUF_LEN] = " \t\r\n\p";
		int len_comp = strlen(comp);

		for (size_t i = 0; i < strlen(comp); i++)
		{
			if (buf[0] == comp[i])
			{
				return true;
			}
		}

		return false;
	}
	static bool isFirstCharBlankOrSymbol(char* buf)
	{
		char comp[HELPER_NORMAL_BUF_LEN] = " \t\r\n(){}[],.!-_=+`~@#$%^&*|\\\p<>/?;:'\"";
		int len_comp = strlen(comp);

		for (size_t i = 0; i < strlen(comp); i++)
		{
			if (buf[0] == comp[i])
			{
				return true;
			}
		}

		return false;
	}

	static bool isCharPrintable(char c)
	{
		return (!(c == '\r' || c == '\n' || c == ' ' || c == '\t' || c == '\p'));
	}

	static bool isCharBlank(char c)
	{
		return (c == '\r' || c == '\n' || c == ' ' || c == '\t' || c == '\p');
	}

	static bool isCharBlankOrSymbol(char c)
	{
		char comp[HELPER_NORMAL_BUF_LEN] = " \t\r\n(){}[],.!-_=+`~@#$%^&*|\\\p<>/?;:'\"";
		int len_comp = strlen(comp);

		for (size_t i = 0; i < strlen(comp); i++)
		{
			if (c == comp[i])
			{
				return true;
			}
		}

		return false;
	}


	static bool containsWord(char* buf, char* word)
	{
		char * p = strstr(buf, word);
		if (!p)
			return false;


		if (buf == p)
		{
			//like:
			//bool fun()
			if (isFirstCharBlank(buf + strlen(word)))
			{
				return true;
			}
		}
		else
		{
			//like:
			//static bool fun()
			if (isFirstCharBlank(p + strlen(word)) && isCharBlank(p[-1]))
			{
				return true;
			}
		}
		return false;
	}


	static std::string copyToString(char* head, char* tail)
	{
		std::string ret;
		if (head == tail)
			return ret;
		char* tmp = allocbuf(HELPER_NORMAL_BUF_LEN);
		memcpy(tmp, head, tail - head);
		ret = tmp;
		deallocbuf(tmp);
		return ret;
	}

	static bool isComment(char* buf)
	{
		char * p0 = strstr(buf, "//");
		char * p1 = strstr(buf, "/*");
		if (p0 == NULL && p1 == NULL)
			return false;
		if (p0)
		{
			std::string str = copyToString(buf, p0);
			isAllCharsOfStringIn();
		}

		if (p1)
		{

		}


	}


	static bool containsStroke(char* buf, char* word)
	{
		char * p = strstr(buf, word);
		if (!p)
			return false;


		if (buf == p)
		{
			//like:
			//bool fun()
			if (isFirstCharBlankOrSymbol(buf + strlen(word)))
			{
				return true;
			}
		}
		else
		{
			//like:
			//static bool fun()
			if (isFirstCharBlankOrSymbol(p + strlen(word)) && isCharBlankOrSymbol(p[-1]))
			{
				return true;
			}
		}
		return false;
	}


	static bool isCppFunction(char* buf)
	{
		//h.contains((char*)((*ci).c_str()), "::") && h.contains((char*)((*ci).c_str()), "(") && (!(h.contains((char*)((*ci).c_str()), "="))) && (!(h.contains((char*)((*ci).c_str()), "#DEBUG:  ")))
		if (containsStroke(buf, "::") && containsStroke(buf, "("))
		{
			return true;
		}
		else
		{
			if (containsStroke(buf, "static") && containsStroke(buf, "("))
			{
				return true;
			}
		}

	}

	static std::string makeDebugInfoForCpp(char* src, char* filename)
	{
		char* buf = allocbuf(HELPER_NORMAL_BUF_LEN);
		char* bufprint = allocbuf(HELPER_NORMAL_BUF_LEN);

		sprintf(buf, "%s", src);

		sprintf(bufprint, "    CCLog(\"#DEBUG:  %-20s\");", buf);

		std::string ret = bufprint;

		deallocbuf(buf);
		deallocbuf(bufprint);
		return ret;
	}


private:
	void _extract()
	{

	}
};

