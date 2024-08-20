/**
 * Testcases for cpputils/cpputilsshared/static_string.h
 * @author Copyright (c) 2023 Martin Oberzalek
 */

#ifndef SRC_TEST_CPPUTILSSHARED_TEST_STATIC_STRING_H_
#define SRC_TEST_CPPUTILSSHARED_TEST_STATIC_STRING_H_

#include <TestUtils.h>
#include <memory>

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_constructor_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_constructor_2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_capacity_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_max_size_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_reserve_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_reserve_2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_resize_3();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_c_str_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_5();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_6();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_assign_8();

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string1();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string2();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string3();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string4();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string5();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string6();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string7();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string8();

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_replace_1();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_replace_2();


std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_string_append_1();

#if __cpp_lib_string_contains >= 202011L
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_1();
#endif

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_substr_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_substr_2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_5();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_6();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_8();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_ostream_1();

#endif /* SRC_TEST_CPPUTILSSHARED_TEST_STATIC_VECTOR_H_ */
