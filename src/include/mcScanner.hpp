#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "../builddir/mcc@sha/location.hh"
#include "../builddir/mcc@sha/parser.tab.hh"

namespace MC{

class MC_Scanner : public yyFlexLexer{
public:

   MC_Scanner(std::istream *in) : yyFlexLexer(in){};
   virtual ~MC_Scanner() {};

   using FlexLexer::yylex;  /* get rid of override virtual function warning */

   virtual int yylex( MC::MC_Parser::semantic_type * const lval,
              MC::MC_Parser::location_type *location );

private:
   MC::MC_Parser::semantic_type *yylval = nullptr;  /* yyval ptr */
   //MC::MC_Parser::location_type *loc = nullptr; /* location ptr */
};

} /* end namespace MC */

#endif /* END __MCSCANNER_HPP__ */
