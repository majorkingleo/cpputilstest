/**
 * Testcases for cpputils/cpputilsshared/span_vector.h
 * @author Copyright (c) 2024 Martin Oberzalek
 */
#include "test_static_vector.h"
#include "ColoredOutput.h"
#include <initializer_list>
#include <variant>
#include <CpputilsDebug.h>
#include <cstring>
#include <vector>
#include <format.h>

#include <span_vector.h>

using namespace Tools;

namespace {

template <class T>
bool operator==( const span_vector<T> & c, const std::vector<T> & v )
{
    if( c.size() != v.size() ) {
    	// CPPDEBUG( Tools::format("c.size != v.size => %d != %d", c.size(), v.size()) );
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
template <class T>
std::ostream & operator<<( std::ostream & out, const span_vector<T> & carray )
{
	out << "[" << carray.size() << "]";

	out << "{";

	bool first = true;

	for( const T & t : carray ) {

		if( first ) {
			first = false;
		} else {
			out << ", ";
		}

		out << t;
	}

	out << "}";

	return out;
}


template <class T>
std::ostream & operator<<( std::ostream & out, const std::vector<T> & varray )
{
	out << "[" << varray.size() << "]";

	out << "{";

	bool first = true;

	for( const T & t : varray ) {

		if( first ) {
			first = false;
		} else {
			out << ", ";
		}

		out << t;
	}

	out << "}";

	return out;
}

} // namespace std

namespace {

template <class T, std::size_t N=10>
struct TestEqualToVector : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<span_vector<T>,std::vector<T>>;
	typedef std::function<void(CONTAINER&)> Func;
	Func func;


	std::array<T,N> data;
	span_vector<T> c;
    std::vector<T> v;

    TestEqualToVector( const std::string & descr, Func func )
	: TestCaseBase<bool>( descr, true, false ),
	  func( func ),
	  c( data.data(), data.size() ),
	  v()
	{

	}

    bool run() override
    {
    	CONTAINER cc = c;
    	CONTAINER cv = v;

        func( cc );
        func( cv );

        return std::get<0>(cc) == std::get<1>(cv);
    }
};


template <std::size_t N,class T,typename ret_type>
struct TestEqualToVectorRet : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<span_vector<T>,std::vector<T>>;
	typedef std::function<ret_type(CONTAINER&)> Func;
	Func func;

	std::array<T,N> data;
	span_vector<T> c;
    std::vector<T> v;

    TestEqualToVectorRet( const std::string & descr, Func func, bool throws_exception = false )
	: TestCaseBase<bool>( descr, true, throws_exception ),
	  func( func ),
	  c( data.data(), data.size() ),
	  v()
	{}

    bool run() override
    {
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


template <std::size_t N,class T,typename ret_type>
struct TestInsert : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<span_vector<T>,std::vector<T>>;
	typedef std::function<ret_type(CONTAINER&)> Func;
	Func func;

	std::array<T,N> data;
	span_vector<T> c;
    std::vector<T> v;

    TestInsert( const std::string & descr, Func func, bool throws_exception = false )
	: TestCaseBase<bool>( descr, true, throws_exception ),
	  func( func ),
	  c( data.data(), data.size() ),
	  v()
	{}

    bool run() override
    {
    	CONTAINER cc = c;
    	CONTAINER cv = v;

        auto ret1 = func( cc );
        auto ret2 = func( cv );

        if( ret1 != ret2 || std::get<0>(cc) != std::get<1>(cv) ) {
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

std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		// for testing data() const
		const auto & v2 = v;

		return std::strcmp( a.data(), v.data() ) == 0 && std::strcmp( a.data(), v2.data() ) == 0;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		return v.size() == 0;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		std::span<char> s( a.data(), a.size() );
		span_vector<char> v( s, s.size() );

		return ( std::strcmp( a.data(), v.data() ) == 0 ) && ( a.size() == v.size() );
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a1 = { 'H', 'e', 'l', 'l', 'o', '\0' };
		std::span<char> s1( a1.data(), a1.size() );
		span_vector<char> v1( s1, s1.size() );

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = v1;

		if( v2.size() != v1.size() ) {
			return false;
		}

		return v1 == v2;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a1 = { 'H', 'e', 'l', 'l', 'o', '\0' };
		std::span<char> s1( a1.data(), a1.size() );
		span_vector<char> v1( s1, s1.size() );

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = s1;

		if( v2.size() != v1.size() ) {
			return false;
		}

		return v1 == v2;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = { 'H', 'e', 'l', 'l', 'o', '\0' };

		return strcmp( v2.data(), "Hello" ) == 0;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign1()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.assign(5,1);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign2()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign3()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il);
						}, v );
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_size1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = { 'H', 'e', 'l', 'l', 'o', '\0' };

		return v2.size() == 6;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_capacity1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = { 'H', 'e', 'l', 'l', 'o', '\0' };

		return v2.capacity() == 10 && !v2.empty() && v2.max_size() == 10;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_reserve1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2 = { 'H', 'e', 'l', 'l', 'o', '\0' };

		v2.reserve(8);

		return true;
	});
}

