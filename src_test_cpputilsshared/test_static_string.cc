/**
 * Testcases for cpputils/cpputilsshared/CyclicArray.h
 * @author Copyright (c) 2023 Martin Oberzalek
 */
#include "static_string.h"
#include "test_static_string.h"
#include "ColoredOutput.h"
#include <initializer_list>
#include <variant>
#include <CpputilsDebug.h>
#include <format.h>
#include <sstream>

using namespace Tools;

namespace {

template<std::size_t N,class T>
bool operator==( const static_basic_string<N,T> & c, const std::basic_string<T> & v )
{
    if( c.size() != v.size() ) {
    	// CPPDEBUG( format("c.size != v.size => %d != %d", c.size(), v.size()) );
        return false;
    }

    for( unsigned i = 0; i < c.size(); i++ ) {
        if( c[i] != v[i] ) {
            return false;
        }
    }

    return true;
}

} // namespace

#if 0
namespace std {
template <std::size_t N, class T>
std::ostream & operator<<( std::ostream & out, const static_basic_string<N,T> & cstring )
{
	out << "[" << cstring.size() << "," << cstring.max_size() << "]";

	out << "{";

	out << cstring.c_str();

	out << "}";

	return out;
}
} // namespace std
#endif

namespace {

template <std::size_t N,class T>
struct TestEqualToString : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<static_basic_string<N,T>,std::basic_string<T>>;
	typedef std::function<void(CONTAINER&)> Func;
	Func func;

	static_basic_string<N,T> c;
    std::basic_string<T>   v;

    TestEqualToString( const std::string & descr, Func func, std::initializer_list<T> list = {'h','e','l','l','o'} )
	: TestCaseBase<bool>( descr, true, false ),
	  func( func ),
	  c(list),
	  v(list)
	{}

    bool run() override
    {
    	CONTAINER cc = c;
    	CONTAINER cv = v;

        func( cc );
        func( cv );

        return std::get<0>(cc) == std::get<1>(cv);
    }
};


struct TestBool : public TestCaseBase<bool>
{
	typedef std::function<bool()> Func;
	Func func;

    TestBool( const std::string & descr, Func func, bool throws_exception = false )
	: TestCaseBase<bool>( descr, true, throws_exception ),
	  func( func )
	{}

    bool run() override
    {
        return func();
    }
};


