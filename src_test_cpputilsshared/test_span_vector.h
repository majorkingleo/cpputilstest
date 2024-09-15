/**
 * Testcases for cpputils/cpputilsshared/span_vector.h
 * @author Copyright (c) 2024 Martin Oberzalek
 */

#include <TestUtils.h>
#include <memory>

std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector1();
std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector2();
std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign2();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_assign3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign2();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_assign3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_size1();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_capacity1();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_reserve1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_reserve2();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at2();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_at3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_at1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_operator_at2();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front2();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_front3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back2();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_back3();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_begin1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_begin2();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_clear1();

std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert1();
std::shared_ptr<TestCaseBase<bool>> test_case_span_vector_insert2();

#if 0

std::shared_ptr<TestCaseBase<bool>> test_case_init_span_vector5();

std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_vector1();
std::shared_ptr<TestCaseBase<bool>> test_case_modify_static_vector2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_reverse_iterator();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert5();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert6();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert8();
std::shared_ptr<TestCaseBase<bool>> test_case_static_vector_insert9();
#endif

