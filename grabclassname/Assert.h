#pragma once
#include <cassert>
#include <iostream>
using namespace std;
/*
#ifndef NDEBUG
#   define ASSERT(condition, message) \
do { \
if (! (condition)) { \
std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
<< " line " << __LINE__ << ": " << message << std::endl; \
std::terminate(); \
} \
} while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif
*/

class Assert
{
public:
	Assert();
	~Assert();
	static void assert_argc(int argc)
	{
		assert(argc >= 2);
	}

	static void assert_load_file_success(bool b)
	{
		if (!b)
		{
			cout << "error: listfile failed." << endl;
			assert(b);
		}
	}
};

