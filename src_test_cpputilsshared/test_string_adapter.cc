/*
 * test_string_adapter.cc
 *
 *  Created on: 17.09.2024
 *      Author: martin.oberzalek
 */
#include "test_string_adapter.h"
#include <initializer_list>
#include <variant>
#include <CpputilsDebug.h>
#include <format.h>
#include <sstream>
#include <string_adapter.h>
#include <span_vector.h>

using namespace Tools;

using string_t = basic_string_adapter<char,span_vector<char>>;

namespace std {
std::ostream & operator<<( std::ostream & out, const string_t & s )
{
	out << "[" << s.size() << "]";

	out << "{";
	out << std::string_view(s);
	out << "}";

	return out;
}


} // namespace std


namespace {

template <std::size_t N, typename ret_type>
struct TestEqualToString : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<string_t,std::string>;
	typedef std::function<ret_type(CONTAINER&)> Func;
	Func func;

	TestEqualToString( const std::string & descr, Func func, bool throws_exception = false )
	: TestCaseBase<bool>( descr, true, throws_exception ),
	  func( func )
	{}

    bool run() override
    {

    	std::array<char,N> data;
    	span_vector<char> sv(data.data(),data.size());
    	string_t c( sv );
    	std::string v;

    	CONTAINER cc = c;
    	CONTAINER cv = v;

        auto ret1 = func( cc );
        auto ret2 = func( cv );

        if( ret1 != ret2 ) {
        	CPPDEBUG( Tools::format( "FAILED: '%s' {%d}(span_vector<%d>) ret: %d != %d '%s' {%d}(vector)",
        			std::get<0>(cc),
					std::get<0>(cc).size(),
					N,
					ret1,
					ret2,
					std::get<1>(cv),
					std::get<1>(cv).size() ) );
        	return false;
        }

        return true;
    }
};


} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_constructor_1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>> s(v);

		return std::strcmp( a.data(), v.data() ) == 0;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_capacity_1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>> s(v);

		return s.capacity() == a.size() -1;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_max_size_1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>> s(v);

		return s.max_size() == a.size() -1;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>> s(v);
		s.reserve(8);

		return true;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>,static_string_out_of_range_cut> s(v);
		s.reserve(15);

		return true;
	}, false );
}


std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		basic_string_adapter<char,span_vector<char>,static_string_out_of_range_except> s(v);
		s.reserve(15);

		return true;
	}, true );
}


std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_replace_1()
{
	return std::make_shared<TestEqualToString<20,bool>>(__FUNCTION__, []( auto & v ) {
		std::visit( []( auto & s ) {
			s = "Hello";
			s.replace( 2, 2, "xx" );
		}, v);
		return true;
	}, false );
}

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_replace_2()
{
	return std::make_shared<TestEqualToString<20,bool>>(__FUNCTION__, []( auto & v ) {
		std::visit( []( auto & s ) {
			s = "Hello";
			s.replace( 2, 2, "x" );
		}, v);
		return true;
	}, false );
}


std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_replace_3()
{
	return std::make_shared<TestEqualToString<20,bool>>(__FUNCTION__, []( auto & v ) {
		std::visit( []( auto & s ) {
			s = "Hello";
			s.replace( 2, 2, "xxxxxxx" );
		}, v);
		return true;
	}, false );
}

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_replace_4()
{
	return std::make_shared<TestEqualToString<20,bool>>(__FUNCTION__, []( auto & v ) {
		std::visit( []( auto & s ) {
			s = "%%";
			s.replace( 0, 2, "%" );
		}, v);
		return true;
	}, false );
}