namespace {

	class Reserve2 : public TestCaseBase<bool>
	{
	public:
		  Reserve2()
		  : TestCaseBase<bool>( __FUNCTION__, true, true )
		  {}

		  bool run() override {
				std::array<char,10> a2 = {};
				std::span<char> s2( a2 );
				span_vector<char> v2( s2 );

				v2 = { 'H', 'e', 'l', 'l', 'o', '\0' };

				v2.reserve(20);

				// just to call it, even if it does nothing
				v2.shrink_to_fit();
				return true;
		  }
	};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_reserve2()
{
	return std::make_shared<Reserve2>();
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at1()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			c = v.at(1);
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at2()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			c = v.at(30);
		}, v );

		return c;
	}, true );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at3()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			const auto vc = v;
			c = vc.at(1);
		}, v );

		return c;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_at1()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			c = v[1];
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_at2()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			const auto vc = v;
			c = vc[1];
		}, v );

		return c;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front1()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			c = v.front();
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front2()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			const auto vc = v;
			c = vc.front();
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		// throws exception
		v2.front();

		return true;
	}, true );
}



std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back1()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			c = v.back();
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back2()
{
	return std::make_shared<TestEqualToVectorRet<10,char,char>>(__FUNCTION__, []( auto & v ) -> char {

		char c = '\0';

		std::visit( [&c]( auto & v ) {
			v = { 'H', 'e', 'l', 'l', 'o', '\0' };
			const auto vc = v;
			c = vc.back();
		}, v );

		return c;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2 = {};
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		// throws exception
		v2.back();

		return true;
	}, true );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_begin1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		auto il = { 'H', 'e', 'l', 'l', 'o', '\0' };

		std::array<char,10> a2;
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );
		v2 = il;

		std::vector<char> v = il;

		const auto & cv2 = v2;
		const auto & cv = v;

		return *v2.begin() == *v.begin() &&
				*cv2.begin() == *cv.begin() &&
				*v2.cbegin() == *v.cbegin();
	}, false );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_begin2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a2;
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		const auto & cv2 = v2;


		return v2.begin() == v2.end() &&
				cv2.begin() == cv2.end() &&
				cv2.cbegin() == cv2.cend() &&
				v2.cbegin() == cv2.cend();
	}, false );
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_clear1()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());
							e.clear();
						}, v );
			});
}

