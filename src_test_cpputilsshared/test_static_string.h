/**
 * Testcases for cpputils/cpputilsshared/static_string.h
 * @author Copyright (c) 2023 Martin Oberzalek
 */

#ifndef SRC_TEST_CPPUTILSSHARED_TEST_STATIC_STRING_H_
#define SRC_TEST_CPPUTILSSHARED_TEST_STATIC_STRING_H_

#include <TestUtils.h>
#include <memory>

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
