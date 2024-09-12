/**
 * Classes for type safe versions of sprintf() that are returning a std::string
 * @author Copyright (c) 2001 - 2024 Martin Oberzalek
 *
 * C++-11 version with variadic templates
 *
 * Examples:
 *    std::cout << format( "Hello %s, I have $05d$ in my pocket", "world", 5 ) << std::endl;
 *    std::cout << format( "Do not try this with printf: %s", 10101 ) << std::endl;
 *
 */

#pragma once

#if __cplusplus - 0 >= 201103L

#include <string>
#include <iomanip>
#include <iostream>

#include <sstream>
#include <cctype>
#include <variant>
#include <static_vector.h>
#include <static_string.h>
#include <cformat.h>
#include <type_traits>
#include <charconv>

namespace Tools {

  namespace StaticFormat
  {
    class BaseException : public std::exception
    {
      const char *err;

    public:
      BaseException(const BaseException& ex): std::exception() , err ( ex.err ) {}
      BaseException( const char* e ) : std::exception(), err( e ) {}
      BaseException & operator=(const BaseException& ex) { err = ex.err; return *this; }

      virtual const char* what() const throw() { return err; }
    };

    template<std::size_t N_SIZE>
    class BaseArg
    {
      bool _is_int;
      bool _is_string;

    public:
      BaseArg( bool is_int_ = false, bool is_string_  = false )
    : _is_int( is_int_ ),
      _is_string( is_string_ )
    {}
      virtual ~BaseArg() {}

      bool isInt() { return _is_int; }
      bool isString() { return _is_string; }

      virtual Tools::static_string<N_SIZE> doFormat( const Format::CFormat & cf ) = 0;
      virtual int get_int() {
        if( !isInt() ) {
#if __cpp_exceptions > 0
            throw BaseException( "expecting int arg" );
#else
            std::abort();
#endif
        }
        return 0;
      }

      template <class N> bool is_int( const N &n ) const { return false; }
      bool is_int( const int* n ) const { return true; }
      bool is_int( const unsigned int* n ) const { return true; }
      bool is_int( const short* n ) const { return true; }
      bool is_int( const unsigned short* ) const { return true; }
      bool is_int( const unsigned long* ) const { return true; }
      bool is_int( const unsigned long long* ) const { return true; }
      bool is_int( const long long* ) const { return true; }

      template <class S> bool is_string( const S &s_ ) const { return false; }
      bool is_string( std::string* s_ ) const { return true; }
      bool is_string( const std::string* s_ ) const { return true; }
      bool is_string( std::string_view* s_ ) const { return true; }
      bool is_string( const std::string_view* s_ ) const { return true; }
      bool is_string( char** ) const { return true; }
      bool is_string( const char** ) const { return true; }
      bool is_string( const char* const* ) const { return true; }
    };

    template<typename Arg, std::size_t N_SIZE>
    class RealArg : public BaseArg<N_SIZE>
    {
      const Arg *arg;
    public:

      RealArg( const Arg & arg_ )
		: BaseArg<N_SIZE>( BaseArg<N_SIZE>::is_int( &arg_ ), BaseArg<N_SIZE>::is_string( &arg_ ) ),
		  arg(&arg_)
		{
		}

      Tools::static_string<N_SIZE> doFormat( const Format::CFormat & cf ) override
      {
        return x2s( *arg, cf );;
      }

      int get_int() override {
        BaseArg<N_SIZE>::get_int();
        return get_int(*arg);
      }


    private:
      template<class T> int get_int( const T &t ) { return 0; }
      int get_int( int n ) { return (int)n; }
      int get_int( unsigned int n ) { return (int)n; }
      int get_int( short n ) { return (int)n; }
      int get_int( unsigned short n ) { return (int)n; }
      int get_int( long long n ) { return (int)n; }
      int get_int( unsigned long long n  ) { return (int)n; }
      int get_int( long n ) { return (int)n; }
      int get_int( unsigned long n ) { return (int)n; }


      template <class S> static std::string x2s( S ss, const Format::CFormat &cf )
      {
        std::stringstream str;
        str << cf << ss;
        return str.str();
      }
    };

    template <std::size_t N_SIZE, class BaseArgType, class CastTo>
    class RealArgCastFromChar : public BaseArg<N_SIZE>
        {
          const BaseArgType arg;
        public:
          RealArgCastFromChar( const BaseArgType & arg_ )
        : BaseArg<N_SIZE>( false, false ),
          arg(arg_)
        {}