namespace {

class TestInsert1 : public TestCaseBase<bool>
{
public:
	TestInsert1( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {

		auto il = { 1, 2, 3, 4, 5 };

		std::array<int,10> a;
		std::span<int> s(a);
		span_vector<int> c(s);
		std::vector<int> v;

		v.assign(il);
		c.assign(il);

		v.insert(v.end(),-1);
		c.insert(c.end(),-1);

		CPPDEBUG( Tools::format( "c: %s v: %s", c, v ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert1()
{
	return std::make_shared<TestInsert1>(__FUNCTION__);
}

namespace {

class TestInsert2 : public TestCaseBase<bool>
{
public:
	TestInsert2( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {

		auto il = { 1, 2, 3, 4, 5 };

		std::array<int,10> a;
		std::span<int> s(a);
		span_vector<int> c(s);
		std::vector<int> v;

		v.assign(il);
		c.assign(il);

		c.insert(c.begin()+2,-1);
		v.insert(v.begin()+2,-1);

		CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert2()
{
	return std::make_shared<TestInsert2>(__FUNCTION__);
}


namespace {

class TestInsert3 : public TestCaseBase<bool>
{
public:
	TestInsert3( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		auto il = { 1, 2, 3, 4, 5 };

		std::array<int,10> a;
		std::span<int> s(a);
		span_vector<int> c(s);
		std::vector<int> v;

		v.assign(il);
		c.assign(il);

		c.insert(c.begin(),-1);
		v.insert(v.begin(),-1);

		CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert3()
{
	return std::make_shared<TestInsert3>(__FUNCTION__);
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert4()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());

							ret = *(e.insert(e.cend(),-1));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert5()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,1> a2;
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2.insert(v2.begin(),1);
		v2.insert(v2.begin(),2); // should throw

		return true;
	}, true );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert6()
{
	return std::make_shared<TestInsert<10,std::string,std::string>>(__FUNCTION__,
			[]( auto & v ) {
				std::string ret;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<std::string> il { std::string("1"), std::string("2"), std::string("3"), std::string("4") };
							e.assign(il.begin(), il.end());

							ret = *(e.insert(e.begin()+2,std::move(std::string("hello"))));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert7()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());

							ret = *(e.insert(e.cend(), 3,-1));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert8()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							ret = *(e.insert(e.cend(), 3,-1));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert9()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,2> a2;
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		v2.insert(v2.cend(), 3,-1);

		return true;
	}, true );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert10()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());
							ret = *(e.insert(e.begin()+1, 3,-1));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert11()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());
							ret = *(e.insert(e.begin()+3, 3,-1));
						}, v );

				return ret;
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert12()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
							e.assign(il.begin(), il.end());
							ret = *(e.insert(e.begin()+3, 4,-1));
						}, v );

				return ret;
			});
}















std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert13()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3 };

							ret = *(e.insert(e.cend(), ins.begin(), ins.end() ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert14()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){

							std::initializer_list<int> ins { -1, -2, -3 };

							ret = *(e.insert(e.cend(), ins.begin(), ins.end() ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert15()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,2> a2;
		std::span<char> s2( a2 );
		span_vector<char> v2( s2 );

		std::initializer_list<int> ins { -1, -2, -3 };

		v2.insert(v2.cend(), ins.begin(), ins.end() );

		return true;
	}, true );
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert16()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3 };

							ret = *(e.insert(e.begin()+1, ins.begin(), ins.end() ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert17()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3 };

							ret = *(e.insert(e.begin()+3, ins.begin(), ins.end() ));
						}, v );

				return ret;
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert18()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3, -4 };

							ret = *(e.insert(e.begin()+3, ins.begin(), ins.end() ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert19()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3, -4 };

							ret = *(e.insert(e.begin()+3, ins ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert20()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
			[]( auto & v ) {
				int ret = 0;
				std::visit(
						[&ret](auto & e){
							std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
							e.assign(il.begin(), il.end());

							std::initializer_list<int> ins { -1, -2, -3, -4 };

							ret = *(e.insert(e.begin(), ins ));
						}, v );

				return ret;
			});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		return v.empty() && (v.erase(v.begin()) == v.end());
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		return v.erase(v.end()) == v.end();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), 1 );

		return (v.size() == 1) && (v.erase(v.begin()) == v.end() ) && v.empty();
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase4()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
						e.assign(il.begin(), il.end());

						ret = *(e.erase(e.cbegin()) );
					}, v );

			return ret;
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase5()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
						e.assign(il.begin(), il.end());

						ret = *(e.erase(e.cbegin()+1) );
					}, v );

			return ret;
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase6()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3 };
						e.assign(il.begin(), il.end());

						ret = *(e.erase(e.cbegin()+2) );
					}, v );

			return ret;
		});
}







