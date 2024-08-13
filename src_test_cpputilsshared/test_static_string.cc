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

} // namespace

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
