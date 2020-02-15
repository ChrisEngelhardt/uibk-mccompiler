<http://www.jonathanbeard.io/tutorials/FlexBisonC++>

---

### Notes before getting started

 To compile the example located on [GitHub](https://github.com/jonathan-beard/simple_wc_example) you'll need a few things. First, you'll need the [Flex](http://flex.sourceforge.net/) utility. Some systems come with it pre-installed with developer or build tools, but you'll need to make sure that it is a relatively recent version (e.g., 2.5.37). One issue that might arise for Apple users is an incompatible version of Flex. The default installed version is 2.5.35 (Apple provided), however the header file that is included won't work with this example. One solution is changing the example, however that will make it incompatible with any recent version of Flex. A better solution is simply to upgrade Flex to a newer version. For more information on this issue for Apple users, [LMGTFY](http://lmgtfy.com/?q=FlexLexer.h+header+file+on+OS+X). 

### The Flex Scanner

 How the Flex scanner itself works is beyond the scope of this tutorial. There are plenty of references on how to get started with a scanner, especially in C. There are lots of other examples out there but I found that most require quite a bit of work to get going and are far from complete. I based the example on some other Flex/Bison examples that create something similar to the Unix word count utility (*wc*). The language I used differs slightly from *wc* in the following respects: words are only alpha characters, numbers are simply counted as characters and I count upper and lower case characters.

### The Flex Scanner Code

```c
%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "mc_scanner.hpp"
#undef  YY_DECL
#define YY_DECL int MC::MC_Scanner::yylex( MC::MC_Parser::semantic_type * const lval, MC::MC_Parser::location_type *location )

/* using "token" to make the returns for the tokens shorter to type */
using token = MC::MC_Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="MC::MC_Scanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

[a-z]       {
               return( token::LOWER );
            }

[A-Z]       {
               return( token::UPPER );
            }

[a-zA-Z]+   {
               /**
                * Section 10.1.5.1 of the 3.0.2 Bison Manual says the 
                * following should work:
                * yylval.build( yytext );
                * but it doesn't.
                * ref: http://goo.gl/KLn0w2
                */
               yylval->build< std::string >( yytext );
               return( token::WORD );
            }

\n          {
               /** Update line number **/
               loc->lines();
               return( token::NEWLINE );
            }

.           {
               return( token::CHAR );
            }
%%
```

A brief explanation of the scanner file

On line 3 the C++ string header file is included since we use it within this code. The scanner header file (line 6) is included, which we'll talk about next, extends yyFlexLexer found in FlexLexer.h. This is the scanner class itself. Next you'll see a using statement included simply to make the namespacing a bit shorter to type when returning tokens. In previous versions of this tutorial I'd added a macro to create actual string objects from the char string yytext. Bison now defines a template function to cast/create the proper objects for you, so this version of the tutorial uses this more modern construct. If you're interested in the details, see the Bison documenation (direct link). In the past you would manually have to define your own union. Now that is largely done for you based on the token types which is much nicer. On line 7 you'll want to notice that the yylex function that is defined in the mc\_scanner.hpp header file is declared as a \#define with YY\_DECL. This function signature must match that one (minus the virtual or other class header keywords). This is extremely important, otherwise you will hit this section within the generated code, and get the default yylex() function (discussed in detail later).

On line 14 you'll notice that I've defined terminate, I would like it to be a token type instead of NULL so we define it before the code below is read (from the generated file). This way yyterminate() is already defined by the time the compiler reaches this point in the generated code so our version is in the compiled code and not the default one.

```c
/* No semi-colon after return; correct usage is to write "yyterminate();" -
 * we don't want an extra ';' after the "return" because that will cause
 * some compilers to complain about unreachable statements.
 */
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif
```

Next you'll see that there are several options selected. Most of these are self explanatory or are explained within the Flex documentation, however the one's you don't want to miss are the nodefault, yyclass=, noyywrap and c++ options. The yyclass option indicates what the scanner class is actually called. This is the same class that is imported on line 3.

**The Scanner Class Definition**
--------------------------------

```c
ifndef MCSCANNER_HPP

define MCSCANNER_HPP 1

if ! defined(yyFlexLexerOnce)

include <FlexLexer.h>

endif

include "mc_parser.tab.hh"

include "location.hh"

namespace MC{

class MC_Scanner : public yyFlexLexer{
public:

MC_Scanner(std::istream *in) : yyFlexLexer(in)
{
loc = new MC::MC_Parser::location_type();
};

//get rid of override virtual function warning
using FlexLexer::yylex;

virtual
int yylex( MC::MC_Parser::semantic_type * const lval,
MC::MC_Parser::location_type *location );
// YY_DECL defined in mc_lexer.l
// Method body created by flex in mc_lexer.yy.cc

private:
/* yyval ptr */
MC::MC_Parser::semantic_type yylval = nullptr;
/ location ptr */
MC::MC_Parser::location_type *loc = nullptr;
};

} /* end namespace MC */

endif /* END MCSCANNER_HPP */

```

Line 5 simply includes the FlexLexer.h class that defines yyFlexLexer. We then include the bison generated header file which includes the token definitions. The constructor is relatively straight forward, we simply call the yyFlexLexer constructor then we initialize the private yylval pointer to nullptr. The only function that we need to define in this simple example we have yylex which we defined as YY\_DECL earlier. One thing to make note of is the fact that yylex() is now declared as virtual, and can throw an override error when defining your own function. To get around this, we've added a using statement to ensure the compiler knows that we meant to define a new yylex on line 24\. Just to show why we undefined YY\_DECL here's a code snippet from the generated [lex.yy.cc](http://lex.yy.cc):

```c
#ifndef YY_DECL
#define YY_DECL_IS_OURS 1
/* %if-c-only Standard (non-C++) definition */
/* %endif */
/* %if-c++-only C++ definition */
#define YY_DECL int yyFlexLexer::yylex()
/* %endif */
#endif /* !YY_DECL */
```

By defining YY\_DECL, we get rid of the native one. That pretty much concludes the scanner portion, on to the parser stuff.

The Bison C++ Parser File
-------------------------

```c
%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {MC}
%define parser_class_name {MC_Parser}

%code requires{
   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { MC_Scanner  &scanner  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "mc_driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token               UPPER
%token               LOWER
%token <std::string> WORD
%token               NEWLINE
%token               CHAR

%locations

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( $1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;

%%


void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
```

Exactly how to write a language, and express it such that the parser can parse it is definitely beyond the scope of this tutorial, there are plenty of books on how to do this. Here is just a simple description of how to define the C++ parser. The first line declares that we want to use the lalr1 skeleton file (if you want to learn what types of skeletons are available, the documentation does a fairly good job going through them). We then include the required version of Bison (for this example version 3.0+, however you can download an example that works with version 2.5 through 2.7 here: link). There's a bit of new syntax which is the reason for the version differentiation. The debug option is set on line 3. The namespace that we want this parser to use is defined on line 5 along with the parser class on line 6 (Note: its usually a good idea to have a unique namespace and a parser name so when you have multiple parsers they can be kept very distinct). On line 8 the classes that are used within the parser are defined, think of this as a forward declaration. Lines 14 through 21 are included because of a bug (perhaps feature) that removes this definition when %locations isn't used. Lines 25 and 26 are important as they define what will be given to the parser when its instantiated and upon calls to yylex. There's quite a few more options that can be given to Bison, some of those for version 3.0 are listed here (Bison Docs). Here's a snippet from the generated parser header to show our parser constructor mc_parser.tab.hh:

```c
    /// Build a parser object.
    MC_Parser (MC_Scanner  &scanner_yyarg, MC_Driver  &driver_yyarg);
```

Reference to both the passed in driver and scanner are kept as private members of the parser class. Within the code section we have all the rest of the information that our code will need to compile, include the requisite C++ headers, the driver class that we'll get to shortly. We also define a static yylex function that'll be called within the bison parse function that takes the parameters that were defined on lines 25-26\. This function will call the scanner's yylex function, any other behavior need can be defined here. Next we have the simple language which differs from the way the actual wc functions in the manner mentioned in the intro. Last the error function and the static yylex function is defined.

The Driver Header File
----------------------

```c
#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "mc_scanner.hpp"
#include "mc_parser.tab.hh"

namespace MC{

class MC_Driver{
public:
   MC_Driver() = default;

   virtual ~MC_Driver();
   
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse( const char *filename );
   /** 
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
   void parse( std::istream &iss );

   void add_upper();
   void add_lower();
   void add_word( const std::string &word );
   void add_newline();
   void add_char();

   std::ostream& print(std::ostream &stream);
private:

   void parse_helper( std::istream &stream );

   std::size_t  chars      = 0;
   std::size_t  words      = 0;
   std::size_t  lines      = 0;
   std::size_t  uppercase  = 0;
   std::size_t  lowercase  = 0;
   MC::MC_Parser  *parser  = nullptr;
   MC::MC_Scanner *scanner = nullptr;
   
   /** define some pretty colors **/
   const std::string red   = "\033[1;31m";
   const std::string blue  = "\033[1;36m";
   const std::string norm  = "\033[0m";
};

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */
```

One thing you'll notice is that there are two parse functions. One is to take input from a file, the other for input from a C++ stream. The main function defines paths to take input from a pipe and also via file. This is implemented via these parser functions. The cool thing about having a stream input is that you can also use this to parse command line input if you'd like.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**The Driver Implementation**
-----------------------------

```c
#include <cctype>
#include <fstream>
#include <cassert>

#include "mc_driver.hpp"

MC::MC_Driver::~MC_Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void 
MC::MC_Driver::parse( const char * const filename )
{
   /**
    * Remember, if you want to have checks in release mode
    * then this needs to be an if statement 
    */
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}

void
MC::MC_Driver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream ); 
   return;
}


void 
MC::MC_Driver::parse_helper( std::istream &stream )
{
   
   delete(scanner);
   try
   {
      scanner = new MC::MC_Scanner( &stream );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   delete(parser); 
   try
   {
      parser = new MC::MC_Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
   }
   return;
}

void 
MC::MC_Driver::add_upper()
{ 
   uppercase++; 
   chars++; 
   words++; 
}

void 
MC::MC_Driver::add_lower()
{ 
   lowercase++; 
   chars++; 
   words++; 
}

void 
MC::MC_Driver::add_word( const std::string &word )
{
   words++; 
   chars += word.length();
   for(const char &c : word ){
      if( islower( c ) )
      { 
         lowercase++; 
      }
      else if ( isupper( c ) ) 
      { 
         uppercase++; 
      }
   }
}

void 
MC::MC_Driver::add_newline()
{ 
   lines++; 
   chars++; 
}

void 
MC::MC_Driver::add_char()
{ 
   chars++; 
}


std::ostream& 
MC::MC_Driver::print( std::ostream &stream )
{
   /** NOTE: Colors are defined as class variables w/in MC_Driver **/
   stream << red  << "Results: " << norm << "\n";
   stream << blue << "Uppercase: " << norm << uppercase << "\n";
   stream << blue << "Lowercase: " << norm << lowercase << "\n";
   stream << blue << "Lines: " << norm << lines << "\n";
   stream << blue << "Words: " << norm << words << "\n";
   stream << blue << "Characters: " << norm << chars << "\n";
   return(stream);
}
```



All thats left is to define a main class to instantiate everything and a Makefile to run the compilation from the command line (invoked by typing make in the source code directory). Our main class is perhaps a bit more complex than it has to be, however I wanted to include the stream example and the file example all in one, so there is extra code to parse the two flags I added to make this happen. It should be relatively self explanatory for anyone familiar with parsing the argv array.

**The Main Function**

```c
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "mc_driver.hpp"

int 
main( const int argc, const char **argv )
{
   /** check for the right # of arguments **/
   if( argc == 2 )
   {
      /** instantiate driver object **/
      MC::MC_Driver driver;
      /** example for piping input from terminal, i.e., using cat **/ 
      if( std::strncmp( argv[ 1 ], "-o", 2 ) == 0 )
      {
         driver.parse( std::cin );
      }
      /** simple help menu **/
      else if( std::strncmp( argv[ 1 ], "-h", 2 ) == 0 )
      {
         std::cout << "use -o for pipe to std::cin\n";
         std::cout << "just give a filename to count from a file\n";
         std::cout << "use -h to get this menu\n";
         return( EXIT_SUCCESS );
      }
      /** example reading input from a file **/
      else
      {
         /** assume file, prod code, use stat to check **/
         driver.parse( argv[1] );
      }
      driver.print( std::cout ) << "\n";
   }
   else
   {
      /** exit with failure condition **/
      return ( EXIT_FAILURE );
   }
   return( EXIT_SUCCESS );
}
```

**The Makefile**

```c
CC    ?= clang
CXX   ?= clang++

EXE = my_wc

CDEBUG = -g -Wall

CXXDEBUG = -g -Wall

CSTD = -std=c99
CXXSTD = -std=c++11

CFLAGS = -Wno-deprecated-register -O0  $(CDEBUG) $(CSTD) 
CXXFLAGS = -Wno-deprecated-register -O0  $(CXXDEBUG) $(CXXSTD)


CPPOBJ = main mc_driver
SOBJ =  parser lexer

FILES = $(addsuffix .cpp, $(CPPOBJ))

OBJS  = $(addsuffix .o, $(CPPOBJ))

CLEANLIST =  $(addsuffix .o, $(OBJ)) $(OBJS) \
				 mc_parser.tab.cc mc_parser.tab.hh \
				 location.hh position.hh \
			    stack.hh mc_parser.output parser.o \
				 lexer.o mc_lexer.yy.cc $(EXE)\

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJ)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) parser.o lexer.o $(LIBS)


parser: mc_parser.yy
	bison -d -v mc_parser.yy
	$(CXX) $(CXXFLAGS) -c -o parser.o mc_parser.tab.cc

lexer: mc_lexer.l
	flex --outfile=mc_lexer.yy.cc  $<
	$(CXX)  $(CXXFLAGS) -c mc_lexer.yy.cc -o lexer.o

.PHONY: test
test:
	cd test && ./test0.pl

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
```

Be aware that some compilers still use the c++0x flag for standard in lieu or the c++11 flag. If you are not using clang as your compiler you should change the appropriate lines within the Makefile so that make will know which compiler to call. The full code is available for download from my git-hub page here: https://github.com/jonathan-beard/simple_wc_example.git or Zip Download . If you find some errors, feel free to hop on GitHub and correct them!! I'll update the pieces here accordingly. Thanks to all who have contributed to making this as up to date as possible.