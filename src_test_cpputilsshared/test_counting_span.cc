#include <counting_span.h>
#include "test_counting_span.h"
#include <CpputilsDebug.h>
#include <format.h>
#include <variant>

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

    auto sub = cs1.subspan( 0, 2 );

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
      sub = cs1.subspan( 0, 2 );
    }
    CPPDEBUG( "here" );

    sub[0] = 1; // should throw exception use after free

    CPPDEBUG( "here" );

    sub[1] = 2;

    CPPDEBUG( "here" );

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


      sub = sub1.subspan( 0, 2 );
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

namespace {

template <class T, typename ret_type>
struct TestEqualToSpan : public TestCaseBase<bool>
{
  using CONTAINER = std::variant<std::span<T>,counting_span<T>>;
  typedef std::function<ret_type(CONTAINER&)> Func;
  Func func;

  std::vector<T>         data;
  std::span<T>           c;
  std::basic_string<T>   v;

    TestEqualToSpan( const std::string & descr, Func func, std::initializer_list<T> list = {'h','e','l','l','o'} )
  : TestCaseBase<bool>( descr, true, false ),
    func( func ),
    data(list),
    c(data.data(), data.size()),
    v(data.data(), data.size())
  {}

  bool run() override
  {
    CONTAINER cc = c;
    CONTAINER cv = v;

    auto ret1 = func( cc );
    auto ret2 = func( cv );

    if( ret1 != ret2 ) {
      CPPDEBUG( Tools::format( "FAILED: '%s' (std::span) != '%s' (counting_span)",
          ret1,
          ret2 ) );
          return false;
    }

    return true;
  }
};

} // namespace

template<class ret_type=char>
static auto create_begin( auto func )
{
  return [func]( auto v ) -> ret_type {
    ret_type pos {};
    std::visit(
        [&pos,func](auto e){
          pos = func( e );
        }, v );
    return pos;
  };
}

std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_begin()
{

  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[1]",
      create_begin( []( auto & e ) { return *e.begin();}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[2]",
      create_begin( []( auto & e ) { return *e.cbegin();}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[3]",
      create_begin( []( auto & e ) { return *e.rbegin();}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[4]",
      create_begin( []( auto & e ) { return *e.crbegin();}) ) );

  return ret;
}


std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_end()
{

  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[1]",
      create_begin( []( auto & e ) { return *(--e.end());}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[2]",
      create_begin( []( auto & e ) { return *(--e.cend());}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[3]",
      create_begin( []( auto & e ) { return *(++e.rend());}) ) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[4]",
      create_begin( []( auto & e ) { return *(++e.crend());}) ) );

  return ret;
}


std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_front()
{
  return std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__),
      create_begin( []( auto & e ) { return e.front();}));
}

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_back()
{
  return std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__),
      create_begin( []( auto & e ) { return e.back();}));
}

#if __cpp_lib_span >= 202311L
std::list<std::shared_ptr<TestCaseBase<bool>>> test_cases_counting_span_at()
{
  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[0]",
        create_begin( []( auto & e ) { return e.at(0);})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[1]",
        create_begin( []( auto & e ) { return e.at(1);})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[2]",
        create_begin( []( auto & e ) { return e.at(2);})) );

  return ret;
}
#endif


std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_op_brackets()
{
  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[0]",
        create_begin( []( auto & e ) { return e[0];})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[1]",
        create_begin( []( auto & e ) { return e[1];})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[2]",
        create_begin( []( auto & e ) { return e[2];})) );

  return ret;
}

std::shared_ptr<TestCaseBase<bool>> test_case_counting_span_data()
{
  return std::make_shared<TestEqualToSpan<char,std::string>>(std::string(__FUNCTION__),
      create_begin<std::string>( []( auto & e ) { return std::string(e.data());}));
}


std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_size()
{
  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  // size

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[0]",
        create_begin<std::size_t>( []( auto & e ) { return e.size();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[1]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(1).size();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[2]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(3).size();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[3]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(1,2).size();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[4]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(2).subspan(1,1).size();})) );

  // size_bytes

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[5]",
        create_begin<std::size_t>( []( auto & e ) { return e.size_bytes();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[6]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(1).size_bytes();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[7]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(3).size_bytes();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[8]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(1,2).size_bytes();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[9]",
        create_begin<std::size_t>( []( auto & e ) { return e.subspan(2).subspan(1,1).size_bytes();})) );

  // empty

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[10]",
        create_begin<bool>( []( auto & e ) { return e.subspan(2).subspan(1,1).empty();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[11]",
        create_begin<bool>( []( auto & e ) { return e.subspan(0,0).empty();})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,char>>(std::string(__FUNCTION__) + "[11]",
        create_begin<bool>( []( auto & e ) { return e.empty();})) );

  return ret;
}

template<class ret_type=std::string>
static auto create_string( auto func )
{
  return [func]( auto v ) -> ret_type {
    ret_type ret {};
    std::visit(
        [&ret,func](auto e){
          auto func_ret = func( e );
          ret = std::string( func_ret.data(), func_ret.size() );
          CPPDEBUG( Tools::format( "ret: '%s'", ret ) );
        }, v );
    return ret;
  };
}

std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_first()
{
  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,std::string>>(std::string(__FUNCTION__) + "[0]",
      create_string( []( auto & e ) { return e.first(2);})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,std::string>>(std::string(__FUNCTION__) + "[1]",
      create_string( []( auto & e ) { return e.first(0);})) );

  return ret;
}

std::list<std::shared_ptr<TestCaseBase<bool>>>  test_cases_counting_span_last()
{
  std::list<std::shared_ptr<TestCaseBase<bool>>> ret;

  ret.push_back( std::make_shared<TestEqualToSpan<char,std::string>>(std::string(__FUNCTION__) + "[0]",
      create_string( []( auto & e ) { return e.last(2);})) );

  ret.push_back( std::make_shared<TestEqualToSpan<char,std::string>>(std::string(__FUNCTION__) + "[1]",
      create_string( []( auto & e ) { return e.last(0);})) );

  return ret;
}

