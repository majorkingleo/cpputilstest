/**
 * Testcases for cpputils/cpputilsshared/string_utils.h
 * @author Copyright (c) 2001 - 2023 Martin Oberzalek
 */
#include "string_utils.h"
#include "test_string_utils.h"
#include <format.h>
#include <CpputilsDebug.h>

using namespace Tools;

auto test_upper_equal = []( const auto & a, const auto & b) { return toupper(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_toupper1() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"hello","HELLO",test_upper_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper2() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"hello",L"HELLO",test_upper_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper3() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"","",test_upper_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_toupper4() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"",L"",test_upper_equal);
}



auto test_lower_equal = []( const auto & a, const auto & b) { return tolower(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_tolower1() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"HELLO","hello",test_lower_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower2() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"HELLO",L"hello",test_lower_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower3() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"","",test_lower_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_tolower4() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"HELLO",L"hello",test_lower_equal);
}



auto test_strip_equal = []( const auto & a, const auto & b) { return strip(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_strip1() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," ","",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip2() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"","",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip3() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello","hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip4() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello ","hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip5() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" ",L"",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip6() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"",L"",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip7() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello",L"hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip8() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello ",L"hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip9() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello hello ",L"hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip10() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello hello ","hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip11() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello ",L"hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip12() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello ","hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip13() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello \n",L"hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip14() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello \n","hello hello",test_strip_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip15() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello \r\n","hello hello",test_strip_equal);
}

