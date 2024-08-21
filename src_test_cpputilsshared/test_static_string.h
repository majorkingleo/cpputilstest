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

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_to_basic_string_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_5();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_6();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_8();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_9();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_10();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_13();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_14();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_assign_15();


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
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_5();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_6();
#else
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_8();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_9();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_10();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_contains_12();
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
