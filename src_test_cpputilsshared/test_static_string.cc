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

        if( !(std::get<0>(cc) == std::get<1>(cv)) ) {
        	CPPDEBUG( format( "FAILED: '%s' {%d}(static_basic_string<%d>) != '%s' {%d}(basic_string)",
        			std::get<0>(cc),
					std::get<0>(cc).size(),
					N,
					std::get<1>(cv),
					std::get<1>(cv).size() ) );
        	return false;
        }

        return true;
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

template <std::size_t N,class T,typename ret_type=size_t>
struct TestEqualToStringRet : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<static_basic_string<N,T>,std::basic_string<T>>;
	typedef std::function<ret_type(CONTAINER)> Func;
	Func func;

	static_basic_string<N,T> c;
    std::basic_string<T>   v;

    TestEqualToStringRet( const std::string & descr, Func func )
	: TestCaseBase<bool>( descr, true, false ),
	  func( func ),
	  c(),
	  v()
	{}

    bool run() override
    {
    	CONTAINER cc = c;
    	CONTAINER cv = v;

        auto ret1 = func( cc );
        auto ret2 = func( cv );

        if( ret1 != ret2 ) {
        	CPPDEBUG( format( "FAILED: '%s' {%d}(static_basic_string<%d>) ret: %d != %d '%s' {%d}(basic_string)",
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

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.at(3) = 'x';
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 return std::string(text).at(2) == static_string<20>(text).at(2);
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 const static_string<20> x(text);
					 return x.at(strlen(text)) == 'x';
				}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e[3] = 'x';
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 return std::string(text)[2] == static_string<20>(text)[2];
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 const std::string s1(text);
					 const static_string<20> s2(text);
					 return  s1[2] == s2[2];
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_front_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.front() = 'x';
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_front_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 const std::string s1(text);
					 const static_string<20> s2(text);
					 return  s1.front() == s2.front();
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_back_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.back() = 'x';
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_back_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 const std::string s1(text);
					 const static_string<20> s2(text);
					 return  s1.back() == s2.back();
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_string_view_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "hello";
					 const std::string s1(text);
					 const static_string<20> s2(text);

					 std::string_view v1 = s1;
					 std::string_view v2 = s2;

					 return  v1 == v2;
				});;
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							std::string s(e.begin(),e.end());
							e = s;
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_2()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							std::string s(e.cbegin(),e.cend());
							e = s;
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_3()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							typename std::remove_reference<decltype(e)>::type s;
							std::copy(e.crbegin(), e.crend(), std::back_inserter(s));
							e = s;
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_4()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							typename std::remove_reference<decltype(e)>::type s;
							std::copy(e.rbegin(), e.rend(), std::back_inserter(s));
							e = s;
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_empty_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<10> s1;
					 static_string<10> s2 = "s2";
					 static_string<10> s3 = "";
					 const static_string<10> s4 = "";

					 return ( s1.empty() == true ) &&
							( s2.empty() == false ) &&
							( s3.empty() == true ) &&
							( s4.empty() == true );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_size_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<10> s1;
					 static_string<10> s2 = "s2";
					 static_basic_string<10,char,static_string_out_of_range_cut> s3 = "0123456789 too long";
					 const static_string<10> s4 = "s2";

					 return ( s1.size() == 0 ) &&
							( s2.size() == 2 ) &&
							( s3.size() == 10 ) &&
							( s4.size() == 2 );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_length_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<10> s1;
					 static_string<10> s2 = "s2";
					 static_basic_string<10,char,static_string_out_of_range_cut> s3 = "0123456789 too long";
					 const static_string<10> s4 = "s2";

					 return ( s1.length() == 0 ) &&
							( s2.length() == 2 ) &&
							( s3.length() == 10 ) &&
							( s4.length() == 2 );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_shrink_to_fit_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.shrink_to_fit();
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_clear_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.clear();
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, 5, 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,10,'x');
				 s2.insert(1,10,'x');
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,10,'x');
				 s2.insert(0,10,'x');
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,10,'x');
				 s2.insert(9,10,'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,10,'x');
				 s2.insert(10,10,'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x5 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,8,'x');
				 s2.insert(1,8,'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() & x3() && x4() && x5();
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
					 s1.insert(1,10,'x');
					 return s1 == "hxxxxxxxxx";
				}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_4()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, "xxxx" );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_41()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,"01234567890");
				 s2.insert(1,"01234567890");
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,"01234567890");
				 s2.insert(0,"01234567890");
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,"01234567890");
				 s2.insert(9,"01234567890");
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,"01234567890");
				 s2.insert(10,"01234567890");
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x5 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,"01234567");
				 s2.insert(1,"01234567");
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4() && x5();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_42()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,"123456789");
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_5()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, "xxxx", 2 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_51()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,"01234567890",8);
				 s2.insert(1,"01234567890",8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,"01234567890",8);
				 s2.insert(0,"01234567890",8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,"01234567890",8);
				 s2.insert(9,"01234567890",8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,"01234567890",8);
				 s2.insert(10,"01234567890",8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_52()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,"123456789",8);
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_6()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, std::string("xxxx") );
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_61()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,std::string("01234567"));
				 s2.insert(1,std::string("01234567"));
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,std::string("01234567"));
				 s2.insert(0,std::string("01234567"));
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,std::string("01234567"));
				 s2.insert(9,std::string("01234567"));
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,std::string("01234567"));
				 s2.insert(10,std::string("01234567"));
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_62()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,std::string("12345678"));
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_7()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,static_string<20>("01234567"));
				 s2.insert(1,std::string("01234567"));
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,static_string<20>("01234567"));
				 s2.insert(0,std::string("01234567"));
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,static_string<20>("01234567"));
				 s2.insert(9,std::string("01234567"));
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,static_string<20>("01234567"));
				 s2.insert(10,std::string("01234567"));
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_71()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,static_string<20>("12345678"));
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_8()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, std::string("1234567"), 1, 2 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_81()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, std::string("123"), 1 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_82()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,std::string("01234567"),1);
				 s2.insert(1,std::string("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,std::string("01234567"),1);
				 s2.insert(0,std::string("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,std::string("01234567"),1);
				 s2.insert(9,std::string("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,std::string("01234567"),1);
				 s2.insert(10,std::string("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_83()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,std::string("1234567890123456789"),1,15);
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_84()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,std::string("012345679012345678"),1,8);
				 s2.insert(1,std::string("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'{%d}", s1, s1.size() ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'{%d}", s2, s2.size() ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,std::string("012345679012345678"),1,8);
				 s2.insert(0,std::string("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,std::string("012345679012345678"),1,8);
				 s2.insert(9,std::string("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,std::string("012345679012345678"),1,8);
				 s2.insert(10,std::string("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_9()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,static_string<20>("01234567"),1);
				 s2.insert(1,std::string("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,static_string<20>("01234567"),1);
				 s2.insert(0,std::string("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,static_string<20>("01234567"),1);
				 s2.insert(9,std::string("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,static_string<20>("01234567"),1);
				 s2.insert(10,std::string("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_91()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,static_string<30>("1234567890123456789"),1,15);
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_92()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,static_string<20>("012345679012345678"),1,8);
				 s2.insert(1,std::string("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'{%d}", s1, s1.size() ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'{%d}", s2, s2.size() ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,static_string<20>("012345679012345678"),1,8);
				 s2.insert(0,std::string("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,static_string<20>("012345679012345678"),1,8);
				 s2.insert(9,std::string("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,static_string<20>("012345679012345678"),1,8);
				 s2.insert(10,std::string("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_10()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( ++e.begin(), 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_101()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( e.end(), 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_102()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "0123456789";
			s1.insert(s1.begin(),'x');
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_103()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			auto x1 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(s1.begin(),'x');
				 s2.insert(s2.begin(),'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x2 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(s1.begin(),'x');
				 auto it_s2 = s2.insert(s2.begin(),'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(++s1.begin(),'x');
				 auto it_s2 = s2.insert(++s2.begin(),'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			return x1() && x2() && x3();
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( ++e.cbegin(), 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_111()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( e.cend(), 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_112()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "0123456789";
			s1.insert(s1.cbegin(),'x');
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_113()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			auto x1 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(s1.cbegin(),'x');
				 s2.insert(s2.cbegin(),'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x2 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(s1.cbegin(),'x');
				 auto it_s2 = s2.insert(s2.cbegin(),'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(++s1.cbegin(),'x');
				 auto it_s2 = s2.insert(++s2.cbegin(),'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			return x1() && x2() && x3();
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_12()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( ++e.cbegin(), 2, 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_121()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( e.cend(), 2, 'x' );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_122()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "0123456789";
			s1.insert(s1.begin(), 10, 'x');
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_123()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			auto x1 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(s1.cbegin(),5,'x');
				 s2.insert(s2.cbegin(),5,'x');
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x2 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(s1.cbegin(),3,'x');
				 auto it_s2 = s2.insert(s2.cbegin(),3,'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(++s1.cbegin(),3,'x');
				 auto it_s2 = s2.insert(++s2.cbegin(),3,'x');
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			return x1() && x2() && x3();
		});
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_13()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							std::string_view sv("xx");
							e.insert( ++e.cbegin(), sv.begin(), sv.end() );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_131()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							const std::string_view sv("xx");
							e.insert( e.cend(), sv.begin(), sv.end() );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_132()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "0123456789";
			const std::string_view sv("xxxxxxxxxxxxxx");
			s1.insert(s1.begin(), sv.begin(), sv.end());
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_133()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			auto x1 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;
				 const std::string_view sv("12345");

				 s1.insert(s1.cbegin(),sv.begin(), sv.end());
				 s2.insert(s2.cbegin(),sv.begin(), sv.end());
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x2 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;
				 const std::string_view sv("123");

				 auto it_s1 = s1.insert(s1.cbegin(),sv.begin(), sv.end());
				 auto it_s2 = s2.insert(s2.cbegin(),sv.begin(), sv.end());
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;
				 const std::string_view sv("123");

				 auto it_s1 = s1.insert(++s1.cbegin(),sv.begin(), sv.end());
				 auto it_s2 = s2.insert(++s2.cbegin(),sv.begin(), sv.end());
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			return x1() && x2() && x3();
		});
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_14()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( ++e.cbegin(), { 'x', 'x' } );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_141()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( e.cend(), { 'x', 'x' } );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_142()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "0123456789";
			s1.insert(s1.begin(), { 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x' });
			return s1 == "hxxxxxxxxx";
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_143()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			auto x1 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(s1.cbegin(),{ '1', '2', '3', '4', '5' });
				 s2.insert(s2.cbegin(),{ '1', '2', '3', '4', '5' });
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x2 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 auto it_s1 = s1.insert(s1.cbegin(),{ '1', '2', '3' });
				 auto it_s2 = s2.insert(s2.cbegin(),{ '1', '2', '3' });
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;
				 const std::string_view sv("123");

				 auto it_s1 = s1.insert(++s1.cbegin(),{ '1', '2', '3' });
				 auto it_s2 = s2.insert(++s2.cbegin(),{ '1', '2', '3' });
				 s2.resize(10);

				 if( *it_s1 == *it_s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			};

			return x1() && x2() && x3();
		});
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_15()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, std::string_view("1234567"), 1, 2 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_151()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "'hello'";
							e.insert( 1, std::string_view("123"), 1 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_152()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,std::string_view("01234567"),1);
				 s2.insert(1,std::string_view("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,std::string_view("01234567"),1);
				 s2.insert(0,std::string_view("01234567"),1);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,std::string_view("01234567"),1);
				 s2.insert(9,std::string_view("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,std::string_view("01234567"),1);
				 s2.insert(10,std::string_view("01234567"),1);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_153()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			static_basic_string<10,char,static_string_out_of_range_except> s1 = "hello";
			s1.insert(1,std::string_view("1234567890123456789"),1,15);
			return s1 == "hxxxxxxxxx";
		}, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_154()
{
	return std::make_shared<TestBool>(__FUNCTION__,
		[]() {
			 auto x1 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(1,std::string_view("012345679012345678"),1,8);
				 s2.insert(1,std::string_view("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'{%d}", s1, s1.size() ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'{%d}", s2, s2.size() ) );
				 return false;
			 };

			 auto x2 = []() {
				 std::string s2 = "hello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(0,std::string_view("012345679012345678"),1,8);
				 s2.insert(0,std::string_view("012345679012345678"),1,8);
				 s2.resize(10);


				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x3 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(9,std::string_view("012345679012345678"),1,8);
				 s2.insert(9,std::string_view("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s1 (static_string): '%s'", s1 ) );
				 CPPDEBUG( format( "s2 (std::string)  : '%s'", s2 ) );
				 return false;
			 };

			 auto x4 = []() {
				 std::string s2 = "hellohello";
				 static_basic_string<10,char,static_string_out_of_range_cut> s1 = s2;

				 s1.insert(10,std::string_view("012345679012345678"),1,8);
				 s2.insert(10,std::string_view("012345679012345678"),1,8);
				 s2.resize(10);

				 if( s1 == s2 ) {
					 return true;
				 }

				 CPPDEBUG( format( "s2 (static_string): '%s'", s2 ) );
				 CPPDEBUG( format( "s1 (std::string)  : '%s'", s1 ) );
				 return false;
			 };

			 return x1() && x2() && x3() && x4();
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(e.begin());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_12()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(e.cbegin());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_13()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string   s1 = "hello";
					 static_string<20> s2 = s1;

					 auto it_s1 = s1.erase(++s1.cbegin());
					 auto it_s2 = s2.erase(++s2.cbegin());

					 return *it_s1 == *it_s2;
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_21()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase();
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_22()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_23()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(2,2);
						}, v );
			});
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_31()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(e.begin(),e.end());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_32()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.erase(++e.begin(),e.end());
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_33()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							auto it1 = e.begin();
							++it1;
							++it1;

							auto it2 = it1;
							++it2;
							++it2;

							e.erase(it1,it2);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.push_back('1');
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<5,char,static_string_out_of_range_cut> s2 = s1;

					 s1.push_back('x');
					 s2.push_back('x');

					 s1.resize(5);

					 return s1 == s2;
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<5,char,static_string_out_of_range_except> s2 = s1;

					 s1.push_back('x');
					 s2.push_back('x');

					 s1.resize(5);

					 return s1 == s2;
				}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_pop_back_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.pop_back();
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string("30"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_12()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(std::string("1234567"));
					 s2.append(std::string("1234677"));

					 s1.resize(7);

					 CPPDEBUG( format( "s2 (static_string): '%s'", s2 ) );
					 CPPDEBUG( format( "s1 (std::string)  : '%s'", s1 ) );

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_13()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(std::string("1234567"));
					 s2.append(std::string("1234677"));

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_21()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(1,'x');
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_22()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(0,'x');
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_23()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(7,'x');
					 s2.append(7,'x');

					 s1.resize(7);

					 CPPDEBUG( format( "s2 (static_string): '%s'", s2 ) );
					 CPPDEBUG( format( "s1 (std::string)  : '%s'", s1 ) );

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_24()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(7,'x');
					 s2.append(7,'x');

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_31()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 std::string text = "1234677";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_basic_string<10,char,static_string_out_of_range_except> s3 = text;

					 s1.append(s3);
					 s2.append(text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_32()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(static_string<10>("1234567"));
					 s2.append(std::string("1234677"));

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_33()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(static_string<10>("1234567"));
					 s2.append(std::string("1234677"));

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_41()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string("1234567"),1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_42()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string("1234567"),1,2);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_43()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 std::string text = "1234677";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(text,1,5);
					 s2.append(text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_44()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 std::string text = "1234677";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(text,1,5);
					 s2.append(text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_51()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(static_string<20>("1234567"),1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_52()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(static_string<20>("1234567"),1,2);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_53()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 std::string text = "1234677";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_basic_string<10,char,static_string_out_of_range_except> s3 = text;

					 s1.append(s3,1,5);
					 s2.append(text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_54()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 std::string text = "1234677";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 static_basic_string<10,char,static_string_out_of_range_cut> s3 = text;

					 s1.append(s3,1,5);
					 s2.append(text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_61()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append("1234567",1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_62()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append("1234567",3);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_63()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append("1234677",7);
					 s2.append("1234677",7);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_64()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append("1234677",7);
					 s2.append("1234677",7);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_71()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append("1234567");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_72()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append("1234567");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_73()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append("1234677");
					 s2.append("1234677");

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_74()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append("1234677");
					 s2.append("1234677");

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_81()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string_view("1234567"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_82()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string_view("1234567"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_83()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(std::string_view("1234677"));
					 s2.append(std::string_view("1234677"));

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_84()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(std::string_view("1234677"));
					 s2.append(std::string_view("1234677"));

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_91()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string_view("1234567"),2);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_92()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append(std::string_view("1234567"),2,3);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_93()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append(std::string_view("1234677"),2);
					 s2.append(std::string_view("1234677"),2);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_94()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append(std::string_view("1234677"),2);
					 s2.append(std::string_view("1234677"),2);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_101()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							std::string_view sv("1234567");
							e.append(sv.begin(),sv.end());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_102()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							std::string_view sv("1234567");
							auto it = sv.begin();
							++it;

							e.append(it, sv.end());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_103()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view sv("1234567");

					 s1.append(sv.begin(),sv.end());
					 s2.append(sv.begin(),sv.end());

					 s1.resize(7);

					 CPPDEBUG( format( "s2 (static_string): '%s'", s2 ) );
					 CPPDEBUG( format( "s1 (std::string)  : '%s'", s1 ) );

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_104()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view sv("1234567");

					 s1.append(sv.begin(),sv.end());
					 s2.append(sv.begin(),sv.end());

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_111()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.append({ '1','2','3','4','5','6','7' });
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_112()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.append({ '1','2','3','4','5','6','7' });
					 s2.append({ '1','2','3','4','5','6','7' });

					 s1.resize(7);

					 CPPDEBUG( format( "s2 (static_string): '%s'", s2 ) );
					 CPPDEBUG( format( "s1 (std::string)  : '%s'", s1 ) );

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_113()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.append({ '1','2','3','4','5','6','7' });
					 s2.append({ '1','2','3','4','5','6','7' });

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += std::string("1234567");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_12()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_13()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_21()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += static_string<20>("1234567");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_22()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_string<20> text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_23()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 static_string<20> text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_31()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += 'c';
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_32()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<5,char,static_string_out_of_range_cut> s2 = s1;

					 s1 += 'x';
					 s2 += 'x';

					 s1.resize(5);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_33()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<5,char,static_string_out_of_range_except> s2 = s1;

					 s1 += 'X';
					 s2 += 'X';

					 s1.resize(5);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_41()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += "1234567";
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_42()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 const char* text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_43()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 const char* text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_51()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += { '1','2','3','4','5','6','7' };
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_52()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1 += { '1','2','3','4','5','6','7' };
					 s2 += { '1','2','3','4','5','6','7' };

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_53()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1 += { '1','2','3','4','5','6','7' };;
					 s2 += { '1','2','3','4','5','6','7' };;

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_61()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e += std::string_view("1234567");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_62()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_63()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view text = "1234567";

					 s1 += text;
					 s2 += text;

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string("Xx"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_12()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_13()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_21()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string_view("Xx"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_22()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_23()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_31()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,static_string<10>("Xx"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_32()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_33()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text);
					 s2.replace(1,2,text);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_41()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							auto it_first = e.begin();
							++it_first;
							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,static_string<10>("Xx"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_42()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_string<10> text = "1234567";

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,text);
					 s2.replace(s2_it_first,s2_it_last,text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_43()
{
	return std::make_shared<TestBool>(__FUNCTION__,
	[]() {
		 std::string s1 = "hello";
		 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
		 static_string<10> text = "1234567";

		 auto s1_it_first = s1.begin();
		 ++s1_it_first;
		 auto s1_it_last = s1_it_first;
		 ++s1_it_last;

		 auto s2_it_first = s2.begin();
		 ++s2_it_first;
		 auto s2_it_last = s2_it_first;
		 ++s2_it_last;

		 s1.replace(s1_it_first,s1_it_last,text);
		 s2.replace(s2_it_first,s2_it_last,text);

		 s1.resize(7);

		 return s1 == s2;
	},true);
}




std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_51()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							auto it_first = e.begin();
							++it_first;
							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,std::string("Xx"));
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_52()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,text);
					 s2.replace(s2_it_first,s2_it_last,text);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_53()
{
	return std::make_shared<TestBool>(__FUNCTION__,
	[]() {
		 std::string s1 = "hello";
		 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
		 std::string text = "1234567";

		 auto s1_it_first = s1.begin();
		 ++s1_it_first;
		 auto s1_it_last = s1_it_first;
		 ++s1_it_last;

		 auto s2_it_first = s2.begin();
		 ++s2_it_first;
		 auto s2_it_last = s2_it_first;
		 ++s2_it_last;

		 s1.replace(s1_it_first,s1_it_last,text);
		 s2.replace(s2_it_first,s2_it_last,text);

		 s1.resize(7);

		 return s1 == s2;
	},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_61()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string("Xx23456"),1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_62()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string("Xx23456"),1,5);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_63()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_64()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_65()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_66()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}




std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_71()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string_view("Xx23456"),1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_72()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,std::string_view("Xx23456"),1,5);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_73()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_74()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_75()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_76()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_81()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,static_string<10>("Xx23456"),1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_82()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,static_string<10>("Xx23456"),1,5);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_83()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_84()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_85()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text,1,5);
					 s2.replace(1,2,text,1,5);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_86()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 static_string<10> text = "1234567";

					 s1.replace(1,2,text,1);
					 s2.replace(1,2,text,1);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_91()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,"Xx23456",4);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_92()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.replace(1,2,"1234567",7);
					 s2.replace(1,2,"1234567",7);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_93()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.replace(1,2,"1234567",7);
					 s2.replace(1,2,"1234567",7);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_101()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							auto it_first = e.begin();
							++it_first;
							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,"Xx");
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_102()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string text = "1234567";

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,text.c_str());
					 s2.replace(s2_it_first,s2_it_last,text.c_str());

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_103()
{
	return std::make_shared<TestBool>(__FUNCTION__,
	[]() {
		 std::string s1 = "hello";
		 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
		 std::string text = "1234567";

		 auto s1_it_first = s1.begin();
		 ++s1_it_first;
		 auto s1_it_last = s1_it_first;
		 ++s1_it_last;

		 auto s2_it_first = s2.begin();
		 ++s2_it_first;
		 auto s2_it_last = s2_it_first;
		 ++s2_it_last;

		 s1.replace(s1_it_first,s1_it_last,text.c_str());
		 s2.replace(s2_it_first,s2_it_last,text.c_str());

		 s1.resize(7);

		 return s1 == s2;
	},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_111()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							auto it_first = e.begin();
							++it_first;
							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,5,'x');
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_112()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,10,'x');
					 s2.replace(s2_it_first,s2_it_last,10,'x');

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_113()
{
	return std::make_shared<TestBool>(__FUNCTION__,
	[]() {
		 std::string s1 = "hello";
		 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

		 auto s1_it_first = s1.begin();
		 ++s1_it_first;
		 auto s1_it_last = s1_it_first;
		 ++s1_it_last;

		 auto s2_it_first = s2.begin();
		 ++s2_it_first;
		 auto s2_it_last = s2_it_first;
		 ++s2_it_last;

		 s1.replace(s1_it_first,s1_it_last,10,'x');
		 s2.replace(s2_it_first,s2_it_last,10,'x');

		 s1.resize(7);

		 return s1 == s2;
	},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_121()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e.replace(1,2,4,'x');
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_122()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 s1.replace(1,2,7,'x');
					 s2.replace(1,2,7,'x');

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_123()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 s1.replace(1,2,7,'x');
					 s2.replace(1,2,7,'x');

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_131()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							std::string_view sv("1234567");
							auto it_first = e.begin();
							++it_first;

							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,sv.begin(),sv.end());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_132()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view sv("1234567");

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,sv.begin(),sv.end());
					 s2.replace(s2_it_first,s2_it_last,sv.begin(),sv.end());

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_133()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view sv("1234567");

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,sv.begin(),sv.end());
					 s2.replace(s2_it_first,s2_it_last,sv.begin(),sv.end());

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_141()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";

							auto it_first = e.begin();
							++it_first;

							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,{ '1','2','3','4','5','6','7' });
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_142()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,{ '1','2','3','4','5','6','7' });
					 s2.replace(s2_it_first,s2_it_last,{ '1','2','3','4','5','6','7' });

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_143()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,{ '1','2','3','4','5','6','7' });
					 s2.replace(s2_it_first,s2_it_last,{ '1','2','3','4','5','6','7' });

					 s1.resize(7);

					 return s1 == s2;
				},true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_151()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							std::string_view sv("1234567");
							auto it_first = e.begin();
							++it_first;

							auto it_last = it_first;
							++it_last;

							e.replace(it_first,it_last,sv);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_152()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_cut> s2 = s1;
					 std::string_view sv("1234567");

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,sv);
					 s2.replace(s2_it_first,s2_it_last,sv);

					 s1.resize(7);

					 return s1 == s2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_153()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string s1 = "hello";
					 static_basic_string<7,char,static_string_out_of_range_except> s2 = s1;
					 std::string_view sv("1234567");

					 auto s1_it_first = s1.begin();
					 ++s1_it_first;
					 auto s1_it_last = s1_it_first;
					 ++s1_it_last;

					 auto s2_it_first = s2.begin();
					 ++s2_it_first;
					 auto s2_it_last = s2_it_first;
					 ++s2_it_last;

					 s1.replace(s1_it_first,s1_it_last,sv);
					 s2.replace(s2_it_first,s2_it_last,sv);

					 s1.resize(7);

					 return s1 == s2;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_copy_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::vector<char> v1(50,0);
					 std::vector<char> v2(50,0);

					 auto do_copy = []( auto & source, std::vector<char> & dest, size_t pos ) {
						 size_t len = source.copy( dest.data(), source.size(), pos);
						 dest.resize(len+1);
						 dest.at(len) = '\0';
						 return len;
					 };

					 std::string s1 = "hello";
					 static_string<20> s2 = s1;

					 size_t len1 = do_copy( s1, v1, 0 );
					 size_t len2 = do_copy( s2, v2, 0 );

					 CPPDEBUG( format( "len1: %d len2: %d", len1, len2 ) );
					 CPPDEBUG( format( "v1: (std::string)   '%s'", v1.data() ) );
					 CPPDEBUG( format( "v2: (static_string) '%s'", v2.data() ) );

					 return len1 == len2 && v1 == v2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_copy_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::vector<char> v1(50,0);
					 std::vector<char> v2(50,0);

					 auto do_copy = []( auto & source, std::vector<char> & dest, size_t pos ) {
						 size_t len = source.copy( dest.data(), source.size(), pos);
						 dest.resize(len+1);
						 dest.at(len) = '\0';
						 return len;
					 };

					 std::string s1 = "hello";
					 static_string<20> s2 = s1;

					 size_t len1 = do_copy( s1, v1, 3 );
					 size_t len2 = do_copy( s2, v2, 3 );

					 CPPDEBUG( format( "len1: %d len2: %d", len1, len2 ) );
					 CPPDEBUG( format( "v1: (std::string)   '%s'", v1.data() ) );
					 CPPDEBUG( format( "v2: (static_string) '%s'", v2.data() ) );

					 return len1 == len2 && v1 == v2;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_copy_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::vector<char> v2(50,0);

					 auto do_copy = []( auto & source, std::vector<char> & dest, size_t pos ) {
						 size_t len = source.copy( dest.data(), source.size(), pos);
						 dest.resize(len+1);
						 dest.at(len) = '\0';
						 return len;
					 };

					 static_string<20> s2 = "hello";

					 size_t len2 = do_copy( s2, v2, 7 );

					 return false;
				},true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_swap_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							typename std::remove_cvref<decltype(e)>::type s = "nix";
							e.swap(s);
						}, v );
			});
}

template<class ret_type=size_t>
static auto create_find_1( auto func )
{
	return [func]( auto v ) -> ret_type {
		ret_type pos = 0;
		std::visit(
				[&pos,func](auto e){
					e = "hello";
					pos = func( e );
				}, v );
		return pos;
	};
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_1()
{
	/*
	return std::make_shared<TestEqualToStringRet<50,char>>(__FUNCTION__,
			[]( auto & v ) -> size_t {
				size_t pos;
				std::visit(
						[&pos](auto & e){
							e = "hello";
							pos = e.find(std::string("ll"));
						}, v );
				return pos;
			});
			*/

	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find(std::string("ll") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find(std::string("xx") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find(std::string("ll", 1) );}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_2()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find(static_string<20>("ll") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find(static_string<20>("xx") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find(static_string<20>("ll", 1) );}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_3()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find("oo",1,1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find("xx",0, 1 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find("llo",0,2);}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_4()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find("oo",1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find("xx",0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find("llo",4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
					create_find_1( []( auto & e ) { return e.find("llo");}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_5()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find('o',1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find('x',0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find('e',4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
				create_find_1( []( auto & e ) { return e.find('h');}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_find_6()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.find(std::string_view("oo"),1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.find(std::string_view("xx"),0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.find(std::string_view("llo"),4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
					create_find_1( []( auto & e ) { return e.find(std::string_view("llo"));}) ) );

	return ret;
}



std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_1()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind(std::string("ll") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind(std::string("xx") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind(std::string("ll", 1) );}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_2()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind(static_string<20>("ll") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind(static_string<20>("xx") );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind(static_string<20>("ll", 1) );}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_3()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind("oo",1,1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind("xx",0, 1 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind("llo",0,2);}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_4()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind("oo",1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind("xx",0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind("llo",4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
					create_find_1( []( auto & e ) { return e.rfind("llo");}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_5()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind('o',1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind('x',0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind('e',4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
				create_find_1( []( auto & e ) { return e.rfind('h');}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_rfind_6()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "1",
			create_find_1( []( auto & e ) { return e.rfind(std::string_view("oo"),1);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "2",
				create_find_1( []( auto & e ) { return e.rfind(std::string_view("xx"),0 );}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "3",
				create_find_1( []( auto & e ) { return e.rfind(std::string_view("llo"),4);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char>>(std::string(__FUNCTION__) + "4",
					create_find_1( []( auto & e ) { return e.rfind(std::string_view("llo"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_1()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(std::string("hello"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(std::string("x"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_2()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(std::string_view("hello"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(std::string_view("x"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_3()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(static_string<20>("hello"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(static_string<20>("x"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_4()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(1,std::string::npos,std::string("hello"),2,3);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,std::string("hello"),1,2);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,std::string("hello"),1);}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_5()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(1,std::string::npos,static_string<20>("hello"),2,3);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,static_string<20>("hello"),1,2);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,static_string<20>("hello"),1);}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_6()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare("hello");}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare("xxx");}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_7()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(1,std::string::npos,"ll");}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,2,"xxx");}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_8()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(1,std::string::npos,std::string_view("ll"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,2,std::string_view("xxx"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_compare_9()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "1",
			create_find_1<int>( []( auto e ) { return e.compare(1,std::string::npos,std::string_view("hello"),2,3);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,std::string_view("hello"),1,2);}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,int>>(std::string(__FUNCTION__) + "2",
			create_find_1<int>( []( auto e ) { return e.compare(1,3,std::string_view("hello"),1);}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_starts_with_1()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.starts_with(std::string_view("h"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.starts_with(std::string_view("x"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_starts_with_2()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.starts_with('h');}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.starts_with('x');}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_starts_with_3()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.starts_with("he");}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.starts_with("xx");}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_ends_with_1()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.ends_with(std::string_view("lo"));}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.ends_with(std::string_view("x"));}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_ends_with_2()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.ends_with('o');}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.ends_with('x');}) ) );

	return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_case_static_string_ends_with_3()
{
	std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "1",
			create_find_1<bool>( []( auto e ) { return e.ends_with("lo");}) ) );

	ret.push_back( std::make_shared<TestEqualToStringRet<50,char,bool>>(std::string(__FUNCTION__) + "2",
			create_find_1<bool>( []( auto e ) { return e.ends_with("xx");}) ) );

	return ret;
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

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_to_basic_string_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 std::string x;
					 static_string<30> y("y");

					 x = y;
					 return x == y;
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(5,'y');
						}, v );
			});
}



std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_string<20> x;
					 static_string<20> y("y");

					 x.assign(y);
					 return x == y;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 static_basic_string<20,char> x;
					 static_basic_string<30,char> y("y");

					 x.assign(y);
					 return x == y;
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_4()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign( std::string("hello" ) );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_5()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = std::string_view( "hello" );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_6()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char* testtext = "firstsecond";

					 static_basic_string<20,char> sx;
					 static_basic_string<30,char> sy(testtext);
					 sx.assign(sy,5);

					 std::string stdx;
					 std::string stdy(testtext);
					 stdx.assign(stdy,5);

					 return sx == stdx;
				});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_7()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char* testtext = "firstsecond";

					 static_basic_string<20,char> sx;
					 static_basic_string<30,char> sy(testtext);
					 sx.assign(sy,2);

					 std::string stdx;
					 std::string stdy(testtext);
					 stdx.assign(stdy,2);


					 return sx == stdx;
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_8()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(std::string( "firstsecond" ),5);
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_9()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(std::string( "firstsecond" ),5,2);
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_10()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(std::string_view( "firstsecond" ),5,2);
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_11()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(std::string_view( "firstsecond" ),5);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_12()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign( "firstsecond" ,5);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_13()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign( "firstsecond" );
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_14()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign( { 'H', 'e', 'l', 'l', 'o' });
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_15()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							std::string str("hello");
							e.assign(str.begin(), str.end());
						}, v );
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

#if __cpp_lib_string_contains >= 202011L
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_1()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( "hello" );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_2()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( 'e' );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_3()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( std::string_view( "hello" ) );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_4()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( "xxx" );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_5()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( 'y' );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_6()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 auto contains = []( const auto & str) {
						return str.contains( std::string_view( "xxx" ) );
					 };

					 const char *text = "text hello text";
					 return contains( static_string<20>( text ) ) == contains( std::string( text ) );
				});
}
#else
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_7()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return static_string<20>( text ).contains("hello");
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_8()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return static_string<20>( text ).contains('e');
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_9()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return static_string<20>( text ).contains( std::string_view( "hello" ) );
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_10()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return !static_string<20>( text ).contains("xxx");
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_11()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return !static_string<20>( text ).contains('y');
				});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_12()
{
	return std::make_shared<TestBool>(__FUNCTION__,
				[]() {
					 const char *text = "text hello text";
					 return !static_string<20>( text ).contains( std::string_view( "xxx" ) );
				});
}

#endif

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_substr_1()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e = e.substr( 2 );
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_substr_2()
{
	return std::make_shared<TestEqualToString<50,char>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e = "hello";
							e = e.substr( 2, 2 );
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
