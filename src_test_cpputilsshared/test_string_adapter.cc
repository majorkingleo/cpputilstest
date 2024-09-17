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

