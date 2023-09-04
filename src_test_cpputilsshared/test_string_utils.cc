/**
 * Testcases for cpputils/cpputilsshared/string_utils.h
 * @author Copyright (c) 2001 - 2023 Martin Oberzalek
 */
#include "string_utils.h"
#include "test_string_utils.h"

using namespace Tools;

template<class t_std_string>
class TestToUpper : public TestCaseBase<bool>
{
	t_std_string input;
	t_std_string output;

public:
	TestToUpper( const t_std_string & input,
			     const t_std_string & output )
	: TestCaseBase<bool>( "Tools::toupper", true ),
	  input( input ),
	  output( output )
	{}

	bool run() override {
		return Tools::toupper(input) == output;
	}
};

std::shared_ptr<TestCaseBase<bool>> test_case_toupper1()
{
	return std::make_shared<TestToUpper<std::string>>("hello","HELLO");
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper2()
{
	return std::make_shared<TestToUpper<std::wstring>>(L"hello",L"HELLO");
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper3()
{
	return std::make_shared<TestToUpper<std::string>>("","");
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper4()
{
	return std::make_shared<TestToUpper<std::wstring>>(L"",L"");
}

template<class t_std_string>
class TestToLower : public TestCaseBase<bool>
{
	t_std_string input;
	t_std_string output;

public:
	TestToLower( const t_std_string & input,
			     const t_std_string & output )
	: TestCaseBase<bool>( "Tools::tolower", true ),
	  input( input ),
	  output( output )
	{}

	bool run() override {
		return Tools::tolower(input) == output;
	}
};

std::shared_ptr<TestCaseBase<bool>> test_case_tolower1()
{
	return std::make_shared<TestToLower<std::string>>("HELLO","hello");
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower2()
{
	return std::make_shared<TestToLower<std::wstring>>(L"HELLO",L"hello");
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower3()
{
	return std::make_shared<TestToLower<std::string>>("","");
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower4()
{
	return std::make_shared<TestToLower<std::wstring>>(L"",L"");
}


