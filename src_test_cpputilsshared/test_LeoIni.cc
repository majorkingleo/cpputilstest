/*
 * test_SimpleIni.cc
 *
 *  Created on: 06.09.2024
 *      Author: martin.oberzalek
 */
#include "test_LeoIni.h"
#include <CpputilsDebug.h>
#include "LeoIni.h"
#include <xml.h>
#include <fstream>
#include <format.h>
#include <filesystem>

using namespace Tools;

namespace {

class TestCaseFuncWriteIni : public TestCaseBase<bool>
{
	typedef std::function<bool( const std::string & file )> Func;
	Func func;
	std::ios_base::openmode openmode;
	std::string expected_ini_text;

public:
	TestCaseFuncWriteIni( const std::string & name,
							Func func_,
							std::ios_base::openmode openmode_,
							std::string expected_ini_text_ )
	: TestCaseBase<bool>( name, true ),
	  func( func_ ),
	  openmode( openmode_ ),
	  expected_ini_text( expected_ini_text_ )
	  {}

	bool run() override {

		std::string file_name = Tools::format( ".%s.ini", name );
		std::filesystem::remove(file_name);

		{
			if( !func( file_name ) ) {
				return false;
			}
		}

		std::string data;
		if( !XML::read_file( file_name, data ) ) {
			CPPDEBUG( Tools::format( "cannot read file '%s'", file_name ) );
			return false;
		}

		if( data != expected_ini_text ) {
			CPPDEBUG( "output text differs ");
			std::string expected_out_file_name = file_name + ".expected.ini";
			std::ofstream out( expected_out_file_name, std::ios_base::trunc | std::ios_base::out );
			if( !out ) {
				CPPDEBUG( format( "cannot open file '%s'", expected_out_file_name ) );
				return false;
			}

			out << expected_ini_text;

			return false;
		}

		return true;
	}
};


bool write_default_ini1( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file <<
			"[section1]\n" \
			"  key1=value1\n" \
			"  key2=value2\n" \
			"\n" \
			"[section2]\n" \
			"   \n"
			"  key1 = value1 \t\n" \
			" \t key2= value2 \n" \
			"[section3 ]\n" \
			"\" comment 1   \n"
			"  key3 = value3 \t\n" \
			"; comment = 2   \n"
			"  key4= value4 \n" \
			"[section4 ]\n" \
			"  key1=nolineend";


	if( !file ) {
		return false;
	}

	return true;
}

bool read( Leo::Ini & ini, const std::string & section, const std::string & key, std::string & value )
{
	Leo::Ini::Element el( Leo::Ini::Element::TYPE::KEY, section, key );
	if( !ini.read( el ) ) {
		return false;
	}

	value = el.value;

	return true;
}

bool write( Leo::Ini & ini, const std::string & section, const std::string & key, const std::string & value )
{
	Leo::Ini::Element el( Leo::Ini::Element::TYPE::KEY, section, key, value );
	if( !ini.write( el ) ) {
		return false;
	}

	return true;
}

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_read_1()
{
	auto test_func = []( const std::string & file ) {

		write_default_ini1( file );

		Leo::Ini ini( file );

		std::string value;


		if( !read( ini, "section1","key1", value ) || value != "value1" ) {
			CPPDEBUG( format( "value: %d", value ) );
			CPPDEBUG( "section1/key1 not found" );
			return false;
		}

		if( !read( ini, "section1","key2", value ) || value != "value2" ) {
			CPPDEBUG( "section1/key2 not found" );
			return false;
		}

		if( read( ini, "section1","key3", value ) ) {
			CPPDEBUG( "section1/key3 found" );
			return false;
		}

		if( !read( ini, "section2","key1", value ) || value != "value1" ) {
			CPPDEBUG( format( "section2/key1 not found (value:'%s')", value ) );
			return false;
		}

		if( !read( ini, "section2","key2", value ) || value != "value2" ) {
			CPPDEBUG( format( "section2/key2 not found (value:'%s')", value ) );
			return false;
		}

		if( !read( ini, "section3","key3", value ) || value != "value3" ) {
			CPPDEBUG( "section3/key3 not found" );
			return false;
		}

		if( !read( ini, "section3","key4", value ) || value != "value4" ) {
			CPPDEBUG( "section3/key4 not found" );
			return false;
		}

		if( !read( ini, "section4","key1", value ) || value != "nolineend" ) {
			CPPDEBUG( "section4/key1 not found" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncOneFile>(__FUNCTION__, test_func,
			std::ios_base::in | std::ios_base::out | std::ios_base::trunc );
}

namespace {

bool write_default_ini2( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file << "[section4 ]\n" \
			"  key1=nolineend";

	if( !file ) {
		return false;
	}

	return true;
}

}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_read_2()
{
	auto test_func = []( const std::string & file_name ) {

		write_default_ini2( file_name );

		Leo::Ini ini( file_name );

		std::string value;

		if( !read( ini, "section4","key1", value ) || value != "nolineend" ) {
			CPPDEBUG( format( "section4/key1 not found (value:'%s')", value ) );
			return false;
		}
		return true;
	};

	return std::make_shared<TestCaseFuncOneFile>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc );
}

namespace {

bool write_default_ini3( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file <<
			"[section4 ]\n" \
			"  key1=";

	if( !file ) {
		return false;
	}

	return true;
}

}


std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_read_3()
{
	auto test_func = []( const std::string & file_name ) {

		write_default_ini3( file_name );

		Leo::Ini ini( file_name );

		std::string value;

		if( !read( ini, "section4","key1", value ) || value != "" ) {
			CPPDEBUG( format( "section4/key1 not found (value:'%s')", value ) );
			return false;
		}
		return true;
	};

	return std::make_shared<TestCaseFuncOneFile>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc );
}


namespace {

bool write_default_ini4( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file << 	"[section4 ]\n" \
			"  key1 ";

	if( !file ) {
		return false;
	}


	return true;
}

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_read_4()
{
	auto test_func = []( const std::string & file_name ) {

		write_default_ini4( file_name );

		Leo::Ini ini( file_name );

		std::string value;

		if( read( ini, "section4","key1", value ) ) {
			CPPDEBUG( format( "section4/key1 found (value:'%s')", value ) );
			return false;
		}
		return true;
	};

	return std::make_shared<TestCaseFuncOneFile>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc );
}

namespace {

bool write_default_ini5( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file << 	" key1 ";

	if( !file ) {
		return false;
	}

	return true;
}

} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_read_5()
{
	auto test_func = []( const std::string & file_name ) {

		write_default_ini5( file_name );

		Leo::Ini ini( file_name );

		std::string value;

		if( read( ini, "section4","key1", value ) ) {
			CPPDEBUG( format( "section4/key1 found (value:'%s')", value ) );
			return false;
		}
		return true;
	};

	return std::make_shared<TestCaseFuncOneFile>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc );
}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_1()
{
	std::string expected_text =
			"[section1]\n" \
			"key1 = value1\n";

	auto test_func = []( const std::string & file_name ) {

		Leo::Ini ini( file_name, std::ios_base::out | std::ios_base::trunc );

		if( !ini ) {
			CPPDEBUG( Tools::format( "cannot open ini file '%s'", file_name ) );
			return false;
		}

		std::string value;

		if( !write( ini, "section1","key1", "value1" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_2()
{
	std::string expected_text =
			"[section1]\n" \
			"key1 = value1\n" \
			"\n" \
			"[section2]\n" \
			"key2 = value2\n";

	auto test_func = []( const std::string & file ) {

		Leo::Ini ini( file, std::ios_base::out | std::ios_base::trunc );

		std::string value;

		if( !write( ini, "section1","key1", "value1" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		if( !write( ini, "section2","key2", "value2" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

namespace {
bool write_default_ini6( const std::string & file_name )
{
	std::fstream file( file_name, std::ios_base::out | std::ios_base::trunc );

	if( !file ) {
		return false;
	}

	file <<	"[section1]\n" \
			";\tcomment1\n"
			"key1 = value1\n" \
			"\n" \
			"[section2]\n" \
			";\tcomment 2\n"
			"key2 = value2\n";

	if( !file ) {
		return false;
	}


	return true;
}
} // namespace

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_3()
{
	std::string expected_text =
			"[section1]\n" \
			";\tcomment1\n"
			"key1 = value3\n" \
			"\n" \
			"[section2]\n" \
			";\tcomment 2\n"
			"key2 = value4\n";

	auto test_func = []( const std::string & file ) {

		if( !write_default_ini6( file ) ) {
			return false;
		}

		Leo::Ini ini( file );

		if( !ini ) {
			return false;
		}

		if( !ini.read() ) {
			return false;
		}


		std::string value;

		if( !write( ini, "section1","key1", "value3" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		if( !write( ini, "section2","key2", "value4" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_4()
{
	std::string expected_text =
			"[section1]\n" \
			"\tkey1 = value1\n" \
			"key3 = value3\n" \
			"\n" \
			"[section2]\n" \
			"\tkey2 = value2\n";

	auto test_func = []( const std::string & file_name ) {

		{
			std::fstream file( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::trunc );

			file << 	"[section1]\n" \
					"\tkey1 = value1\n" \
					"\n" \
					"[section2]\n" \
					"\tkey2 = value2\n";


			if( !file ) {
				return false;
			}
		}

		Leo::Ini ini( file_name );

		if( !ini.read() ) {
			return false;
		}

		if( !write( ini, "section1","key3", "value3" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}


std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_5()
{
	std::string expected_text =
			"[section1]\n" \
			"\tkey1 = value1\n" \
			"key3 = value3\n" \
			"\n" \
			"[section2]\n" \
			"\tkey2 = value2\n";

	auto test_func = []( const std::string & file_name ) {

		{
			std::fstream file( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::trunc );

			file << 	"[section1]\n" \
					"\tkey1 = value1\n" \
					"\n" \
					"[section2]\n" \
					"\tkey2 = value2\n";


			if( !file ) {
				return false;
			}
		}

		Leo::Ini ini( file_name );

		if( !ini.read() ) {
			return false;
		}

		if( !write( ini, "section1","key3", "value3" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_6()
{
	std::string expected_text =
			"[section1]\n" \
			"key3 = value3\n" \
			";\tcomment 3\n" \
			"\n" \
			"[section2]\n" \
			"\tkey2 = value2\n";

	auto test_func = []( const std::string & file_name ) {

		{
			std::fstream file( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::trunc );

			file <<	"[section1]\n" \
					";\tcomment 3\n"
					"\n" \
					"[section2]\n" \
					"\tkey2 = value2\n";


			if( !file ) {
				return false;
			}
		}

		Leo::Ini ini( file_name );

		if( !ini.read() ) {
			return false;
		}

		if( !write( ini, "section1", "key3", "value3" ) ) {
			CPPDEBUG( "writing failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

std::shared_ptr<TestCaseBase<bool>> test_case_leo_ini_write_7()
{
	std::string expected_text =
			"[section1]\n" \
			"key1 = value1\n" \
			"key3 = value3\n" \
			"\n" \
			"[section2]\n" \
			"key2 = value2\n";

	auto test_func = []( const std::string & file ) {

		Leo::Ini ini( file, std::ios_base::in | std::ios_base::out | std::ios_base::trunc );

		if( !write( ini, "section1", "key1", "value1"  ) ) {
			CPPDEBUG( "writing key1 failed" );
			return false;
		}

		if( !write( ini, "section2", "key2", "value2"  ) ) {
			CPPDEBUG( "writing key2 failed" );
			return false;
		}

		if( !write( ini, "section1", "key3", "value3" ) ) {
			CPPDEBUG( "writing key3 failed" );
			return false;
		}

		return true;
	};

	return std::make_shared<TestCaseFuncWriteIni>(__FUNCTION__, test_func,
				std::ios_base::in | std::ios_base::out | std::ios_base::trunc, expected_text );
}

