#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

std::string demangle( const std::string & name );

#include "static_format.h"
#include <ColoredOutput.h>


#include <cxxabi.h>

using namespace Tools;

static ColoredOutput colored_output;

#define TEST( a, b ) \
 aa = a; b; \
 bb = buffer; \
 std::cout << aa << "\t==\t" << bb << "\t: "; \
 if( aa == bb ) \
	 std::cout << colored_output.color_output( colored_output.GREEN, "true" ); \
 else \
	 std::cout <<  colored_output.color_output( colored_output.RED, "false" ); \
 std::cout << std::endl;



std::string demangle( const std::string & name )
{
	int status = 0;
	char* realname = abi::__cxa_demangle(name.c_str(), NULL, NULL, &status);

	std::string ret = realname;
	free(realname);
	return ret;
}

#if 0
template <class T>
struct RealArg
{
	T value;
};

// https://stackoverflow.com/a/62089731/20079418

// end of recursive call: tuple is forwared using `type`
template <typename T, typename... Ts>
struct unique_impl {using type = T;};

// recursive call: 1. Consumes the first type of the variadic arguments,
//                    if not repeated add it to the tuple.
//                 2. Call this again with the rest of arguments
template <template<class...> class Tuple, typename... Ts, typename U, typename... Us>
struct unique_impl<Tuple<Ts...>, U, Us...>
    : std::conditional_t<(std::is_same_v<RealArg<U>, Ts> || ...) // but pack the type in RealArg class
                       , unique_impl<Tuple<Ts...>, Us...>
                       , unique_impl<Tuple<Ts..., RealArg<U>>, Us...>> {}; // but pack the type in RealArg class

// forward definition
template <class Tuple>
struct unique_tuple;

// class specialization so that tuple arguments can be extracted from type
template <template<class...>class Tuple, typename... Ts>
struct unique_tuple<Tuple<Ts...>> : public unique_impl<Tuple<>, Ts...> {};



