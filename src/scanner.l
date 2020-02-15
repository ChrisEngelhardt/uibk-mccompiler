
%{
    #include <memory>
    #include <string>
    #include <stdlib.h>

    #include "include/mcScanner.hpp"
    
    #undef  YY_DECL
    #define YY_DECL int MC::MC_Scanner::yylex( MC::MC_Parser::semantic_type * const lval, MC::MC_Parser::location_type *loc )

    /* typedef to make the returns for the tokens shorter */
    using token = MC::MC_Parser::token;

    /* define yyterminate as this instead of NULL */
    #define yyterminate() return( token::END )

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H

    /* update location on matching */
    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);



    #define YY_TXT                  std::string(yytext, yyleng)
    #define YY_FLOAT                std::atof(yytext)
    #define YY_INT                  std::atol(yytext)


    // utility macros to simplify the actions
    #define YIELD_TOKEN(tok, val, type)                 \
                    yylval->build<type>(val);           \
                    return tok;

    #define INT_TOKEN()     YIELD_TOKEN(token::INT_LITERAL, YY_INT, long)
    #define FLOAT_TOKEN()   YIELD_TOKEN(token::FLOAT_LITERAL, YY_FLOAT, double)
    #define STRING_TOKEN()  YIELD_TOKEN(token::STRING_LITERAL, YY_TXT, std::string)
    #define IDENT_TOKEN()   YIELD_TOKEN(token::IDENTIFIER, YY_TXT, std::string)


    #define TOKEN(tok)         return tok;
%}

%option noyywrap nodefault yylineno
%option debug yyclass="MC::MC_Scanner" c++
%x COMMENT

DIGIT [0-9]

IDENT [a-zA-Z_][a-zA-Z0-9_]*

%%
%{  /** Code executed at the beginning of yylex **/
    yylval = lval;
%}

"+"     		      		TOKEN(token::ADD)
"-"     		      	  TOKEN(token::SUB)
"*"     		      		TOKEN(token::MUL)
"/"     		      		TOKEN(token::DIV)
"<"     		      		TOKEN(token::LES)
">"     		      		TOKEN(token::GRE)
"<="     	      			TOKEN(token::LEQ)
">="     	      			TOKEN(token::GEQ)
"=="     	      			TOKEN(token::EQU)
"!="     	      			TOKEN(token::NEQ)
"&&"     	      			TOKEN(token::AND)
"||"     	      			TOKEN(token::ORR)
"!"     		      		TOKEN(token::NEG)
"("							      TOKEN(token::OPENPARENTH)
")"							      TOKEN(token::CLOSEPARENTH)
"{"							      TOKEN(token::OPENCURLPARENTH)
"}"							      TOKEN(token::CLOSECURLPARENTH)
"["							      TOKEN(token::OPENSQUAREPARENTH)
"]"							      TOKEN(token::CLOSESQUAREPARENTH)
","							      TOKEN(token::COMMA)
";"							      TOKEN(token::SEMICOLON)
"="     				      TOKEN(token::ASS)


"if"                  TOKEN(token::IFF)
"else"                TOKEN(token::ELS)
"while"               TOKEN(token::WHL)
"return"              TOKEN(token::RET)

"int"                 TOKEN(token::INT_TYPE)
"float"               TOKEN(token::FLOAT_TYPE)
"string"              TOKEN(token::STRING_TYPE)
"bool"                TOKEN(token::BOOL_TYPE)
"void"                TOKEN(token::VOID_TYPE)

"/*"                  { BEGIN(COMMENT); }
<COMMENT>"*/"         { BEGIN(INITIAL); }
<COMMENT>\n           { loc->lines(); }
<COMMENT>.            { }

"true"                { yylval->build<bool>(true); return token::BOOL_LITERAL; }

"false"               { yylval->build<bool>(false); return token::BOOL_LITERAL; }

{IDENT}               IDENT_TOKEN()

{DIGIT}+              INT_TOKEN()

{DIGIT}+\.{DIGIT}+    FLOAT_TOKEN()

\"[^\"]*\"            STRING_TOKEN()

[ \t]                 { }
\n     					      { loc->lines(); }
.   						      { }


%%
