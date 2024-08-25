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


std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_at_3();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_at_3();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_front_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_front_2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_back_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_back_2();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_string_view_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_iterator_4();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_empty_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_size_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_length_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_shrink_to_fit_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_clear_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_3();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_4();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_41();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_42();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_5();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_51();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_52();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_6();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_61();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_62();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_7();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_71();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_8();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_81();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_82();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_83();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_84();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_9();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_91();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_92();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_10();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_101();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_102();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_103();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_111();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_112();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_113();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_121();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_122();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_123();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_13();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_131();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_132();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_133();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_14();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_141();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_142();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_143();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_15();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_151();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_152();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_153();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_insert_154();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_13();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_21();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_22();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_23();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_31();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_32();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_erase_33();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_1();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_2();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_push_back_3();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_pop_back_1();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_13();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_21();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_22();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_23();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_24();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_31();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_32();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_33();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_41();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_42();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_43();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_44();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_51();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_52();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_53();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_54();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_61();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_62();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_63();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_64();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_71();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_72();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_73();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_74();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_81();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_82();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_83();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_84();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_91();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_92();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_93();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_94();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_101();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_102();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_103();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_104();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_111();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_112();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_append_113();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_13();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_21();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_22();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_23();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_31();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_32();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_33();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_41();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_42();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_43();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_51();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_52();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_53();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_61();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_62();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_operator_plus_63();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_11();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_12();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_13();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_21();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_22();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_23();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_31();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_32();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_33();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_41();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_42();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_43();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_51();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_52();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_53();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_61();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_62();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_63();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_64();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_65();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_66();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_71();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_72();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_73();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_74();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_75();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_76();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_81();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_82();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_83();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_84();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_85();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_86();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_91();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_92();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_93();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_101();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_102();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_103();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_111();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_112();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_113();

std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_121();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_122();
std::shared_ptr<TestCaseBase<bool>> test_case_static_string_replace_123();

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
