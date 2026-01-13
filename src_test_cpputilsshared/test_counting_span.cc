#include <counting_span.h>
#include "test_counting_span.h"
#include <CpputilsDebug.h>
#include <format.h>

using namespace Tools;

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_constructor_1()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    std::vector<int> v(10);
    std::span<int> sv( v.data(), v.size() );

    counting_span<int>  cs1( sv );
    counting_span<int>  cs2( v.data(), v.size() );

    cs1[0] = 1;
    cs2[1] = 2;

    if( cs2[0] == 1 &&
        cs1[1] == 2 ) {
        return true;
    }

    return false;
  });
}


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_1()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    std::vector<int> v(10);
    std::span<int> sv( v.data(), v.size() );

    counting_span<int>  cs1( sv );

    auto sub = cs1.subspan( 0, 1 );

    sub[0] = 1;
    sub[1] = 2;

    if( cs1[0] == 1 &&
        cs1[1] == 2 ) {
        return true;
    }


    return false;
  });
}


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_2()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    sub_counting_span<int> sub;

    {
      std::vector<int> v(10);
      counting_span<int>  cs1( v.data(), v.size() );
      sub = cs1.subspan( 0, 1 );
    }

    sub[0] = 1; // should throw exception use after free
    sub[1] = 2;

    return false;
  }, true);
}

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_3()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    sub_counting_span<int> sub;

    {
      std::vector<int> v(10);
      counting_span<int>  cs1( v.data(), v.size() );
      [[maybe_unused]]
      auto sub1 = cs1.subspan( 0, v.size() );

      [[maybe_unused]]
      auto sub2 = cs1.subspan( 0, v.size() );

      {
        [[maybe_unused]]
        auto sub3 = cs1.subspan( 0, v.size() );
      }

      [[maybe_unused]]
      auto sub4 = cs1.subspan( 0, v.size() );


      sub = sub1.subspan( 0, 1 );
    }

    sub[0] = 1; // should throw exception use after free
    sub[1] = 2;

    return false;
  }, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_4()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    sub_counting_span<int> sub;

    {
      std::vector<int> v(10);
      counting_span<int>  cs1( v.data(), v.size() );
      [[maybe_unused]]
      auto sub1 = cs1.subspan( 1, 8 );

      [[maybe_unused]]
      auto sub2 = sub1.subspan( 1, 6 );

      {
        {
          [[maybe_unused]]
          auto sub3 = sub2.subspan( 1, 4 );
        }
      }

      [[maybe_unused]]
      auto sub4 = cs1.subspan( 0, v.size() );


      sub = sub1.subspan( 0, 1 );
    }

    sub[0] = 1; // should throw exception use after free
    sub[1] = 2;

    return false;
  }, true);
}


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_subspan_5()
{
  return std::make_shared<TestCaseFuncNoInp>(__FUNCTION__, true, []() {

    sub_counting_span<int> sub;

    std::vector<int> v(10);
    counting_span<int>  cs1( v.data(), v.size() );
    [[maybe_unused]]
    auto sub1 = cs1.subspan( 1, 8 );

    [[maybe_unused]]
    auto sub2 = sub1.subspan( 1, 6 );

    {
      {
        [[maybe_unused]]
        auto sub3 = sub2.subspan( 1, 4 );
      }
    }

    [[maybe_unused]]
    auto sub4 = cs1.subspan( 0, v.size() );

    sub = sub1.subspan( 0, 1 );


    sub[0] = 1; // should throw exception use after free
    sub[1] = 2;

    for( unsigned i = 0; i < v.size(); ++i ) {
        CPPDEBUG( Tools::format( "[%d]: %d", i, v[i]));
    }

    if( cs1[1] == 1 &&
        cs1[2] == 2 ) {
        return true;
    }

    return false;
  });
}
