# Overview

## Front-end
- Validate a given input using syntactic and semantic checks
- **Syntactic** checking is done by the **parser** which generates an abstract syntax tree (AST) (used for semantic checking)
- AST is translated to the compiler's intermediate representation (IR) and passed to the core.

## core 
- Provides infrastructure for running analyses and transformations on the IR. (used for optimisation)
- Additional data structures, like the control flow graph (CFG), are utilised for this phase.

## Back-end 
- translates the platform independent IR code to platform dependent assembly code.
- assembler converts this code to object code, which is finally crafted into an executable by the linker.
- **IR Code -> assembly code -> object code -> executable (linker)**

---

## Links
https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html

---

# Flex

## What is Flex
Tool that generates a scanner that divides the input into tokens. The output of flex is a C programm.

## Basics programm
Flex program consists of three sections, separated by %% lines. 
- First section contains declarations and option settings
- Second section is a list of patterns and actions
- Third section is C code that is copied to the generated scanner

## Generate
1. flex _programmName_
2. gcc lex.yy.c -lfl -o _executableName_
3. ./_executableName_ _INPUT_ ^D

**(Important Notes: On mac linking flex with fl seems not to work, use -ll instead)**
##Example Word count

```c
/* just like Unix wc */
%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%

[a-zA-Z]+  { words++; chars += strlen(yytext); }
\n         { chars++; lines++; }
.          { chars++; }

%%

main(int argc, char **argv)
{
  yylex();
  printf("%8d%8d%8d\n", lines, words, chars);
}
```



# Bison

## What is Bison
- Bisons job is to figure out the relationship among the input tokens
- it generates an syntax tree for further processing
- to define the parser, BNF will be used (slightly modified from the definition)

## Example
Simple grammer for additon and multiplication

```c
<exp> ::= <factor> 
      | <exp> + <factor>
<factor> ::= NUMBER
      | <factor> * NUMBER
```

## Basics programm
- Have the same three-part structure as flex
- The declarations here include C code to be copied to the beginning of the generated C parser, again enclosed in %{ and %}
- Following are %token token declarations, telling bison the names of the symbols in the parser that are tokens  (convention, tokens have uppercase names)
- Any symbols not declared as tokens have to appear on the left side of at least one rule in the program
- The second section contains the rules in simplified BNF
- Each symbol in a bison rule has a value; the value of the target symbol

## Good to know
- Whenever a grammar has multiple levels of precedence where one kind of operator binds "tighter" than another, the parser will need a level of rule for each level
- It will not parse an ambiguous grammar


## Example of a small calculator

```c
/* simplest version of calculator */
%{
#include <stdio.h>
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%

calclist: /* nothing */                       matches at beginning of input
 | calclist exp EOL { printf("= %d\n", $2); } EOL is end of an expression
 ;

exp: factor       default $$ = $1 
 | exp ADD factor { $$ = $1 + $3; }
 | exp SUB factor { $$ = $1 - $3; }
 ;

factor: term       default $$ = $1 
 | factor MUL term { $$ = $1 * $3; }
 | factor DIV term { $$ = $1 / $3; }
 ;

term: NUMBER  default $$ = $1 
 | ABS term   { $$ = $2 >= 0? $2 : - $2; }
;
%%
main(int argc, char **argv)
{
  yyparse();
}

yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
}
```

[Archive.zip](resources/5C32B1D8B65716E9F7727DC7178846F7.zip)

