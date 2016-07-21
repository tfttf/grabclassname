#include "stdafx.h"
#include "TestRun.h"
#include "Helper.h"
#include <cassert>

TestRun::TestRun()
{
}


TestRun::~TestRun()
{
}


void TestRun::replace()
{
	// test normal
	{
		Helper h;
		char buf[100] = "abcdefg072fg0115";
		int buflen = strlen(buf);
		char from[100] = "fg0";
		char to[100] = "www";

		h.replace(buf, buflen, from, to);
		assert(strcmp("abcdewww72www115", buf) == 0);
	}

	// test "" string
	{
		Helper h;
		char buf[100] = "abcdefg072fg0115";
		int buflen = strlen(buf);
		char from[100] = "fg0";
		char to[100] = "";

		h.replace(buf, buflen, from, to);
		assert(strcmp("abcde72115", buf) == 0);
	}

	// test can't find
	{
		Helper h;
		char buf[100] = "abcdefg072fg0115";
		int buflen = strlen(buf);
		char from[100] = "fgw";
		char to[100] = "www";

		h.replace(buf, buflen, from, to);
		assert(strcmp("abcdefg072fg0115", buf) == 0);
	}

	// test NULL
	{
		Helper h;
		char buf[100] = "abcdefg072fg0115";
		int buflen = strlen(buf);
		char from[100] = "fgw";
		char *to = NULL;

		h.replace(buf, buflen, from, to);
		assert(strcmp("abcdefg072fg0115", buf) == 0);
	}

}


void TestRun::zerobufWithPattern()
{
	/*
	example:
	buf = "123123";
	zerobufWithPattern(buf,strlen(buf),"31");

	result:
	buf == "12\0\023"

	*/
	// test normal
	{
		Helper h;
		char buf[100] = "123123";
		char dst[100] = "31";

		h.zerobufWithPattern(buf, strlen(buf), dst);
		assert(strcmp("12", buf) == 0 && buf[2] == 0 && buf[3] == 0 && strcmp("23", buf + 3 + 1) == 0 && buf[6] == 0 && buf[7] == 0);

	}

	// test single
	{
		Helper h;
		char buf[100] = "123123";
		char dst[100] = "3";

		h.zerobufWithPattern(buf, strlen(buf), dst);
		assert(strcmp("12", buf) == 0 && buf[2] == 0 && buf[3] == '1' && strcmp("12", buf + 3) == 0 && buf[5] == 0 && buf[6] == 0 && buf[7] == 0);

	}

	// test no find
	{
		Helper h;
		char buf[100] = "123123";
		char dst[100] = "35";

		h.zerobufWithPattern(buf, strlen(buf), dst);
		assert(strcmp("123123", buf) == 0);
	}


}

void TestRun::strcmpIgnoreZero()
{
	/*
	example:
	buf = "123abcefg";
	buf[3] = 0;
	buf[5] = 0;
	dst = "123\0b\0efg";
	ret = strcmpIgnoreZero(buf, dst, 9);

	result:
	ret == true

	*/

	// test normal
	{
		Helper h;
		char buf[100] = "";
		memset(buf, 0, 100);
		strcpy(buf, "123abcefg");
		buf[3] = 0;
		buf[5] = 0;
		char dst[100] = "123\0b\0efg";

		assert(h.strcmpIgnoreZero(buf, dst, 9));
	}

	// caution! this is also return true
	{
		Helper h;
		char buf[100] = "";
		memset(buf, 0, 100);
		strcpy(buf, "123abcefgw");
		buf[3] = 0;
		buf[5] = 0;
		char dst[100] = "123\0b\0efg";

		assert(h.strcmpIgnoreZero(buf, dst, 9));
	}
}