std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase7()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		return v.empty() && (v.erase(v.begin(),v.end()) == v.end());
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase8()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size(), a.size() );

		if( v.empty() ) {
			CPPDEBUG( "not empty" );
			return false;
		}

		span_vector<char>::iterator it = v.erase(v.begin(), v.end());
		auto end = v.end();

		if( it != v.end()) {
			//CPPDEBUG( Tools::format("not the end: %s it: %p,%d end: %p,%d", v, it.parent, it.pos, end.parent, end.pos ) );
			return false;
		}

		if( !v.empty() ) {
			CPPDEBUG( "not empty" );
			return false;
		}

		return true;
	});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_erase9()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
						e.assign(il.begin(), il.end());

						ret = *(e.erase(e.cbegin()+1, e.cbegin()+5) );
					}, v );

			return ret;
		});
}




std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_push_back1()
{
	return std::make_shared<TestInsert<20,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
						e.assign(il.begin(), il.end());

						e.push_back( 88 );
						e.push_back( 88 );

						ret = e.size();
					}, v );

			return ret;
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_push_back2()
{
	return std::make_shared<TestInsert<10,int,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){
						std::initializer_list<int> il { 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
						e.assign(il.begin(), il.end());

						// should throw
						e.push_back( 88 );
						e.push_back( 88 );

						ret = e.size();
					}, v );

			return ret;
		}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_push_back3()
{
	return std::make_shared<TestInsert<20,std::string,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){

						std::initializer_list<std::string> il { "1", "2", "3", "4" };
						e.assign(il.begin(), il.end());

						e.push_back( std::string("x") );
						e.push_back( std::move( std::string("Y" ) ) );
						e.push_back( "Z" );

						ret = e.size();
					}, v );

			return ret;
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_push_back4()
{
	return std::make_shared<TestInsert<5,std::string,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){

						std::initializer_list<std::string> il { "1", "2", "3", "4" };
						e.assign(il.begin(), il.end());

						e.push_back( std::string("x") );

						ret = e.size();
					}, v );

			return ret;
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_pop_back1()
{
	return std::make_shared<TestInsert<20,std::string,int>>(__FUNCTION__,
		[]( auto & v ) {
			int ret = 0;
			std::visit(
					[&ret](auto & e){

						std::initializer_list<std::string> il { "1", "2", "3", "4" };
						e.assign(il.begin(), il.end());

						e.pop_back();

						ret = e.size();
					}, v );

			return ret;
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_pop_back2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		if( !v.empty() ) {
			return false;
		}

		v.pop_back();

		if( !v.empty() ) {
			return false;
		}

		return true;
	});
}




std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize1()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
		[]( auto & v ) {
			std::visit(
				[](auto & e){
					std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
					e.resize(8);
				}, v );
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		v.resize(20);

		return true;
	}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize3()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
		[]( auto & v ) {
			std::visit(
				[](auto & e){
					std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
					e.resize(2);
				}, v );
		});
}





std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize4()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
		[]( auto & v ) {
			std::visit(
				[](auto & e){
					std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
					e.resize(8,-1);
				}, v );
		});
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize5()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v( a.data(), a.size() );

		v.resize(20,-1);

		return true;
	}, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_resize6()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
		[]( auto & v ) {
			std::visit(
				[](auto & e){
					std::initializer_list<int> il { 1, 2, 3, 4 ,5 };
					e.resize(2,-1);
				}, v );
		});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_swap1()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a1 = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v1( a1.data(), a1.size(), a1.size() );

		std::array<char,10> a2 = { 'x', 'x', 'x', '\0' };
		span_vector<char> v2( a2.data(), a2.size(), a2.size() );

		v1.swap(v2);

		return std::strcmp( v1.data(), a2.data() ) == 0 &&
			   std::strcmp( v2.data(), a1.data() ) == 0;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_swap2()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a1 = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v1( a1.data(), a1.size(), a1.size() );

		span_vector<char> v2( a1.data(), a1.size(), a1.size() );

		v1.swap(v2);

		return std::strcmp( v1.data(), a1.data() ) == 0 &&
			   std::strcmp( v1.data(), a1.data() ) == 0;
	});
}


std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_swap3()
{
	return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

		std::array<char,10> a1 = { 'H', 'e', 'l', 'l', 'o', '\0' };
		span_vector<char> v1( a1.data(), a1.size(), a1.size() );

		span_vector<char> v2 = v1;

		v1.swap(v2);

		return std::strcmp( v1.data(), a1.data() ) == 0 &&
			   std::strcmp( v1.data(), a1.data() ) == 0;
	});
}