auto test_strip_view_equal = []( const auto & a, const auto & b) { return strip_view(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view1() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," ","",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view2() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__,"","",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view3() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," hello","hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view4() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," hello ","hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view5() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" ",L"",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view6() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L"",L"",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view7() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" hello",L"hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view8() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" hello ",L"hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view9() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" hello hello ",L"hello hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view10() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," hello hello ","hello hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view11() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" \thello hello ",L"hello hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view12() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," \thello hello ","hello hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view13() {
	return std::make_shared<TestCaseFuncEqual<std::wstring_view>>(__FUNCTION__,L" \thello hello \n",L"hello hello",test_strip_view_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_view14() {
	return std::make_shared<TestCaseFuncEqual<std::string_view>>(__FUNCTION__," \thello hello \n","hello hello",test_strip_view_equal);
}



auto test_strip_leading_equal = []( const auto & a, const auto & b) { return strip_leading(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading1() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," ","",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading2() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"","",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading3() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello","hello",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading4() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello ","hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading5() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" ",L"",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading6() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"",L"",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading7() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello",L"hello",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading8() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello ",L"hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading9() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello hello ",L"hello hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading10() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello hello ","hello hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading11() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello ",L"hello hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading12() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello ","hello hello ",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading13() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello \n",L"hello hello \n",test_strip_leading_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_leading14() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello \n","hello hello \n",test_strip_leading_equal);
}



auto test_strip_trailing_equal = []( const auto & a, const auto & b) { return strip_trailing(a) == b; };

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing1() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," ","",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing2() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__,"","",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing3() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello"," hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing4() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello "," hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing5() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" ",L"",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing6() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L"",L"",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing7() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello",L" hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing8() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello ",L" hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing9() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" hello hello ",L" hello hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing10() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," hello hello "," hello hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing11() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello ",L" \thello hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing12() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello "," \thello hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing13() {
	return std::make_shared<TestCaseFuncEqual<std::wstring>>(__FUNCTION__,L" \thello hello \n",L" \thello hello",test_strip_trailing_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_strip_trailing14() {
	return std::make_shared<TestCaseFuncEqual<std::string>>(__FUNCTION__," \thello hello \n"," \thello hello",test_strip_trailing_equal);
}


auto test_is_int_equal = []( const auto & a ) { return is_int(a); };

std::shared_ptr<TestCaseBase<bool>> test_case_is_int1() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__,"1",true,test_is_int_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_is_int2() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__,"1234567890",true,test_is_int_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_is_int3() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__,"",false,test_is_int_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_is_int4() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__,"abcdef",false,test_is_int_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_is_int5() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__," ",false,test_is_int_equal);
}

std::shared_ptr<TestCaseBase<bool>> test_case_is_int6() {
	return std::make_shared<TestCaseFuncBool<std::string>>(__FUNCTION__,"\t\n",false,test_is_int_equal);
}

namespace {

	template<class t_std_string=std::string>
	class TestSplitStringBase : public TestCaseBase<bool>
	{
	public:
		struct TestData {
			t_std_string input;
			std::vector<t_std_string> expected_output;
			t_std_string seperator;
			int max = -1;
		};

	protected:
		std::vector<TestData> test_data;		

	public:
		TestSplitStringBase( const std::string & name, const std::vector<TestData> & test_data_ )
		: TestCaseBase<bool>( name, true ),
		  test_data( test_data_ )
		  {}

	public:
	};

	template<class t_std_string=std::string>
	class TestSplitString : public TestSplitStringBase<t_std_string>
	{	
	public:
		using base = TestSplitStringBase<t_std_string>;
		using TestData = typename base::TestData;

	public:
		TestSplitString( const std::string & name,
			const std::vector<TestData> & test_data_ )
		: TestSplitStringBase<t_std_string>( name, test_data_ )
		  {}

	public:
		bool run() override
		{
			for( const auto & td : base::test_data ) {
				auto output = Tools::split_simple( td.input, td.seperator, td.max );

				if( output != td.expected_output ) {
					CPPDEBUG( Tools::format( "FAILED: '%s' sep: '%s' max: %d ret: %s != %s ",
							td.input,
							td.seperator,
							td.max,
							IterableToCommaSeparatedString(output),
							IterableToCommaSeparatedString(td.expected_output) ) );
					return false;
				}			
			}

			return true;
		}
	};

	template<class t_std_string=std::wstring>
	class TestSplitWString : public TestSplitStringBase<t_std_string>
	{
	public:
		using base = TestSplitStringBase<t_std_string>;
		using TestData = typename base::TestData;		

	public:
		TestSplitWString( const std::string & name, const std::vector<TestData> & test_data_ )
		: TestSplitStringBase<t_std_string>( name, test_data_ )
		  {}

	public:
		bool run() override
		{
			for( const auto & td : base::test_data ) {
				auto output = split_string( td.input, td.seperator, td.max );

				if( output != td.expected_output ) {					
					CPPDEBUG( Tools::wformat( L"FAILED: '%s' sep: '%s' max: %d ret: %s != %s ",
							td.input,
							td.seperator,
							td.max,
							IterableToCommaSeparatedWString(output),
							IterableToCommaSeparatedWString(td.expected_output) ) );							
					return false;
				}			
			}

			return true;
		}
	};	
} // namespace

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_split_string() {


	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;


	ret.push_back( std::make_shared<TestSplitString<std::string>>( __FUNCTION__, std::vector<TestSplitString<std::string>::TestData>{
		{ "a,b,c", { "a", "b", "c" }, "," },
		{ "a,,c", { "a", "", "c" }, "," },
		{ ",b,c", { "", "b", "c" }, "," },
		{ "a,b,", { "a", "b", "" }, "," },
		{ ",,", { "", "", "" }, "," },
		{ "", { "" }, "," },
		{ "abc", { "abc" }, "," },
		{ "abc", { "abc" }, "," },
		{ "a,b,c", { "a", "b,c" }, ",", 2 },
		{ "a,b,c", { "a", "b", "c" }, ",", 10 },
	} ) );

	ret.push_back( std::make_shared<TestSplitWString<std::wstring>>( __FUNCTION__, std::vector<TestSplitWString<std::wstring>::TestData>{
		{ L"a,b,c", { L"a", L"b", L"c" }, L"," },
		{ L"a,,c", { L"a", L"", L"c" }, L"," },
		{ L",b,c", { L"", L"b", L"c" }, L"," },
		{ L"a,b,", { L"a", L"b", L"" }, L"," },
		{ L",,", { L"", L"", L"" }, L"," },
		{ L"", { L"" }, L"," },
		{ L"abc", { L"abc" }, L"," },
		{ L"abc", { L"abc" }, L"," },
		{ L"a,b,c", { L"a", L"b,c" }, L",", 2 },
		{ L"a,b,c", { L"a", L"b", L"c" }, L",", 10 },
	} ) );

	return ret;
}