template<typename ...T>
void add( T ...t )
{
	//using variant = typename pack_variant<T...>::type;
	using variant = unique_tuple<std::variant<T...>>::type;

	int status = 0;

	//std::cout << typeid(variant).name() << std::endl;
	std::cout << demangle(typeid(variant).name()) << std::endl;
}
#endif
int main( int argc, char **argv )
{
 // minimal_init( argc, argv, "", false, true );

  char buffer[250];
  std::string aa, bb;
#if 0
  add( 1 ); //, 2, std::string() );
  add( 1, 2 );
  add( 1, 2, std::string() );
  add( 1, 2, std::string(), 1.5 );
  add( 1, 2, std::string(), 1.5, std::string(), 1, 3 );

  return 0;
#endif

#if 0
  using T = Tools::StaticFormat::RealArg<const char*>;

  T t( "hello" );


  std::variant<T> v( "hello" );
#endif

/*
  using T = Tools::StaticFormat::RealArg<const int*>;

  	int x;
    T t(  &x );


    std::variant<T,double> v( t );
*/


  std::cout << static_format<20,char>("test %d %s %f","x", std::string("y"), 1) << std::endl;

  std::cout << static_format<20,char> ("%.3s", "HALLO" ) << std::endl;

  //return 0;

#if __cpp_exceptions > 0
  try {
#endif

      TEST( (static_format<20,char>( "%s", "String" )), 				sprintf( buffer, "%s", "String" ));
      TEST( (static_format<20,char> ("%d", 155 )),                      sprintf( buffer, "%d", 155 ));
      TEST( (static_format<20,char> ("%f", 155.1 )),                    sprintf( buffer, "%f", 155.1 ) );
      TEST( (static_format<20,char> ("%f", (double) 155.1 )) ,          sprintf( buffer, "%f", (double) 155.1 ) );
      TEST( (static_format<20,char> ("%x", 1515 )),                     sprintf( buffer, "%x", 1515 ) );
      TEST( (static_format<20,char> ("%X", 1515 )),                     sprintf( buffer, "%X", 1515 ) );
      TEST( (static_format<20,char> ("%05d", 3 )),                      sprintf( buffer, "%05d", 3 ) );
      TEST( (static_format<20,char> ("%05.f", 3.32 )),                  sprintf( buffer, "%05.f", 3.32 ) );
      TEST( (static_format<20,char> ("%#5x", 1515 )),                   sprintf( buffer, "%#5x", 1515 ) );
      TEST( (static_format<20,char> ("%#5X", 1515 )),                   sprintf( buffer, "%#5X", 1515 ) );
      TEST( (static_format<20,char> ("%0*2$d", 1515, 6 )),              sprintf( buffer, "%0*2$d", 1515, 6 ) );
      TEST( (static_format<20,char> ("%0*d", 6, 1515 )),                sprintf( buffer, "%0*d", 6, 1515 ) );
      TEST( (static_format<20,char> ("%*d", 6, 1515 )),                 sprintf( buffer, "%*d", 6, 1515 ) );
      TEST( (static_format<20,char> ("%2$*1$d", 6, 1515 )),             sprintf( buffer, "%2$*1$d", 6, 1515 ) );
      TEST( (static_format<20,char> ("%2$d%1$d", 6, 1515 )),            sprintf( buffer, "%2$d%1$d", 6, 1515 ) );
      TEST( (static_format<20,char> ("%.*f", 6, 32.32 )),               sprintf( buffer, "%.*f", 6, 32.32 ) );
      TEST( (static_format<20,char> ("%.*2$f", 15.15, 5 )),             sprintf( buffer, "%.*2$f", 15.15, 5 ) );
      TEST( (static_format<20,char> ("%.*f", 5, 15.15 )),               sprintf( buffer, "%.*f", 5, 15.15 ) );
      TEST( (static_format<20,char> ("%.3s", "HALLO" )),                sprintf( buffer, "%.3s", "HALLO" ) );
      TEST( (static_format<20,char> ("pi = %.5f", 4 * atan(1.0))),      sprintf( buffer, "pi = %.5f", 4 * atan(1.0)) );
      TEST( (static_format<20,char>( "%*d-%*d-%*d", 1, 3, 2, 4, 5, 6)), sprintf( buffer, "%*d-%*d-%*d", 1, 3, 2, 4, 5, 6) );
      TEST( (static_format<20,char>( "[%#8.3x]", 0x42 )),               sprintf( buffer, "[%#8.3x]", 0x42 ) );
      TEST( (static_format<20,char>( "[%#08x]", 0x42 )),                sprintf( buffer, "[%#08x]", 0x42 ) );
      TEST( (static_format<20,char>( "[%#8.3o]", 0x42 )),               sprintf( buffer, "[%#8.3o]", 0x42 ) );
      TEST( (static_format<20,char>( "[%#08o]", 0x42 )),                sprintf( buffer, "[%#08o]", 0x42 ) );
      TEST( (static_format<20,char>( "[%-#08x]", 0x42 )),               sprintf( buffer, "[%-#08x]", 0x42 ) );
      TEST( (static_format<20,char>( "[%-#08o]", 0x42 )),               sprintf( buffer, "[%-#08o]", 0x42 ) );

      TEST( (static_format<20,char>( "%2$s %1$s", "A", "B" )),          sprintf( buffer, "%2$s %1$s", "A", "B" ) );
      TEST( (static_format<20,char>( "[%]", "A" )),                     sprintf( buffer, "[%]", "A" ) );
      TEST( (static_format<20,char>( "%", "A" )),                       sprintf( buffer, "%", "A" ) );

      TEST( (static_format<20,char>( "%03d", (unsigned char)35 )),      sprintf( buffer, "%03d", (unsigned char)35 ) );
      TEST( (static_format<20,char>( "%03d", (char)35 )),               sprintf( buffer, "%03d", (char)35 ) );
      TEST( (static_format<20,char>( "%.3d", 35 )),                     sprintf( buffer, "%.3d", 35 ) );
      TEST( (static_format<20,char>( "%.3d", 12345 )),                  sprintf( buffer, "%.3d", 12345 ) );
      TEST( (static_format<20,char>( "%c", 35 )),                       sprintf( buffer, "%c", 35 ) );
      TEST( (static_format<20,char>( "%c", (unsigned int)35 )),         sprintf( buffer, "%c", (unsigned int)35 ) );
      TEST( (static_format<20,char>( "%c", (long)35 )),                 sprintf( buffer, "%c", (long)35 ) );
      TEST( (static_format<20,char>( "%c", (unsigned long)35 )),        sprintf( buffer, "%c", (unsigned long)35 ) );
      TEST( (static_format<20,char>( "%c", (short)35 )),                sprintf( buffer, "%c", (short)35 ) );
      TEST( (static_format<20,char>( "%c", (unsigned short)35 )),       sprintf( buffer, "%c", (unsigned short)35 ) );

      std::cout << std::endl;

#if __cpp_exceptions > 0
  } catch( std::exception & error ) {
    std::cerr << format( "Error: %s\n", error.what() );
  }
#endif
  return 0;
}