          Tools::static_string<N_SIZE> doFormat( const Format::CFormat & cf ) override
          {
            std::stringstream str;
            str << cf;

            if( cf.numerical_representation )
              str << static_cast<CastTo>(arg);
            else
              str << arg;

            return str.str();
          }
        };

    template <std::size_t N_SIZE>
    class RealArg<unsigned char,N_SIZE> : public RealArgCastFromChar<N_SIZE,unsigned char,int>
    {
    public:
      RealArg( const unsigned char & arg_ )
        : RealArgCastFromChar<N_SIZE,unsigned char,int>( arg_ )
       {}
    };

    template <std::size_t N_SIZE>
    class RealArg<char,N_SIZE> : public RealArgCastFromChar<N_SIZE,char,int>
    {
    public:
      RealArg( const char & arg_ )
        : RealArgCastFromChar<N_SIZE,char,int>( arg_ )
       {}
    };

    template <std::size_t N_SIZE, class BaseArgType, class CastTo>
    class RealArgCastFromInt : public BaseArg<N_SIZE>
        {
          const BaseArgType arg;
        public:
          RealArgCastFromInt( const BaseArgType & arg_ )
        : BaseArg<N_SIZE>( true, false ),
          arg(arg_)
        {}

          Tools::static_string<N_SIZE> doFormat( const Format::CFormat & cf ) override
          {
            std::stringstream str;
            str << cf;

            if( cf.character_representation )
              str << static_cast<CastTo>(arg);
            else
              str << arg;

            return str.str();
          }

          int get_int() override {
            BaseArg<N_SIZE>::get_int();
            return arg;
          }
        };

    template <std::size_t N_SIZE>
    class RealArg<int,N_SIZE> : public RealArgCastFromInt<N_SIZE,int,char>
    {
    public:
      RealArg( const int & arg_ )
        : RealArgCastFromInt<N_SIZE,int,char>( arg_ )
       {}
    };

#define INT_REAL_ARG_CAST( type )\
    template <std::size_t N_SIZE> \
    class RealArg<type,N_SIZE> : public RealArgCastFromInt<N_SIZE,type,char>\
    {\
    public:\
      RealArg( const type & arg_ )\
        : RealArgCastFromInt<N_SIZE,type,char>( arg_ )\
       {}\
    }

    INT_REAL_ARG_CAST( unsigned int );
    INT_REAL_ARG_CAST( short );
    INT_REAL_ARG_CAST( unsigned short );
    INT_REAL_ARG_CAST( long );
    INT_REAL_ARG_CAST( unsigned long );

#undef INT_REAL_ARG_CAST

    template<std::size_t N_SIZE,typename VECTOR_LIKE, typename Arg> void add_argsx(  VECTOR_LIKE & v_args, Arg & arg )
    {
      v_args.push_back( RealArg<Arg,N_SIZE>(arg) );
    }

    template<std::size_t N_SIZE, typename VECTOR_LIKE, typename A, typename... Arg> void add_args( VECTOR_LIKE & v_args, A & a, Arg... arg )
    {
      add_argsx<N_SIZE>( v_args, a );
      add_args<N_SIZE>( v_args, arg... );
    }

    template<std::size_t N_SIZE,typename VECTOR_LIKE>
    inline void add_args( VECTOR_LIKE & v_args )
    {

    }

    template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
    class Format
    {
    private:
      struct Arg
      {
        bool is_int;
        bool is_string;
      };

      VECTOR_LIKE & args;

      std::string format;

      static constexpr unsigned int num_of_args = N_ARGS;

      Tools::static_string<N_SIZE> s;

    private:
      Format() = delete;
      Format(const Format & f) = delete;
      Format & operator=(const Format & f) = delete;

    public:
      Format( const std::string_view &format_, VECTOR_LIKE & args_ )
      : args(args_),
        format(format_),
        s()
      {
         parse();
      }

      const Tools::static_string<N_SIZE> & get_string() const { return s; }

    private:
      void parse();

      int get_int_arg( int num );
      void gen_arg_list();
      Tools::static_string<N_SIZE> use_arg( unsigned int i, const Tools::Format::CFormat &cf );

      template<class T> int get_int( const T &t ) { return 0; }
      int get_int( int n ) { return (int)n; }
      int get_int( unsigned int n ) { return (int)n; }
      int get_int( short n ) { return (int)n; }
      int get_int( unsigned short n ) { return (int)n; }
      int get_int( long long n ) { return (int)n; }
      int get_int( unsigned long long n  ) { return (int)n; }
      int get_int( long n ) { return (int)n; }
      int get_int( unsigned long n ) { return (int)n; }


