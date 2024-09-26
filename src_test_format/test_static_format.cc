#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <arg.h>

std::string demangle( const std::string & name );

#include "static_format.h"
#include <ColoredOutput.h>
#include <OutDebug.h>

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
	std::remove_reference<T>::type *value;


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
void add( T&& ...t )
{
	//using variant = typename pack_variant<T...>::type;
	using variant = unique_tuple<std::variant<T...>>::type;
	using vector = Tools::static_vector<variant,20>;

	vector v;

	int status = 0;

	//std::cout << typeid(variant).name() << std::endl;
	std::cout << demangle(typeid(variant).name()) << std::endl;
	std::cout << "\n";
	std::cout << demangle(typeid(vector).name()) << std::endl;
}
#endif
int main( int argc, char **argv )
{

	Arg::Arg arg( argc, argv );
	arg.addPrefix( "-" );
	arg.addPrefix( "--" );

	Arg::OptionChain oc_info;
	arg.addChainR(&oc_info);
	oc_info.setMinMatch(1);
	oc_info.setContinueOnMatch( false );
	oc_info.setContinueOnFail( true );

	Arg::FlagOption o_help( "help" );
	o_help.setDescription( "Show this page" );
	oc_info.addOptionR( &o_help );

	Arg::FlagOption o_debug("d");
	o_debug.addName( "debug" );
	o_debug.setDescription("print debugging messages");
	o_debug.setRequired(false);
	arg.addOptionR( &o_debug );

	if( !arg.parse() )
	{
		std::cout << arg.getHelp(5,20,30, 80 ) << std::endl;
		return 1;
	}

	if( o_debug.getState() )
	{
		Tools::x_debug = new OutDebug();
	}

	if( o_help.getState() ) {
		std::cout << arg.getHelp(5,20,30, 80 ) << std::endl;
		return 1;
	}

 // minimal_init( argc, argv, "", false, true );

  char buffer[250];
  std::string aa, bb;
#if 0
  add( "x", std::string("x") );

  // add( std::string("x") );
/*
  add( 1 ); //, 2, std::string() );
  */
  /*
  add( 1, 2 );
  add( 1, 2, std::string("x") );
  add( 1, 2, "x" );
  add( 1, 2, std::string(), 1.5 );
  add( 1, 2, std::string(), 1.5, std::string(), 1, 3 );
	*/
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


  //std::cout << static_format<20>("test %d %s %f","x", std::string("y"), 1) << std::endl;

  //std::cout << static_format<20>("test %d %s %f", "y" ) << std::endl;

  //std::cout << static_format<20> ("%.3s", "HALLO" ) << std::endl;



  std::cout << static_format<20>( "% 4.0f%%", (float)23.5 ) << std::endl;


#if 1
#if __cpp_exceptions > 0
  try {
#endif
      TEST( (static_format<20>( "%s", "String" )), 				sprintf( buffer, "%s", "String" ));
      TEST( (static_format<20> ("%d", 155 )),                      sprintf( buffer, "%d", 155 ));
      TEST( (static_format<20> ("%f", 155.1 )),                    sprintf( buffer, "%f", 155.1 ) );
      TEST( (static_format<20> ("%f", (double) 155.1 )) ,          sprintf( buffer, "%f", (double) 155.1 ) );
      TEST( (static_format<20> ("%x", 1515 )),                     sprintf( buffer, "%x", 1515 ) );
      TEST( (static_format<20> ("%X", 1515 )),                     sprintf( buffer, "%X", 1515 ) );
      TEST( (static_format<20> ("%05d", 3 )),                      sprintf( buffer, "%05d", 3 ) );
      TEST( (static_format<20> ("%05.f", 3.32 )),                  sprintf( buffer, "%05.f", 3.32 ) );
      TEST( (static_format<20> ("%#5x", 1515 )),                   sprintf( buffer, "%#5x", 1515 ) );
      TEST( (static_format<20> ("%#5X", 1515 )),                   sprintf( buffer, "%#5X", 1515 ) );
      TEST( (static_format<20> ("%0*2$d", 1515, 6 )),              sprintf( buffer, "%0*2$d", 1515, 6 ) );
      TEST( (static_format<20> ("%0*d", 6, 1515 )),                sprintf( buffer, "%0*d", 6, 1515 ) );
      TEST( (static_format<20> ("%*d", 6, 1515 )),                 sprintf( buffer, "%*d", 6, 1515 ) );
      TEST( (static_format<20> ("%2$*1$d", 6, 1515 )),             sprintf( buffer, "%2$*1$d", 6, 1515 ) );
      TEST( (static_format<20> ("%2$d%1$d", 6, 1515 )),            sprintf( buffer, "%2$d%1$d", 6, 1515 ) );
      TEST( (static_format<20> ("%.*f", 6, 32.32 )),               sprintf( buffer, "%.*f", 6, 32.32 ) );
      TEST( (static_format<20> ("%.*2$f", 15.15, 5 )),             sprintf( buffer, "%.*2$f", 15.15, 5 ) );
      TEST( (static_format<20> ("%.*f", 5, 15.15 )),               sprintf( buffer, "%.*f", 5, 15.15 ) );
      TEST( (static_format<20> ("%.3s", "HALLO" )),                sprintf( buffer, "%.3s", "HALLO" ) );
      TEST( (static_format<20> ("pi = %.5f", 4 * atan(1.0))),      sprintf( buffer, "pi = %.5f", 4 * atan(1.0)) );
      TEST( (static_format<20>( "%*d-%*d-%*d", 1, 3, 2, 4, 5, 6)), sprintf( buffer, "%*d-%*d-%*d", 1, 3, 2, 4, 5, 6) );
      TEST( (static_format<20>( "[%#8.3x]", 0x42 )),               sprintf( buffer, "[%#8.3x]", 0x42 ) );
      TEST( (static_format<20>( "[%#08x]", 0x42 )),                sprintf( buffer, "[%#08x]", 0x42 ) );
      TEST( (static_format<20>( "[%#8.3o]", 0x42 )),               sprintf( buffer, "[%#8.3o]", 0x42 ) );
      TEST( (static_format<20>( "[%#08o]", 0x42 )),                sprintf( buffer, "[%#08o]", 0x42 ) );
      TEST( (static_format<20>( "[%-#08x]", 0x42 )),               sprintf( buffer, "[%-#08x]", 0x42 ) );
      TEST( (static_format<20>( "[%-#08o]", 0x42 )),               sprintf( buffer, "[%-#08o]", 0x42 ) );

      TEST( (static_format<20>( "%2$s %1$s", "A", "B" )),          sprintf( buffer, "%2$s %1$s", "A", "B" ) );
      TEST( (static_format<20>( "[%]", "A" )),                     sprintf( buffer, "[%]", "A" ) );
      TEST( (static_format<20>( "%", "A" )),                       sprintf( buffer, "%", "A" ) );

      TEST( (static_format<20>( "%03d", (unsigned char)35 )),      sprintf( buffer, "%03d", (unsigned char)35 ) );
      TEST( (static_format<20>( "%03d", (char)35 )),               sprintf( buffer, "%03d", (char)35 ) );
      TEST( (static_format<20>( "%.3d", 35 )),                     sprintf( buffer, "%.3d", 35 ) );
      TEST( (static_format<20>( "%.3d", 12345 )),                  sprintf( buffer, "%.3d", 12345 ) );
      TEST( (static_format<20>( "%c", 35 )),                       sprintf( buffer, "%c", 35 ) );
      TEST( (static_format<20>( "%c", (unsigned int)35 )),         sprintf( buffer, "%c", (unsigned int)35 ) );
      TEST( (static_format<20>( "%c", (long)35 )),                 sprintf( buffer, "%c", (long)35 ) );
      TEST( (static_format<20>( "%c", (unsigned long)35 )),        sprintf( buffer, "%c", (unsigned long)35 ) );
      TEST( (static_format<20>( "%c", (short)35 )),                sprintf( buffer, "%c", (short)35 ) );
      TEST( (static_format<20>( "%c", (unsigned short)35 )),       sprintf( buffer, "%c", (unsigned short)35 ) );
      TEST( (static_format<20>( "% 4.0f%%", (float)23.5 )),  	   sprintf( buffer, "% 4.0f%%", (float)23.5 ) );
      std::cout << std::endl;

#if __cpp_exceptions > 0
  } catch( std::exception & error ) {
    std::cerr << format( "Error: %s\n", error.what() );
  }
#endif
#endif
  return 0;
}
