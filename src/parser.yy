%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {MC}
%define parser_class_name {MC_Parser}

%code requires{
   namespace MC {
      class MCC;
      class MC_Scanner;
      class ArgumentsAST;
      class ArrayIdentifierAST;
      class AssignmentStmtAST;
      class AST;
      class BinaryOpAST;
      class BoolLiteralAST;
      class CallExprAST;
      class CompoundStmtAST;
      class DeclarationStmtAST;
      class ExpressionAST;
      class ExpressionStmtAST;
      class FloatLiteralAST;
      class FunctionAST;
      class IdentifierAST;
      class IfStmtAST;
      class IntLiteralAST;
      class LiteralAST;
      class ParametersAST;
      class ProgramAST;
      class ReturnStmtAST;
      class StmtAST;
      class StmtListAST;
      class StringLiteralAST;
      class UnaryOpAST;
      class WhileStmtAST;
   }
   #include<memory>



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
%parse-param { MCC  &mcc  }

%code{
  #include <cstdlib>
  #include <iostream>
  #include <fstream>

  #include "mcc/mcc.hpp"

  #include "include/astAll.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert


%start program
%token ADD SUB MUL DIV LES GRE LEQ GEQ EQU NEQ AND ORR ASS
%token NEG
%token OPENPARENTH CLOSEPARENTH OPENSQUAREPARENTH CLOSESQUAREPARENTH OPENCURLPARENTH CLOSECURLPARENTH
%token COMMA SEMICOLON
%token <std::string> IDENTIFIER
%token IFF ELS
%token WHL
%token RET
%token INT_TYPE FLOAT_TYPE BOOL_TYPE STRING_TYPE VOID_TYPE
%token <long> INT_LITERAL
%token <double> FLOAT_LITERAL
%token <bool> BOOL_LITERAL
%token <std::string> STRING_LITERAL
%token EOL
%token               END    0     "end of file"


%precedence CLOSEPARENTH
%precedence ELS


%left AND ORR
%left LES GRE LEQ GEQ EQU NEQ NEG
%left ADD SUB
%left MUL DIV
%precedence NEGPRE     /* negation--unary minus */




%type <std::shared_ptr<ProgramAST>> program
%type <std::shared_ptr<FunctionAST>> functionDef
%type <std::string> type
%type <std::shared_ptr<StmtListAST>> statementList
%type <std::shared_ptr<StmtAST>> statement
%type <std::shared_ptr<IfStmtAST>> ifStmt
%type <std::shared_ptr<WhileStmtAST>> whileStmt
%type <std::shared_ptr<ReturnStmtAST>> returnStmt
%type <std::shared_ptr<DeclarationStmtAST>> declaration
%type <std::shared_ptr<AssignmentStmtAST>> assignment
%type <std::shared_ptr<CompoundStmtAST>> compoundStmt
%type <std::shared_ptr<ExpressionAST>> expression
%type <std::shared_ptr<LiteralAST>> literal
%type <std::shared_ptr<CallExprAST>> callExpr
%type <std::shared_ptr<ArgumentsAST>> arguments
%type <std::shared_ptr<ParametersAST>> parameters



%locations

%%

type : INT_TYPE                                                                    { $$ = "int"; }
     | FLOAT_TYPE                                                                  { $$ = "float"; }
     | BOOL_TYPE                                                                   { $$ = "bool"; }
     | STRING_TYPE                                                                 { $$ = "string"; }
     ;

literal : INT_LITERAL                                                              { $$ = std::make_shared<IntLiteralAST>($1, @1.begin.line); }
        | FLOAT_LITERAL                                                            { $$ = std::make_shared<FloatLiteralAST>($1, @1.begin.line); }
        | STRING_LITERAL                                                           { $$ = std::make_shared<StringLiteralAST>($1, @1.begin.line); }
        | BOOL_LITERAL                                                             { $$ = std::make_shared<BoolLiteralAST>($1, @1.begin.line); }
        ;

declaration : type IDENTIFIER                                                      { $$ = std::make_shared<DeclarationStmtAST>($1, std::make_shared<IdentifierAST>($2, @2.begin.line), @2.begin.line); }
            | type OPENSQUAREPARENTH INT_LITERAL CLOSESQUAREPARENTH IDENTIFIER     { $$ = std::make_shared<DeclarationStmtAST>($1, std::make_shared<IdentifierAST>($5, @5.begin.line), std::make_shared<IntLiteralAST>($3, @3.begin.line), @5.begin.line); }
            ;

assignment : IDENTIFIER ASS expression                                             { $$ = std::make_shared<AssignmentStmtAST>(std::make_shared<IdentifierAST>($1, @1.begin.line), $3, @1.begin.line); }
           | IDENTIFIER OPENSQUAREPARENTH expression CLOSESQUAREPARENTH ASS expression   { $$ = std::make_shared<AssignmentStmtAST>(std::make_shared<IdentifierAST>($1, @1.begin.line), $3, $6, @1.begin.line); }
           ;


expression : literal                                                               { $$ = $1; }
           | IDENTIFIER                                                            { $$ = std::make_shared<IdentifierAST>($1, @1.begin.line); }
           | IDENTIFIER OPENSQUAREPARENTH expression CLOSESQUAREPARENTH            { $$ = std::make_shared<ArrayIdentifierAST>(std::make_shared<IdentifierAST>($1, @1.begin.line), $3, @1.begin.line); }
           | callExpr                                                              { $$ = $1; }
           | SUB expression %prec NEGPRE                                           { $$ = std::make_shared<UnaryOpAST>("-", $2, @1.begin.line); }
           | NEG expression                                                        { $$ = std::make_shared<UnaryOpAST>("!", $2, @1.begin.line); }
           | expression ADD expression                                             { $$ = std::make_shared<BinaryOpAST>("+", $1, $3, @2.begin.line); }
           | expression SUB expression                                             { $$ = std::make_shared<BinaryOpAST>("-", $1, $3, @2.begin.line); }
           | expression MUL expression                                             { $$ = std::make_shared<BinaryOpAST>("*", $1, $3, @2.begin.line); }
           | expression DIV expression                                             { $$ = std::make_shared<BinaryOpAST>("/", $1, $3, @2.begin.line); }
           | expression LES expression                                             { $$ = std::make_shared<BinaryOpAST>("<", $1, $3, @2.begin.line); }
           | expression GRE expression                                             { $$ = std::make_shared<BinaryOpAST>(">", $1, $3, @2.begin.line); }
           | expression LEQ expression                                             { $$ = std::make_shared<BinaryOpAST>("<=", $1, $3, @2.begin.line); }
           | expression GEQ expression                                             { $$ = std::make_shared<BinaryOpAST>(">=", $1, $3, @2.begin.line); }
           | expression EQU expression                                             { $$ = std::make_shared<BinaryOpAST>("==", $1, $3, @2.begin.line); }
           | expression NEQ expression                                             { $$ = std::make_shared<BinaryOpAST>("!=", $1, $3, @2.begin.line); }
           | expression AND expression                                             { $$ = std::make_shared<BinaryOpAST>("&&", $1, $3, @2.begin.line); }
           | expression ORR expression                                             { $$ = std::make_shared<BinaryOpAST>("||", $1, $3, @2.begin.line); }
           | OPENPARENTH expression CLOSEPARENTH                                   { $$ = $2; }
           ;

statement : ifStmt                                                                 { $$ = $1; }
          | whileStmt                                                              { $$ = $1; }
          | returnStmt  SEMICOLON                                                  { $$ = $1; }
          | declaration SEMICOLON                                                  { $$ = $1; }
          | assignment SEMICOLON                                                   { $$ = $1; }
          | expression SEMICOLON                                                   { $$ = std::make_shared<ExpressionStmtAST>($1, @2.begin.line); }
          | compoundStmt {}                                                        { $$ = $1; }
          ;

ifStmt : IFF OPENPARENTH expression CLOSEPARENTH statement                         { $$ = std::make_shared<IfStmtAST>($3, $5, @1.begin.line); }
       | IFF OPENPARENTH expression CLOSEPARENTH statement ELS statement           { $$ = std::make_shared<IfStmtAST>($3, $5, $7, @1.begin.line); }
       ;

whileStmt : WHL OPENPARENTH expression CLOSEPARENTH statement                      { $$ = std::make_shared<WhileStmtAST>($3, $5, @1.begin.line); }

returnStmt : RET expression                                                        { $$ = std::make_shared<ReturnStmtAST>($2, @1.begin.line); }
           | RET                                                                   { $$ = std::make_shared<ReturnStmtAST>(@1.begin.line); }
           ;

compoundStmt : OPENCURLPARENTH statementList CLOSECURLPARENTH                      { $$ = std::make_shared<CompoundStmtAST>($2, @1.begin.line); }
             ;

statementList : %empty                                                             { $$ = std::make_shared<StmtListAST>(); }
              | statementList statement                                            { $1->addStatement($2) ; $$ = $1; }
              ;

functionDef : type IDENTIFIER OPENPARENTH parameters CLOSEPARENTH compoundStmt      { $$ = std::make_shared<FunctionAST>($1, std::make_shared<IdentifierAST>($2, @2.begin.line), $6, $4, @2.begin.line); }
            | VOID_TYPE IDENTIFIER OPENPARENTH parameters CLOSEPARENTH compoundStmt { $$ = std::make_shared<FunctionAST>("void", std::make_shared<IdentifierAST>($2, @2.begin.line), $6, $4, @2.begin.line); }
            | type IDENTIFIER OPENPARENTH CLOSEPARENTH compoundStmt                 { $$ = std::make_shared<FunctionAST>($1, std::make_shared<IdentifierAST>($2, @2.begin.line), $5, @2.begin.line); }
            | VOID_TYPE IDENTIFIER OPENPARENTH CLOSEPARENTH compoundStmt            { $$ = std::make_shared<FunctionAST>("void", std::make_shared<IdentifierAST>($2, @2.begin.line), $5, @2.begin.line); }
            ;

parameters : parameters COMMA declaration                                           { $1->addParameter($3); $$ = $1; }
           | declaration                                                            { $$ = std::make_shared<ParametersAST>(); $$->addParameter($1); }
           ;

callExpr : IDENTIFIER OPENPARENTH arguments CLOSEPARENTH                           { $$ = std::make_shared<CallExprAST>(std::make_shared<IdentifierAST>($1, @1.begin.line),$3, @1.begin.line); }
         | IDENTIFIER OPENPARENTH CLOSEPARENTH                                     { $$ = std::make_shared<CallExprAST>(std::make_shared<IdentifierAST>($1, @1.begin.line), @1.begin.line); }
         ;

arguments : arguments COMMA expression                                             { $1->addArgument($3); $$ = $1; }
          | expression                                                             { $$ = std::make_shared<ArgumentsAST>(); $$->addArgument($1); }
          ;



program : %empty                                                                    { $$ = std::make_shared<ProgramAST>(); mcc.ast = $$;}
        | program functionDef                                                       { $1->addFunction($2); $$=$1; }
        ;


%%

void MC::MC_Parser::error( const location_type &l, const std::string &err_message ){
  std::cerr << "Error: " << err_message << " at " << l << "\n";
}