      int skip_atoi( const std::string_view & s, std::string::size_type start, std::string::size_type & pos ) const;
      Tools::static_string<N_SIZE> substitude( const std::string_view & str_orig, const std::string & what, const std::string & with, std::string::size_type start = 0 ) const;
    }; // class StaticFormat



    namespace pack_real_args_impl {
		// https://stackoverflow.com/a/62089731/20079418

		// end of recursive call: tuple is forwared using `type`
		template <std::size_t N_SIZE, typename T, typename... Ts>
		struct unique_impl {using type = T;};

		// recursive call: 1. Consumes the first type of the variadic arguments,
		//                    if not repeated add it to the tuple.
		//                 2. Call this again with the rest of arguments
		template <std::size_t N_SIZE, template<class...> class Tuple, typename... Ts, typename U, typename... Us>
		struct unique_impl<N_SIZE, Tuple<Ts...>, U, Us...>
			: std::conditional_t<(std::is_same_v<RealArg<U,N_SIZE>, Ts> || ...) // but pack the type in RealArg class
							   , unique_impl<N_SIZE,Tuple<Ts...>, Us...>
							   , unique_impl<N_SIZE,Tuple<Ts..., RealArg<U,N_SIZE>>, Us...>> {}; // but pack the type in RealArg class

		// forward definition
		template <std::size_t N_SIZE,class Tuple>
		struct unique_tuple;

		// class specialization so that tuple arguments can be extracted from type
		template <std::size_t N_SIZE, template<class...>class Tuple, typename... Ts>
		struct unique_tuple<N_SIZE,Tuple<Ts...>> : public unique_impl<N_SIZE,Tuple<>, Ts...> {};

    } // namespace pack_real_args_impl

  } // namespace StaticFormat
} // /namespace Tools

namespace Tools {
  template <std::size_t N_SIZE, typename CharT, typename... Args>
  Tools::static_basic_string<N_SIZE,CharT> static_format( const std::basic_string_view<CharT> & format, Args... args )
  {
	using namespace StaticFormat;

	constexpr auto N_ARGS = sizeof...(Args);
	using variant = pack_real_args_impl::unique_tuple<N_SIZE,std::variant<Args...>>::type;
	using vector = Tools::static_vector<variant,N_ARGS>;

    vector v_args;

    // std::cout << " v_args member size: %d " << sizeof(variant) << std::endl;

    StaticFormat::add_args<N_SIZE>( v_args, args... );

    StaticFormat::Format<N_ARGS,N_SIZE,vector> f2( format, v_args );

    return f2.get_string();
  }
} // /namespace Tools
#endif

