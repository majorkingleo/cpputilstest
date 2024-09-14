/**
 * Testcases for cpputils/io/read_file.h
 * @author Copyright (c) 2024 Martin Oberzalek
 */
#include "test_read_file.h"
#include "ColoredOutput.h"
#include <initializer_list>
#include <variant>
#include <CpputilsDebug.h>
#include <format.h>
#include <cppdir.h>
#include <vector>
#include <xml.h>
#include <string_utils.h>
#include <stderr_exception.h>
#include <filesystem>
#include <fstream>
#include <read_file.h>
#include <string.h>
#include <set>
#include <utf8.h>

using namespace Tools;

#if 0

namespace {

template <class T, std::size_t N=10>
struct TestEqualToVector : public TestCaseBase<bool>
{
	using CONTAINER = std::variant<CyclicArray<T,N>,std::vector<T>>;
	typedef std::function<void(CONTAINER&)> Func;
	Func func;

    CyclicArray<T,N> c;
    std::vector<T>   v;

    TestEqualToVector( const std::string & descr, Func func, std::initializer_list<T> list = {1,2,3,4,5,6,7,8,9,10} )
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

template <class T, std::size_t N=10>
class TestInitEqualToVector : public TestCaseBase<bool>
{
public:
	CyclicArray<T,N> c;
	std::vector<T>   v;

	TestInitEqualToVector( const std::string & descr, const CyclicArray<T,N> & c, const std::vector<T> & v )
	: TestCaseBase<bool>( descr, true ),
	  c(c),
	  v(v)
	{}

	bool run() override {
		return c == v;
	}
};


} // namespace
#endif

namespace {

class SystemInfo
{
public:
	enum class NativEncoding
	{
		UTF16LE,
		UTF32LE,
	};

	NativEncoding encoding;

public:

	SystemInfo()
	{
		CPPDEBUG( Tools::format( "sizeof(wchar_t): %d", sizeof(wchar_t) ) );

		if( sizeof(wchar_t) == sizeof(uint16_t) ) {
			encoding = NativEncoding::UTF16LE;
		}
		else if( sizeof(wchar_t) == sizeof(uint32_t) ) {
			encoding = NativEncoding::UTF32LE;
		}

		static_assert( sizeof(wchar_t) == sizeof(uint16_t) || sizeof(wchar_t) == sizeof(uint32_t) );
	}
};

static SystemInfo SYSTEM_INFO;

class TestReadFile : public TestCaseBase<bool>
{
	const std::string testcase_directory;
	std::string expected_file_name;

public:
	TestReadFile( unsigned test_number )
	: TestCaseBase<bool>( format( "read_file%02d", test_number ), true ),
	testcase_directory( format( "src_test_io/testdata/read_file%02d", test_number ) )
	{
		switch( SYSTEM_INFO.encoding )
		{
		case SystemInfo::NativEncoding::UTF16LE: expected_file_name = "expected-utf16le.txt"; break;
		case SystemInfo::NativEncoding::UTF32LE: expected_file_name = "expected-utf32le.txt"; break;
		}
	}

	std::shared_ptr<std::vector<char>> read_file_bin( const std::string & file_name )
	{
		std::size_t size = std::filesystem::file_size(file_name);
		auto data = std::make_shared<std::vector<char>>(size,0);

		std::ifstream in( file_name, std::ios_base::binary | std::ios_base::in );
		in.read( data->data(), size );

		return data;
	}

	bool run() override {
		ReadFile rf;

		const std::string in_file = CppDir::concat_dir( testcase_directory, "in.txt" );
		const std::string expected_file = CppDir::concat_dir( testcase_directory, expected_file_name );
		const std::string expected_encoding_file = CppDir::concat_dir( testcase_directory, "encoding.txt" );

		std::wstring content;

		if( !rf.read_file( in_file, content ) ) {
			throw STDERR_EXCEPTION( Tools::format( "cannot open file: '%s'", in_file ));
		}

		const std::size_t content_size = content.size() * sizeof(decltype(content)::value_type);

		std::string encoding;

		if( !XML::read_file( expected_encoding_file, encoding ) ) {
			throw STDERR_EXCEPTION( Tools::format( "cannot open file: '%s'", expected_encoding_file ));
		}

		auto vs = split_and_strip_simple( encoding );
		std::set<std::string> sencodings( vs.begin(), vs.end() );


		if( sencodings.count( rf.getFileEncoding() ) == 0 ) {
			CPPDEBUG( Tools::format( "file encoding: '%s' expected encoding: '%s'", rf.getFileEncoding(), encoding ) );
			return false;
		}

		auto data_expected = read_file_bin( expected_file );

		if( data_expected->size() != content.size() * sizeof(std::wstring::value_type) ) {
			CPPDEBUG( Tools::format( "expected size: %d contect size: %d", data_expected->size(), content_size ) );
			return false;
		}

		{
			const char16_t *u16data = reinterpret_cast<const char16_t*>(data_expected->data());
			std::u16string su16data( u16data );

			CPPDEBUG( wformat( L"check: %d", utf8::is_valid(su16data.begin(), su16data.end()) ) );
		}

		if( int n = memcmp( data_expected->data(), content.c_str(), content_size ); n != 0 ) {

			const wchar_t *wdata = reinterpret_cast<const wchar_t*>(data_expected->data());

			CPPDEBUG( wformat( L"expected: '%s'", wdata ) );
			CPPDEBUG( wformat( L"got:      '%s'", content ) );

			for( unsigned i = 0; i < content_size; i++ ) {
				if( content[i] != wdata[i] ) {
					CPPDEBUG( Tools::format( "diff[%d]: 0x%X != 0x%X ", i, static_cast<unsigned>(content[i]), static_cast<unsigned>(wdata[i]) ) );
				}
			}

			CPPDEBUG( Tools::format( "data differs: %d", n ) );
			return false;
		}

		return true;
	}
};
}

std::shared_ptr<TestCaseBase<bool>> test_case_read_file1()
{
	return std::make_shared<TestReadFile>(1);
}

std::shared_ptr<TestCaseBase<bool>> test_case_read_file2()
{
	return std::make_shared<TestReadFile>(2);
}

std::shared_ptr<TestCaseBase<bool>> test_case_read_file3()
{
	return std::make_shared<TestReadFile>(3);
}

std::shared_ptr<TestCaseBase<bool>> test_case_read_file4()
{
	return std::make_shared<TestReadFile>(4);
}

std::shared_ptr<TestCaseBase<bool>> test_case_read_file5()
{
	return std::make_shared<TestReadFile>(5);
}

