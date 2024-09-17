/*
 * test_string_adapter.h
 *
 *  Created on: 17.09.2024
 *      Author: martin.oberzalek
 */
#pragma once

#include <TestUtils.h>
#include <memory>
#include <list>

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_constructor_1();

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_capacity_1();

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_max_size_1();

std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_1();
std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_2();
std::shared_ptr<TestCaseBase<bool>> test_case_string_adapter_reserve_3();