namespace Tools::StaticFormat {

template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
int Format<N_ARGS,N_SIZE,VECTOR_LIKE>::get_int_arg( int num )
{
    if( static_cast<unsigned int>(num) > num_of_args - 1 ) {
#if __cpp_exceptions > 0
      throw BaseException( "The arg you wan't to use is out of range" );
#else
      std::abort();
#endif
    }

    if( num < 0 ) {
#if __cpp_exceptions > 0
      throw BaseException( "negativ number for arg number not allowed" );
#else
      std::abort();
#endif
    }

    bool is_int = false;
    std::visit( [&is_int]( auto & real_arg ) {
  	  if( real_arg.isInt() ) {
  		  is_int = true;
  	  }
    }, args[num] );

    if( is_int )
      {
        int value = 0;
        std::visit( [&value]( auto & real_arg ) {
      	  value = real_arg.get_int();
        }, args[num] );

        return value;
      }
    else {
#if __cpp_exceptions > 0
      throw BaseException( "expecting int arg" );
#else
      std::abort();
#endif
    }

    return 0; // should never be reached
}

template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
Tools::static_string<N_SIZE> Format<N_ARGS,N_SIZE,VECTOR_LIKE>::use_arg( unsigned int i, const Tools::Format::CFormat &cf )
{
  if( i > num_of_args ) {
#if __cpp_exceptions > 0
    throw BaseException( "out of arg range" );
#else
    std::abort();
#endif
  }

  Tools::static_string<N_SIZE> s;

  std::visit( [&s,&cf]( auto & real_arg ){
	  s = real_arg.doFormat(cf);
  }, args[i] );

  return s;
}

template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
int Format<N_ARGS,N_SIZE,VECTOR_LIKE>::skip_atoi( const std::string_view & s, std::string::size_type start, std::string::size_type & pos ) const
{
  pos = start;
  std::string::size_type len = s.size();

  while( (pos < len) && isdigit( s[pos] ) )
    pos++;

  std::string_view sv = s.substr( start, start-pos );

  int res = 0;

  std::from_chars( sv.data(), sv.data() + sv.size(), res );
  return res;
}

template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
Tools::static_string<N_SIZE> Format<N_ARGS,N_SIZE,VECTOR_LIKE>::substitude( const std::string_view & str_orig, const std::string & what, const std::string & with, std::string::size_type start  ) const
{
  using string_t = Tools::static_string<N_SIZE>;

  std::string::size_type pos=start;

  if( what.empty() ) {
    return string_t(str_orig);
  }

  string_t str( str_orig );

  for(;;)
    {
      pos = str.find( what, pos );
      if( pos == std::string::npos ) {
        break;
      }

      if( with.empty() )
        {
    	  auto s = str.substr( 0, pos );
          s += str.substr( pos + what.size() );
          str = s;
          continue;
        }
      else
        {
          str.replace( pos, what.size(), with );
        }

      pos += with.size();
    }
  return str;
}

template<std::size_t N_ARGS,std::size_t N_SIZE,typename VECTOR_LIKE>
void Format<N_ARGS,N_SIZE,VECTOR_LIKE>::parse()
{
  using CFormat = Tools::Format::CFormat;
  using string_t = Tools::static_string<N_SIZE>;

  if( format.empty() )
    return;

  unsigned int par = 0;
  unsigned int use_par = 0;
  std::string::size_type pos = 0;
  std::string::size_type  len = format.size();
  s = "";

  while( par < num_of_args && pos < len )
    { // while
      bool had_precision = false;

      use_par = par;

      if( pos >= len )
        break;

      if( format[pos] != '%' )
        {
          s += format[pos];
          pos++;
          continue;
        }

      // % digit found
      pos++;

      if( !(pos < len ) || (format[pos] == '%') )
        {
          // %% -> %
          s += format[pos];
          pos++;
          continue;
        }

      // format string found

      std::string::size_type start = pos - 1;
      CFormat cf;

      // process flags

      while( (pos < len) )
        {
          bool finished = false;

          switch( format[pos] )
          {
          case '-' : cf.adjust = CFormat::LEFT; break;
          case '+' : cf.sign = true; break;
          case ' ' : cf.zero = false; break;
          case '#' : cf.special = true; break;
          case '\'': cf.grouping = true; break;
          case 'I' : cf.conversion = true; break;
          case '0' : cf.zero = true; break;
          default: finished = true; break;
          }

          if( finished )
            break;

          pos++;
        } //       while( (pos < len) )

      // get argument number
      if( pos < len )
        {
          // search for the $ digit
          unsigned int dp = (int)pos;

          while( dp < len && isdigit( format[dp] ) )
            dp++;

          if( dp < len && format[dp] == '$' )
            {
              use_par = skip_atoi( format, pos, pos ) - 1;
              pos = dp + 1;
            }
        }

      // get field with
      if( pos < len )
        {
          if( isdigit( format[pos] ) )
            cf.width = skip_atoi( format, pos, pos );
          else if( format[pos] == '*' )
            {
              pos++;

              // search for the $ digit
              unsigned int dp = (int)pos;

              while( dp < len && isdigit( format[dp] ) )
                dp++;

              if( dp < len && format[dp] == '$' )
                {
                  cf.width = get_int_arg( skip_atoi( format, pos, pos ) - 1 );
                  // skip $ sign
                  pos++;
                }
              else
                {
                  cf.width = get_int_arg( par );

                  if( use_par == par )
                    use_par++;

                  par++;
                }

              if( cf.width < 0 )
                {
                  cf.width *= -1;
                  cf.adjust = CFormat::LEFT;
                }
            }
        }

      // precision
      if( pos < len )
        {
          if( format[pos] == '.' )
            {
              pos++;
              if( !(pos < len) )
                return;

              had_precision = true;

              if( isdigit( format[pos] ) )
                cf.precision = skip_atoi( format, pos, pos );
              else if( format[pos] == '*' )
                {
                  pos++;


                  // search for the $ digit
                  unsigned int dp = (int)pos;

                  while( dp < len && isdigit( format[dp] ) )
                    dp++;

                  if( dp < len && format[dp] == '$' )
                    {
                      cf.precision = get_int_arg( skip_atoi( format, pos, pos ) - 1 );
                      // skip $ sign
                      pos++;
                    }
                  else
                    {
                      cf.precision = get_int_arg( par );

                      if( use_par == par )
                        use_par++;

                      par++;
                    }

                  if( cf.precision == 0)
                    cf.precision_explicit = true;

                  if( cf.precision < 0 )
                    cf.precision = 0;
                }
              else
                cf.precision = 0;
            }

        }

      // lenght modifier
      /*
     they will be ignored
     cause we know the types of the parameter
       */
      if( (pos < len) )
        {
          bool hh = false;
          bool ll = false;
          bool found = false;

          switch( format[pos] )
          {
          case 'h': hh = true; found = true; break;
          case 'l': ll = true; found = true; break;
          case 'L':
          case 'q':
          case 'j':
          case 'z':
          case 't': found = true; break;
          default: break;
          }

          if(found )
            {
              pos++;

              if( pos < len )
                {
                  if( hh == true )
                    {
                      if( format[pos] == 'h' )
                        pos++;
                    }
                  else if( ll == true )
                    {
                      if( format[pos] == 'l' )
                        pos++;
                    }
                } // if
            } // found
        }

      // conversion specifier

      if( pos < len )
        {
          bool invalid = false;
          switch( format[pos] )
          {
          case 'd':
          case 'u':
          case 'i':
            cf.numerical_representation = true;
            cf.base = CFormat::DEC;
            if( cf.zero && (cf.adjust != CFormat::LEFT) )
              cf.internal = true;
            break;

          case 'X': cf.setupper = true;
			/* Fallthrough */
          case 'x':
            cf.numerical_representation = true;
            cf.base = CFormat::HEX;
            if( cf.special )
              cf.showbase = true;
            break;

          case 'o':
            cf.numerical_representation = true;
            cf.base = CFormat::OCT;
            if( cf.special )
              cf.showbase = true;
            break;


          case 'E':
            cf.setupper = true;
			/* Fallthrough */

          case 'e':
            if( cf.special )
              cf.sign = true;
            cf.floating = CFormat::SCIENTIFIC;
            break;

          case 'F': // not supported
          case 'f':
            if( cf.special )
              cf.sign = true;
            cf.floating = CFormat::FIXED;
            break;

          case 's':
            if( cf.zero )
              cf.zero = false;
            break;


          case 'p':
            cf.base = CFormat::HEX;
            cf.showbase = true;
            break;

            // unsupported modifiers


          case 'G':
          case 'g':

          case 'A':
          case 'a':
            break;

          case 'c':
            cf.character_representation = true;
            break;

          case 'C':
          case 'S':
          case 'P':
          case 'n': break;

          default: invalid = true;
          }

          if( !invalid )
            cf.valid = true;
        }

      if( cf.valid )
        {
    	  string_t str;
          int upar = par;

          if( use_par != par )
            upar = use_par;

          if( cf.base == CFormat::HEX && had_precision && cf.special )
            {
              CFormat f2;
              f2.base = cf.base;
              string_t ss = use_arg( upar, f2 );
              cf.strlength = (int)ss.size();
              //        printf( "str: %s\n", s.c_str() );
            }

          str = use_arg( upar, cf );

          bool is_string = false;
          std::visit( [&is_string]( auto & real_arg ) {
        	  if( real_arg.isString() ) {
        		  is_string = true;
        	  }
          },  args[upar] );

          // std::cout << "had_precision: " << had_precision << " is_string: " << is_string << std::endl;

          // cut string
          if( had_precision && is_string )
            str = str.substr( 0, cf.precision );

          // cut null bytes out of the string
          // can happen when std::string.resize() is called
          // eg: std::string foo="foo";
          //     foo.resize(4);
          //     std::cout << (foo + "bar").c_str();
          //     will result in only the string "foo"
          //     we avoid this by cutting zeor bytes out

          for( std::string::size_type p = 0; p < str.size(); p++ )
            {
              if( str[p] ==  '\0' )
                {
                  str = str.substr( 0, p );
                  break;
                }
            }

          s += str;

          if( use_par == par )
            par++;
        }
      else
        {
          // copy the invalid format string
          for( std::string::size_type  i = start;  i<= pos; i++ )
            if( i < len )
              s += format[i];
        }

      pos++;

    } // while

  if( pos < len )
    {
      s += substitude( format.substr(pos), "%%", "%" );
    }
}


} // namespace Tools::StaticFormat
