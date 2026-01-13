#include <counting_span.h>
#include "test_counting_span.h"
#include <CpputilsDebug.h>

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

    CPPDEBUG( "before use after free" );

    sub[0] = 1; // should throw exception use after free

    CPPDEBUG( "after use after free" );

    sub[1] = 2;

    return false;
  }, true);
}
