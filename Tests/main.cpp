
#include "global.h"
#undef main

#include "RageLog.h"
#include "RageUtil.h"

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe(IntToString_function)
{
	
	It(converts_int_to_string)
	{
		Assert::That(IntToString(15), Equals("15"));
	}
	
	It(this_test_should_fail)
	{
		Assert::That(IntToString(20), Equals("15"));
	}
	
};

int main(int argc, const char **argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
