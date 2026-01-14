#pragma once

#include <TestUtils.h>
#include <memory>
#include <list>

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_constructor_1();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_1();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_2();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_3();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_4();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_5();

std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_begin();
std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_end();


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_front();
std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_back();

#if __cpp_lib_span >= 202311L
std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_at();
#endif

std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_op_brackets();

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_data();

std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_size();

std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_first();
std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_last();
