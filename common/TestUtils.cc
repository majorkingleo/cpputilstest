#include "TestUtils.h"
#include <format.h>
#include <CpputilsDebug.h>
#include <filesystem>

using namespace Tools;

bool TestCaseFuncOneFile::run()
{
	std::string file_name = Tools::format( ".%s.txt", name );
	std::filesystem::remove(file_name);

	return func( file_name );
}