template <std::size_t N,class T>
struct TestEqualConv : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<static_basic_string<N,T>,std::basic_string<T>>;
	typedef std::function<std::string(CONTAINER&)> Func;
	Func func;

	static_basic_string<N,T> c;
    std::basic_string<T>   v;

    TestEqualConv( const std::string & descr, Func func )
	: TestCaseBase<bool>( descr, true, false ),
	  func( func ),
	  c(),
	  v()
	{}

    bool run() override
    {
    	CONTAINER cc = c;
    	CONTAINER cv = v;

        auto res_cc = func( cc );
        auto res_cv = func( cv );

        return res_cc == res_cv;
    }
};

} // namespace


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_constructor_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & text ) {
					 return ( std::string(text) == static_string<20>(text) );
				 };

				 return cmp( "aaa" ) &&
						cmp( std::string_view("aaa") ) &&
						cmp( std::string("aaa") ) &&
						cmp( std::initializer_list({ 'a', 'b', 'c' }) );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_constructor_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 std::string_view sv = "hello";
				 auto it_a = sv.begin();
				 it_a++;

				 auto it_b = sv.end();
				 it_b--;

				 return ( static_string<20>( static_string<20>("aaa") ) == std::string( std::string("aaa") ) ) &&
						( static_string<20>( 10, 'A' ) == std::string( 10, 'A' ) ) &&
						( static_string<20>( "A", 10 ) == std::string( "A" ,10 ) ) &&
						( static_string<20>( sv.begin(), sv.end() ) == std::string( sv.begin(), sv.end() ) ) &&
						( static_string<20>( it_a, it_b ) == std::string( it_a, it_b ) ) &&
						( static_string<20>( sv, 1, 10 ) == std::string( sv, 1, 10 ) );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_capacity_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 return ( static_string<20>().capacity() == 20 ) &&
						( static_string<10>().capacity() == 10 );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_max_size_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 return ( static_string<20>().max_size() == 20 ) &&
						( static_string<10>().max_size() == 10 );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_reserve_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {

				auto a = static_basic_string<20,char,static_string_out_of_range_cut>();
				a.reserve(40);

				return a.max_size() == 20;

			}, false);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_reserve_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {

				auto a = static_basic_string<20,char,static_string_out_of_range_except>();
				a.reserve(40);

				return a.max_size() == 20;

			}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {

				auto a = static_basic_string<20,char,static_string_out_of_range_except>();
				a.resize(40);

				return a.max_size() == 20;

			}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {

				auto a = static_basic_string<20,char,static_string_out_of_range_cut>();
				a.resize(40);

				return a.max_size() == 20;

			}, false);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp1 = []( const char* text, std::size_t n ) {
					 std::string a( text );
					 a.resize( n );

					 static_string<20> b( text );
					 b.resize( n );

					 return a == b;
				 };

				 auto cmp2 = []( const char* text, std::size_t n, char ch ) {
					 std::string a( text );
					 a.resize( n, ch );

					 static_string<20> b( text );
					 b.resize( n, ch );

					 return a == b;
				 };

				 return ( cmp1( "hello", 3 ) ) &&
						( cmp1( "hello", 0 ) ) &&
						( cmp2( "hello", 10, 'x' ) );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string1()
{
	static_string<10> s( "hello" );

	CPPDEBUG( format("s: %s", s ) );

	return std::make_shared<TestEqualToString<10,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "nix";
							e += '1';
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string2()
{
	return std::make_shared<TestEqualToString<10,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.clear();
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string3()
{
	return std::make_shared<TestEqualToString<10,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("XXX");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string4()
{
	return std::make_shared<TestEqualToString<20,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("XXX");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string5()
{
	return std::make_shared<TestEqualToString<20,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("01234567890123456789");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string6()
{
	return std::make_shared<TestEqualToString<30,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("012345678901234567890123456789");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string7()
{
	return std::make_shared<TestEqualToString<40,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("0123456789012345678901234567890123456789");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string8()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("01234567890123456789012345678901234567890123456789");
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_replace_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("'%s'");
							e.replace( 1, 2, "hello" );
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_replace_2()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string("'hello'");
							e.replace( 1, 5, "%s" );
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_c_str_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 return ( std::strcmp( static_string<20>().c_str(), std::string().c_str() ) == 0 ) &&
							( std::strcmp( static_string<20>("hello").c_str(), std::string("hello").c_str() ) == 0 );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<20> x;
					 static_string<20> y("y");

					 x = y;
					 return x == y;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_2()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_3()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = 'h';
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_4()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = { 'h', 'e', 'l', 'l', 'o' };
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_5()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string_view( "hello" );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_6()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string( "hello" );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_7()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_basic_string<20,char> x;
					 static_basic_string<30,char> y("y");

					 x = y;
					 return x == y;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_8()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<20> x;
					 static_string<30> y("y");

					 x = y;
					 return x == y;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_append_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.append("1").append(std::string("2")).append(std::string_view("3")).append({'4'});
							CPPDEBUG( format( "string: %s", e ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a == b) && ( b == a );
				 };

				 return cmp( std::string("a"), static_string<20>("a") ) &&
						cmp( std::string_view("a"), static_string<20>("a") ) &&
						cmp( "a", static_string<20>("a") ) &&
						cmp( static_string<15>("a"), static_string<20>("a") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a == b) && ( b == a );
				 };

				 return !cmp( std::string("a"), static_string<20>("ab") ) &&
						!cmp( std::string_view("a"), static_string<20>("ab") ) &&
						!cmp( "a", static_string<20>("ab") ) &&
						!cmp( static_string<15>("a"), static_string<20>("ab") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a != b) && ( b != a );
				 };

				 return cmp( std::string("a"), static_string<20>("ab") ) &&
						cmp( std::string_view("a"), static_string<20>("ab") ) &&
						cmp( "a", static_string<20>("ab") ) &&
						cmp( static_string<15>("a"), static_string<20>("ab") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_4()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a != b) && ( b != a );
				 };

				 return !cmp( std::string("a"), static_string<20>("a") ) &&
						!cmp( std::string_view("a"), static_string<20>("a") ) &&
						!cmp( "a", static_string<20>("a") ) &&
						!cmp( static_string<15>("a"), static_string<20>("a") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_5()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a == b) && ( b == a );
				 };

				 return !cmp( "0123456789", static_string<5>("01234") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_6()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a < b) && ( b > a );
				 };

				 return cmp( "aaa", static_string<10>("bbb") ) &&
						cmp( std::string_view("aaa"), static_string<5>("bbb") ) &&
						cmp( std::string("aaa"), static_string<5>("bbb") ) &&
						cmp( static_string<10>("aaa"), static_string<5>("bbb") ) &&
						cmp( static_string<10>("aaa"), static_string<10>("bb") );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_7()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a <= b) && ( b > a );
				 };

				 return cmp( "aaa", static_string<10>("bbb") ) &&
						cmp( std::string_view("aaa"), static_string<5>("bbb") ) &&
						cmp( std::string("aaa"), static_string<5>("bbb") ) &&
						cmp( static_string<10>("aaa"), static_string<5>("bbb") ) &&
						cmp( static_string<10>("aaa"), static_string<10>("bb") );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_8()
{
	return std::make_shared<TestBool>(__FUNCTION__,
			[]() {
				 auto cmp = []( const auto & a, const auto & b ) {
					 return ( a >= b) && ( b < a );
				 };

				 return !cmp( "aaa", static_string<10>("bbb") ) &&
						!cmp( std::string_view("aaa"), static_string<5>("bbb") ) &&
						!cmp( std::string("aaa"), static_string<5>("bbb") ) &&
						!cmp( static_string<10>("aaa"), static_string<5>("bbb") ) &&
						!cmp( static_string<10>("aaa"), static_string<10>("bb") );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_ostream_1()
{
	return std::make_shared<TestEqualConv<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::stringstream str;

				std::visit(
						[&str](auto & e){
							e = "hello";
							str << e;
						}, v );

				return str.str();
			});
}
