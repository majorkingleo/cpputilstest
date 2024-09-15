/**
 * Testcases for cpputils/cpputilsshared/CyclicArray.h
 * @author Copyright (c) 2023 Martin Oberzalek
 */
#include <span_vector.h>
#include "test_static_vector.h"
#include "ColoredOutput.h"
#include <initializer_list>
#include <variant>
#include <CpputilsDebug.h>
#include <format.h>
#include <cstring>
#include <vector>

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


#if 0
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_vector1()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.erase(e.begin());
						}, v );
			});
}


std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_vector2()
{
	return std::make_shared<TestEqualToVector<int,10>>(__FUNCTION__,
			[]( auto & v ) {
				std::visit(
						[](auto & e){
							e.erase(e.begin()+3);
						}, v );
			});
}

namespace {

class TestReverseIterator : public TestCaseBase<bool>
{
public:
	TestReverseIterator( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c({ 1, 2, 3, 4, 5 });
		std::vector<int> v({ 1, 2, 3, 4, 5 });

		if( *c.rbegin() != *v.rbegin() ) {
			return false;
		}

		if( *(--c.rend()) != *(--v.rend()) ) {
			return false;
		}

		return true;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_reverse_iterator()
{
	return std::make_shared<TestReverseIterator>(__FUNCTION__);
}

namespace {

class TestInsert1 : public TestCaseBase<bool>
{
public:
	TestInsert1( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c({ 1, 2, 3, 4, 5 });
		std::vector<int> v({ 1, 2, 3, 4, 5 });

		v.insert(v.end(),-1);
		c.insert(c.end(),-1);

		CPPDEBUG( Tools::format( "c: %s v: %s", c, v ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert1()
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
		static_vector<int,10> c({ 1, 2, 3, 4, 5 });
		std::vector<int> v({ 1, 2, 3, 4, 5 });

		c.insert(c.begin()+2,-1);
		v.insert(v.begin()+2,-1);

		CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert2()
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
		static_vector<int,10> c({ 1, 2, 3, 4, 5 });
		std::vector<int> v({ 1, 2, 3, 4, 5 });

		c.insert(c.begin(),-1);
		v.insert(v.begin(),-1);

		CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert3()
{
	return std::make_shared<TestInsert3>(__FUNCTION__);
}

namespace {

class InstanceCounter
{
	std::string name;
	std::string pos;
	unsigned count = 0;

public:
	InstanceCounter( const std::string & name = "x", const std::string & pos = "x" )
	: name( name ),
	  pos(pos)
	{
	}

	InstanceCounter( const InstanceCounter & other )
	: name( other.name ),
	  pos(other.pos),
	  count( other.count + 1 )
	{
		CPPDEBUG( Tools::format( "%s:%s %s %d", __FUNCTION__, pos, name, count ) );
	}

	InstanceCounter( InstanceCounter && other )
	: name( other.name ),
	  pos(other.pos),
	  count( other.count )
	{
		CPPDEBUG( Tools::format( "%s:%s %s %d", __FUNCTION__, pos, name, count ) );
	}

	~InstanceCounter() {
		CPPDEBUG( Tools::format( "%s:%s %s %d", __FUNCTION__, pos, name, count ) );
	}

	const InstanceCounter & operator=( const InstanceCounter & other )
	{
		CPPDEBUG( Tools::format( "%s:%s %s %d", __FUNCTION__, pos, name, count ) );
		name = other.name;
		pos = other.pos;
		count++;
		return *this;
	}

	bool operator!=( const InstanceCounter & other ) const
	{
		if( count != other.count ) {
			CPPDEBUG( Tools::format( "%s:%s %s %d count is differtent", __FUNCTION__, pos, name, count ) );
			return true;
		}

		if( name != other.name ) {
			CPPDEBUG( Tools::format( "%s:%s %s %d name is different", __FUNCTION__, pos, name, count ) );
			return true;
		}

		return false;
	}
};

class TestInsert4 : public TestCaseBase<bool>
{
public:
	TestInsert4( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<InstanceCounter,10> c;
		std::vector<InstanceCounter> v;

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace


std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert4()
{
	return std::make_shared<TestInsert4>(__FUNCTION__);
}

namespace {

class TestInsert5 : public TestCaseBase<bool>
{
public:
	TestInsert5( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<InstanceCounter,10> c;
		std::vector<InstanceCounter> v;
		v.reserve(10);

		c.push_back(InstanceCounter("a", "c"));
		c.insert(c.begin(),InstanceCounter("b", "c"));

		v.push_back(InstanceCounter("a", "v"));
		v.insert(v.begin(),InstanceCounter("b", "v"));

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert5()
{
	return std::make_shared<TestInsert5>(__FUNCTION__);
}

namespace {

class TestInsert6 : public TestCaseBase<bool>
{
public:
	TestInsert6( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c;
		std::vector<int> v { 1, 2, 3, 4, 5 };
		v.reserve(10);

		c = v;

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert6()
{
	return std::make_shared<TestInsert6>(__FUNCTION__);
}


namespace {

class TestInsert7 : public TestCaseBase<bool>
{
public:
	TestInsert7( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c;
		std::pmr::vector<int> v { 1, 2, 3, 4, 5 };
		v.reserve(10);

		c = v;

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert7()
{
	return std::make_shared<TestInsert7>(__FUNCTION__);
}


namespace {

class TestInsert8 : public TestCaseBase<bool>
{
public:
	TestInsert8( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c { 1, 2, 3, 4, 5 };
		std::pmr::vector<int> v;
		v.reserve(10);

		v = c;

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert8()
{
	return std::make_shared<TestInsert8>(__FUNCTION__);
}



namespace {

class TestInsert9 : public TestCaseBase<bool>
{
public:
	TestInsert9( const std::string & descr )
	: TestCaseBase<bool>( descr, true, false )
	{}

	bool run() override {
		static_vector<int,10> c { 1, 2, 3, 4, 5 };
		std::vector<int> v;
		v.reserve(10);

		v = c;

		//CPPDEBUG( Tools::format("v: %s c: %s", v, c ) );

		return c == v;
	}
};

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert9()
{
	return std::make_shared<TestInsert9>(__FUNCTION__);
}

#endif
