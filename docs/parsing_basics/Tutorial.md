<h2>Chapter&nbsp;1.&nbsp;Introducing Flex and Bison</h2><p>Flex and Bison are tools for building programs that handle
    structured input. They were originally tools for building compilers, but
    they have proven to be useful in many other areas. In this first chapter,
    we’ll start by looking at a little (but not too much) of the theory behind
    them, and then we’ll dive into some examples of their use.</p><div><h2>Lexical Analysis and Parsing</h2><p>The earliest compilers back in the 1950s used utterly ad
      hoc techniques to analyze the syntax of the source code of programs they
      were compiling. During the 1960s, the field got a lot of academic
      attention, and by the early 1970s, syntax analysis was a well-understood
      field.</p><p>One of the key insights was to break the job into two parts:
      <span><em>lexical analysis</em></span> (also called
      <span><em>lexing</em></span> or <span><em>scanning</em></span>) and
      <span><em>syntax analysis</em></span> (or
      <span><em>parsing</em></span>).</p><p>Roughly speaking, scanning divides the input into
      meaningful chunks, called <span><em>tokens</em></span>, and parsing
      figures out how the tokens relate to each other. For example, consider
      this snippet of C code:</p><div style="overflow: auto;"><pre>alpha = beta + gamma ;</pre></div><p>A scanner divides this into the tokens <code>alpha</code>, <code>equal sign</code>, <code>beta</code>, <code>plus sign</code>, <code>gamma</code>, and <code>semicolon</code>. Then the parser determines that
      <code>beta + gamma</code> is an expression, and
      that the expression is assigned to <code>alpha</code>.</p><div><div>Getting Flex and Bison</div><p>Most Linux and BSD systems come with flex and bison as
        part of the base system. If your system doesn’t have them, or has
        out-of-date versions, they’re both easy to install.</p><p>Flex is a Sourceforge project, at <a href="http://flex.sourceforge.net/">http://flex.sourceforge.net/</a>. The current version as of
        early 2009 was 2.5.35. Changes from version to version are usually
        minor, so it’s not essential to update your version if it’s close to
        .35, but some systems still ship with version 2.5.4 or 2.5.4a, which
        is more than a decade old.</p><p>Bison is available from <a href="http://www.gnu.org/software/bison/">http://www.gnu.org/software/bison/</a>. The current version
        as of early 2009 was 2.4.1. Bison is under fairly active development,
        so it’s worth getting an up-to-date version to see what’s new. Version
        2.4 added support for parsers in Java, for example. BSD users can
        generally install a current version of flex or bison using the ports
        collection. Linux users may be able to find current RPMs. If not, flex
        and bison both use the standard GNU build process, so to install them,
        download and unpack the current flex and bison tarballs from the web
        sites, run <code>./configure</code> and then
        <code>make</code> to build each, then become
        superuser and <code>make install</code> to
        install them.</p><p>Flex and bison both depend on the GNU m4 macroprocessor. Linux
        and BSD should all have m4, but in case they don’t, or they have an
        ancient version, the current GNU m4 is at <a href="http://www.gnu.org/software/m4/">http://www.gnu.org/software/m4/</a>.</p><p>For Windows users, both bison and flex are included in the
        Cygwin Linux emulation environment available at <a href="http://www.cygwin.com/">http://www.cygwin.com/</a>. You can use the C or C++ code
        they generate either with the Cygwin development tools or with native
        Windows development tools.</p></div></div><div><h2>Regular Expressions and Scanning</h2><p>Scanners generally work by looking for patterns of
      characters in the input. For example, in a C program, an integer
      constant is a string of one or more digits, a variable name is a letter
      followed by zero or more letters or digits, and the various operators
      are single characters or pairs of characters. A straightforward way to
      describe these patterns is <span><em>regular expressions</em></span>,
      often shortened to <span><em>regex</em></span> or
      <span><em>regexp</em></span>. These are the same kind of patterns that
      the editors ed and vi and the search program egrep use to describe text
      to search for. A flex program basically consists of a list of regexps
      with instructions about what to do when the input matches any of them,
      known as <span><em>actions</em></span>. A flex-generated scanner reads through its input,
      matching the input against all of the regexps and doing the appropriate
      action on each match. Flex translates all of the regexps into an
      efficient internal form that lets it match the input against all the
      patterns simultaneously, so it’s just as fast for 100 patterns as for
      one.<sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#ftn.id333485">1</a>]</sup></p><div><h3>Our First Flex Program</h3><p>Unix systems (by which I also mean Unix-ish systems
        including Linux and the BSDs) come with a word count program, which
        reads through a file and reports the number of lines, words, and
        characters in the file. Flex lets us write <code>wc</code> in a few dozen lines, shown in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#pgmwc">Example&nbsp;1-1</a>.</p><div><p>Example&nbsp;1-1.&nbsp;Word count fb1-1.l</p><div style="overflow: auto;"><pre>/* just like Unix wc */
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
}</pre></div></div><p>Much of this program should look familiar to C programmers,
        since most of it is C. A flex program consists of three sections,
        separated by <code>%%</code> lines. The first
        section contains declarations and option settings. The second section
        is a list of patterns and actions, and the third section is C code
        that is copied to the generated scanner, usually small routines
        related to the code in the actions.</p><p>In the declaration section, code inside of <code>%{</code> and <code>%}</code>
        is copied through verbatim near the beginning of the generated C
        source file. In this case it just sets up variables for lines, words,
        and characters.</p><p>In the second section, each pattern is at the beginning of a
        line, followed by the C code to execute when the pattern matches. The
        C code can be one statement or possibly a multiline block in braces,
        <code>{ }</code>. (Each pattern
        <span><em>must</em></span> start at the beginning of the line, since
        flex considers any line that starts with whitespace to be code to be
        copied into the generated C program.)</p><p>In this program, there are only three patterns. The first one,
        <code>[a-zA-Z]+</code>, matches a word. The
        characters in brackets, known as a <span><em>character
        class</em></span>, match any single upper- or lowercase letter, and the
        <code>+</code> sign means to match one or more
        of the preceding thing, which here means a string of letters or a
        word. The action code updates the number of words and characters seen.
        In any flex action, the variable <code>yytext</code> is set to point to the input text
        that the pattern just matched. In this case, all we care about is how
        many characters it was so we can update the character count
        appropriately.</p><p>The second pattern, <code>\n</code>, just
        matches a new line. The action updates the number of lines and
        characters.</p><p>The final pattern is a dot, which is regex-ese for any
        character. (It’s similar to a <code>?</code> in
        shell scripts.) The action updates the number of characters. And
        that’s all the patterns we need.<sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#ftn.id347971">2</a>]</sup></p><p>The C code at the end is a main program that calls <code>yylex()</code>, the name that flex gives to the
        scanner routine, and then prints the results. In the absence of any
        other arrangements, the scanner reads from the standard input. So
        let’s run it.</p><div style="overflow: auto;"><pre>$ flex fb1-1.l
$ cc lex.yy.c -lfl
$ ./a.out
The boy stood on the burning deck
shelling peanuts by the peck
^D
2 12 63
$</pre></div><p>First we tell flex to translate our program, and in classic Unix
        fashion since there are no errors, it does so and says nothing. Then
        we compile <code>lex.yy.c</code>, the C program
        it generated; link it with the flex library, <code>-lfl</code>; run it; and type a little input for it
        to count. Seems to work.</p><p>The actual <code>wc</code> program uses a
        slightly different definition of a word, a string of non-whitespace
        characters. Once we look up what all the whitespace characters are, we
        need only replace the line that matches words with one that matches a
        string of non-whitespace characters:</p><div style="overflow: auto;"><pre>[^ \t\n\r\f\v]+  { words++; chars += strlen(yytext); }</pre></div><p>The <code>^</code> at the beginning of the
        character class means to match any character other than the ones in
        the class, and the <code>+</code> once again
        means to match one or more of the preceding patterns. This
        demonstrates one of flex’s strengths—it’s easy to make small changes
        to patterns and let flex worry about how they might affect the
        generated code.</p></div><div><h3>Programs in Plain Flex</h3><p>Some applications are simple enough that you can write the whole
        thing in flex, or in flex with a little bit of C. For example, <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#etoalex">Example&nbsp;1-2</a> shows the skeleton of a translator from English
        to American.</p><div><p>Example&nbsp;1-2.&nbsp;English to American fb1-2.l</p><div style="overflow: auto;"><pre>/* English -&gt; American */
%%
"colour" { printf("color"); }
"flavour" { printf("flavor"); }
"clever" { printf("smart"); }
"smart" { printf("elegant"); }
"conservative" { printf("liberal"); }
 … lots of other words …
. { printf("%s", yytext); }
%%</pre></div></div><p>It reads through its input, printing the American version when
        it matches an English word and passing everything else through. This
        example is somewhat unrealistic (<span><em>smart</em></span> can also
        mean hurt, after all), but flex is not a bad tool to use for doing
        modest text transformations and for programs that collect statistics
        on input. More often than not, though, you’ll want to use flex to
        generate a scanner that divides the input into tokens that are then
        used by other parts of your program.</p></div><div><h3>Putting Flex and Bison Together</h3><p>The first program we’ll write using both flex and bison
        is a desk calculator. First we’ll write a scanner, and then we’ll
        write a parser and splice the two of them together.</p><p>To keep things simple, we’ll start by recognizing only integers,
        four basic arithmetic operators, and a unary absolute value operator
        (<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#calclex1">Example&nbsp;1-3</a>).</p><div><p>Example&nbsp;1-3.&nbsp;A simple flex scanner fb1-3.l</p><div style="overflow: auto;"><pre>/* recognize tokens for the calculator and print them out */
%%
"+"    { printf("PLUS\n"); }
"-"    { printf("MINUS\n"); }
"*"    { printf("TIMES\n"); }
"/"    { printf("DIVIDE\n"); }
"|"    { printf("ABS\n"); }
[0-9]+ { printf("NUMBER %s\n", yytext); }
\n     { printf("NEWLINE\n"); }
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }
%%</pre></div></div><p>The first five patterns are literal operators, written as quoted
        strings, and the actions, for now, just print a message saying what
        matched. The quotes tell flex to use the strings as is, rather than
        interpreting them as regular expressions.</p><p>The sixth pattern matches an integer. The bracketed pattern
        <code>[0-9]</code>matches any single digit, and
        the following <code>+</code> sign means to match
        one or more of the preceding item, which here means a string of one or
        more digits. The action prints out the string that’s matched, using
        the pointer <code>yytext</code> that the scanner
        sets after each match.</p><p>The seventh pattern matches a newline character, represented by
        the usual C <code>\n</code> sequence.</p><p>The eighth pattern ignores whitespace. It matches any single
        space or tab (<code>\t</code>), and the empty
        action code does nothing.</p><p>The final pattern is the catchall to match anything the other
        patterns didn’t. Its action code prints a suitable complaint.</p><p>These nine patterns now provide rules to match anything that the
        user might enter. As we continue to develop the calculator, we’ll add
        more rules to match more tokens, but these will do to get us
        started.</p><p>In this simple flex program, there’s no C code in the third
        section. The flex library (<code>-lfl</code>) provides a tiny main program
        that just calls the scanner, which is adequate for this
        example.</p><p>So let’s try out our scanner:</p><div style="overflow: auto;"><pre>$ flex fb1-3.l
$ cc lex.yy.c -lfl
$ ./a.out
12+34
NUMBER 12
PLUS
NUMBER 34
NEWLINE
 5 6 / 7q
NUMBER 5
NUMBER 6
DIVIDE
NUMBER 7
Mystery character q
NEWLINE
^D
$</pre></div><p>First we run flex, which translates the scanner into a C program
        called <code>lex.yy.c</code>, then we compile
        the C program, and finally we run it. The output shows that it
        recognizes numbers as numbers, it recognizes operators as operators,
        and the <code>q</code> in the last line of input
        is caught by the catchall pattern at the end. (That <code>^D</code> is a Unix/Linux end-of-file character. On
        Windows you’d type <code>^Z</code>.)</p></div><div><h3>The Scanner as Coroutine</h3><p>Most programs with flex scanners use the scanner to
        return a stream of tokens that are handled by a parser. Each time the
        program needs a token, it calls <code>yylex()</code>, which reads a little input and
        returns the token. When it needs another token, it calls <code>yylex()</code> again. The scanner acts as a
        coroutine; that is, each time it returns, it remembers where it was,
        and on the next call it picks up where it left off.</p><p>Within the scanner, when the action code has a token ready, it
        just returns it as the value from <code>yylex()</code>. The next time the program calls
        <code>yylex()</code>, it resumes scanning with
        the next input characters. Conversely, if a pattern doesn’t produce a
        token for the calling program and doesn’t return, the scanner will
        just keep going within the same call to <code>yylex()</code>, scanning the next input characters.
        This incomplete snippet shows two patterns that return tokens, one for
        the <code>+</code> operator and one for a
        number, and a whitespace pattern that does nothing, thereby ignoring
        what it matched.</p><div style="overflow: auto;"><pre>"+"    { return ADD; }
[0-9]+ { return NUMBER; }
[ \t] { /* ignore whitespace */ }</pre></div><p>This apparent casualness about whether action code returns often
        confuses new flex users, but the rule is actually quite simple: If
        action code returns, scanning resumes on the next call to <code>yylex()</code>; if it doesn’t return, scanning
        resumes immediately.</p><p>Now we’ll modify our scanner so it returns tokens that a parser
        can use to implement a calculator.</p></div><div><h3>Tokens and Values</h3><p>When a flex scanner returns a stream of tokens, each
        token actually has two parts, the token and the token’s
        <span><em>value</em></span>. The token is a small integer. The token
        numbers are arbitrary, except that token zero always means
        end-of-file. When bison creates a parser, bison assigns the token
        numbers automatically starting at 258 (this avoids collisions with
        literal character tokens, discussed later) and creates a <code>.h</code> with definitions of the tokens numbers.
        But for now, we’ll just define a few tokens by hand:</p><div style="overflow: auto;"><pre>NUMBER = 258,
ADD = 259,
SUB = 260,
MUL = 261,
DIV = 262,
ABS = 263,
EOL = 264 end of line</pre></div><p>(Well, actually, it’s the list of token numbers that bison will
        create, as we’ll see a few pages ahead. But these token numbers are as
        good as any.)</p><p>A token’s value identifies which of a group of similar tokens
        this one is. In our scanner, all numbers are <code>NUMBER</code> tokens, with the value saying what
        number it is. When parsing more complex input with names,
        floating-point numbers, string literals, and the like, the value says
        which name, number, literal, or whatever, this token is. Our first
        version of the calculator’s scanner, with a small main program for
        debugging, is in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#clex1">Example&nbsp;1-4</a>.</p><div><p>Example&nbsp;1-4.&nbsp;Calculator scanner fb1-4.l</p><div style="overflow: auto;"><pre>/* recognize tokens for the calculator and print them out */
%{
   enum yytokentype {
     NUMBER = 258,
     ADD = 259,
     SUB = 260,
     MUL = 261,
     DIV = 262,
     ABS = 263,
     EOL = 264
   };

   int yylval;
%}

%%
"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
"|"    { return ABS; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
.      { printf("Mystery character %c\n", *yytext); }
%%
main(int argc, char **argv)
{
  int tok;

  while(tok = yylex()) {
    printf("%d", tok);
    if(tok == NUMBER) printf(" = %d\n", yylval);
    else printf("\n");
  }
}</pre></div></div><p>We define the token numbers in a C <code>enum</code>. Then we make <code>yylval</code>, the variable that stores the token
        value, an integer, which is adequate for the first version of our
        calculator. (Later we’ll see that the value is usually defined as a
        union so that different kinds of tokens can have different kinds of
        values, e.g., a floating-point number or a pointer to a symbol’s entry
        in a symbol table.)</p><p>The list of patterns is the same as in the previous example, but
        the action code is different. For each of the tokens, the scanner
        returns the appropriate code for the token; for numbers, it turns the
        string of digits into an integer and stores it in <code>yylval</code> before returning. The pattern that
        matches whitespace doesn’t return, so the scanner just continues to
        look for what comes next.</p><p>For testing only, a small main program calls <code>yylex()</code>, prints out the token values, and,
        for <code>NUMBER</code> tokens, also prints
        <code>yylval</code>.</p><div style="overflow: auto;"><pre>$ flex fb1-4.l
$ cc lex.yy.c -lfl
$ ./a.out
a / 34 + |45
Mystery character a
262
258 = 34
259
263
258 = 45
264
^D
$</pre></div><p>Now that we have a working scanner, we turn our attention to
        parsing.</p><div><p>Where Did Flex and Bison Come From?</p><p>Bison is descended from yacc, a parser generator written
          between 1975 and 1978 by Stephen C. Johnson at Bell Labs. As its
          name, short for “yet another compiler compiler,” suggests, many
          people were writing parser generators at the time. Johnson’s tool
          combined a firm theoretical foundation from parsing work by D. E.
          Knuth, which made its parsers extremely reliable, and a convenient
          input syntax. These made it extremely popular among users of Unix
          systems, although the restrictive license under which Unix was
          distributed at the time limited its use outside of academia and the
          Bell System. In about 1985, Bob Corbett, a graduate student at the
          University of California, Berkeley, reimplemented yacc using
          somewhat improved internal algorithms, which evolved into Berkeley
          yacc. Since his version was faster than Bell’s yacc and was
          distributed under the flexible Berkeley license, it quickly became
          the most popular version of yacc. Richard Stallman of the Free Software
          Foundation (FSF) adapted Corbett’s work for use in the GNU project,
          where it has grown to include a vast number of new features as it
          has evolved into the current version of bison. Bison is now
          maintained as a project of the FSF and is distributed under the GNU
          Public License.</p><p>In 1975, Mike Lesk and summer intern Eric Schmidt wrote lex, a
          lexical analyzer generator, with most of the programming being done
          by Schmidt. They saw it both as a standalone tool and as a companion
          to Johnson’s yacc. Lex also became quite popular, despite being
          relatively slow and buggy. (Schmidt nonetheless went on to have a
          fairly successful career in the computer industry where he is now
          the CEO of Google.)</p><p>In about 1987, Vern Paxson of the Lawrence Berkeley Lab took a
          version of lex written in ratfor (an extended Fortran popular at the
          time) and translated it into C, calling it flex, for
          “<span><em>F</em></span>ast <span><em>Lex</em></span>ical Analyzer
          Generator.” Since it was faster and more reliable than AT&amp;T lex
          and, like Berkeley yacc, available under the Berkeley license, it
          has completely supplanted the original lex. Flex is now a
          SourceForge project, still under the Berkeley license.</p></div></div></div><div><h2>Grammars and Parsing</h2><p>The parser’s job is to figure out the relationship among
      the input tokens. A common way to display such relationships is a
      <span><em>parse tree</em></span>. For example, under the usual rules of
      arithmetic, the arithmetic expression <code>1 * 2 + 3 * 4 + 5</code> would have the parse tree in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#ptree1">Figure&nbsp;1-1</a>.</p><div><div><img src="https://www.oreilly.com/library/view/flex-bison/9780596805418/httpatomoreillycomsourceoreillyimages1740020.png" alt="Expression parse tree" class="block-image"></div><p>Figure&nbsp;1-1.&nbsp;Expression parse tree</p></div><p>Multiplication has higher precedence than addition, so the first
      two expressions are <code>1 * 2</code> and <code>3 * 4</code>. Then those two
      expressions are added together, and that sum is then added to 5. Each
      branch of the tree shows the relationship between the tokens or subtrees
      below it. The structure of this particular tree is quite simple and
      regular with two descendants under each node (that’s why we use a
      calculator as the first example), but any bison parser makes a parse
      tree as it parses its input. In some applications, it creates the tree
      as a data structure in memory for later use. In others, the tree is just
      implicit in the sequence of operations the parser does.</p><div><h3>BNF Grammars</h3><p>In order to write a parser, we need some way to describe
        the rules the parser uses to turn a sequence of tokens into a parse
        tree. The most common kind of language that computer parsers handle is
        a <span><em>context-free grammar</em></span> (CFG).<sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#ftn.id302969">3</a>]</sup> The standard form to write down a CFG is
        <span><em>Backus-Naur Form</em></span> (BNF), created around 1960 to
        describe Algol 60 and named after two members of the Algol 60
        committee.</p><p>Fortunately, BNF is quite simple. Here’s BNF for simple
        arithmetic expressions enough to handle <code>1 * 2 + 3 * 4 + 5</code>:</p><div style="overflow: auto;"><pre>&lt;exp&gt; ::= &lt;factor&gt; 
      | &lt;exp&gt; + &lt;factor&gt;
&lt;factor&gt; ::= NUMBER
      | &lt;factor&gt; * NUMBER</pre></div><p>Each line is a <span><em>rule</em></span> that says how to create
        a branch of the parse tree. In BNF, <code>::=</code> can be read “is a” or “becomes,” and
        <code>|</code> is “or,” another way to create a
        branch of the same kind. The name on the left side of a rule is a
        <span><em>symbol</em></span> or <span><em>term</em></span>. By
        convention, all tokens are considered to be symbols, but there are
        also symbols that are not tokens.</p><p>Useful BNF is invariably quite recursive, with rules that refer
        to themselves directly or indirectly. These simple rules can match an
        arbitrarily complex sequence of additions and multiplications by
        applying them recursively.</p></div><div><h3>Bison’s Rule Input Language</h3><p>Bison rules are basically BNF, with the punctuation
        simplified a little to make them easier to type. <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#calc1">Example&nbsp;1-5</a> shows the bison code, including the BNF, for the
        first version of our calculator.</p><div><p>Example&nbsp;1-5.&nbsp;Simple calculator fb1-5.y</p><div style="overflow: auto;"><pre>/* simplest version of calculator */
%{
#include &lt;stdio.h&gt;
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
 | ABS term   { $$ = $2 &gt;= 0? $2 : - $2; }
;
%%
main(int argc, char **argv)
{
  yyparse();
}

yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
}</pre></div></div><p>Bison programs have (not by coincidence) the same three-part
        structure as flex programs, with declarations, rules, and C code. The
        declarations here include C code to be copied to the beginning of the
        generated C parser, again enclosed in <code>%{</code> and <code>%}</code>. Following that are <code>%token</code> token declarations, telling bison the
        names of the symbols in the parser that are tokens. By convention,
        tokens have uppercase names, although bison doesn’t require it. Any
        symbols not declared as tokens have to appear on the left side of at
        least one rule in the program. (If a symbol neither is a token nor
        appears on the left side of a rule, it’s like an unreferenced variable
        in a C program. It doesn’t hurt anything, but it probably means the
        programmer made a mistake.)</p><p>The second section contains the rules in simplified BNF. Bison
        uses a single colon rather than <code>::=</code>, and since line boundaries are not
        significant, a semicolon marks the end of a rule. Again, like flex,
        the C action code goes in braces at the end of each rule.</p><p>Bison automatically does the parsing for you, remembering what
        rules have been matched, so the action code maintains the values
        associated with each symbol. Bison parsers also perform side effects
        such as creating data structures for later use or, as in this case,
        printing out results. The symbol on the left side of the first rule is
        the <span><em>start symbol</em></span>, the one that the entire input
        has to match. There can be, and usually are, other rules with the same
        start symbol on the left.</p><p>Each symbol in a bison rule has a value; the value of the target
        symbol (the one to the left of the colon) is called <code>$$</code> in the action code, and the values on the
        right are numbered <code>$1</code>, <code>$2</code>, and so forth, up to the number of
        symbols in the rule. The values of tokens are whatever was in <code>yylval</code> when the scanner returned the token;
        the values of other symbols are set in rules in the parser. In this
        parser, the values of the <code>factor</code>,
        <code>term</code>, and <code>exp</code> symbols are the value of the expression
        they represent.</p><p>In this parser, the first two rules, which define the symbol
        <code>calclist</code>, implement a loop that
        reads an expression terminated by a newline and prints its value. The
        definition of <code>calclist</code> uses a
        common two-rule recursive idiom to implement a sequence or list: the
        first rule is empty and matches nothing; the second adds an item to
        the list. The action in the second rule prints the value of the
        <code>exp</code> in $2.</p><p>The rest of the rules implement the calculator. The rules with
        operators such as <code>exp ADD factor</code>
        and <code>ABS term</code> do the appropriate
        arithmetic on the symbol values. The rules with a single symbol on the
        right side are syntactic glue to put the grammar together; for
        example, an <code>exp</code> is a <code>factor</code>. In the absence of an explicit action
        on a rule, the parser assigns <code>$1</code> to
        <code>$$</code>. This is a hack, albeit a very
        useful one, since most of the time it does the right thing.</p><div><p>How About Parsing English?</p><p>For a very long time, as far back as the 1950s, people have
          been trying to program computers to handle <span><em>natural
          languages</em></span>, languages spoken by people rather than by
          computers, a task that turns out to be extremely difficult. One
          approach is to parse them with the same techniques used for computer
          languages, as in this fragment:</p><div style="overflow: auto;"><pre>simple_sentence: subject verb object
      |     subject verb object prep_phrase ;

subject:    NOUN
      |     PRONOUN
      |     ADJECTIVE subject ;

verb:       VERB
      |     ADVERB VERB
      |     verb VERB ;

object:     NOUN
      |     ADJECTIVE object ;

prep_phrase:     PREPOSITION NOUN ;</pre></div><p>Unfortunately, it doesn’t work beyond small and unrealistic
          subsets of natural languages. Although natural languages have
          grammars, the grammars are extremely complex and not easy to write
          down or to handle in software. It remains an interesting and open
          question why this should be. Why are languages we invent for our
          computers so much simpler than the ones we speak?</p></div></div><div><h3>Compiling Flex and Bison Programs Together</h3><p>Before we build the scanner and parser into a working
        program, we have to make some small changes to the scanner in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#clex1">Example&nbsp;1-4</a> so we can call it from the parser. In particular,
        rather than defining explicit token values in the first part, we
        include a header file that bison will create for us, which includes
        both definitions of the token numbers and a definition of <code>yylval</code>. We also delete the testing main
        routine in the third section of the scanner, since the parser will now
        call the scanner. The first part of the scanner now looks like <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#clex2">Example&nbsp;1-6</a>.</p><div><p>Example&nbsp;1-6.&nbsp;Calculator scanner fb1-5.l</p><div style="overflow: auto;"><pre>%{
# include "fb1-5.tab.h"
%}
%%  same rules as before, and no code in the third section</pre></div></div><p>The build process is now complex enough to be worth putting into
        a <code>Makefile</code>:</p><div style="overflow: auto;"><pre># part of the makefile
fb1-5:  fb1-5.l fb1-5.y
        bison -d fb1-5.y
        flex fb1-5.l
        cc -o $@ fb1-5.tab.c lex.yy.c -lfl</pre></div><p>First it runs bison with the <code>-d</code> (for “definitions” file) flag, which
        creates <code>fb1-5.tab.c</code> and <code>fb1-5.tab.h</code>, and it runs flex to create
        <code>lex.yy.c</code>. Then it compiles them
        together, along with the flex library. Try it out, and in particular
        verify that it handles operator precedence correctly, doing
        multiplication and division before addition and subtraction:</p><div style="overflow: auto;"><pre>$ ./fb1-5
2 + 3 * 4
= 14
2 * 3 + 4
= 10
20 / 4 - 2
= 3
20 - 4 / 2
= 18</pre></div></div></div><div><h2>Ambiguous Grammars: Not Quite</h2><p>The reader may be wondering at this point whether the
      grammar in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#calc1">Example&nbsp;1-5</a> is needlessly complicated. Why not
      just write this?</p><div style="overflow: auto;"><pre>exp: exp ADD exp
   | exp SUB exp
   | exp MUL exp
   | exp DIV exp
   | ABS exp
   | NUMBER
   ;</pre></div><p>There are two answers: precedence and ambiguity. The separate symbols for <code>term</code>, <code>factor</code>, and <code>exp</code> tell bison to handle <code>ABS</code>, then <code>MUL</code> and <code>DIV</code>, and then <code>ADD</code> and <code>SUB</code>. In general, whenever a grammar has
      multiple levels of precedence where one kind of operator binds “tighter”
      than another, the parser will need a level of rule for each
      level.</p><p>Well, then, OK, how about this?</p><div style="overflow: auto;"><pre>exp: exp ADD exp
   | exp SUB exp
   | factor
   ;
 similarly for factor and term</pre></div><p>One of bison’s greatest strengths, and simultaneously one
      of its most annoying aspects, is that <span><em>it will not parse an
      ambiguous grammar</em></span>. That is, any parser that bison creates has
      exactly one way to parse any input that it parses, and the parser will
      accept exactly that grammar. The previous grammar is ambiguous, because
      input such as <code>1 - 2 + 3</code> could be
      parsed either as <code>(1-2) + 3</code> or as
      <code>1 - (2+3)</code>, two different expressions
      with different values. Although there are some cases where ambiguity
      doesn’t matter (e.g., <code>1+2+3</code>), in most
      cases the ambiguity really is an error, and the grammar needs to be
      fixed. The way we wrote the grammar in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#calc1">Example&nbsp;1-5</a> makes
      expressions unambiguously group to the left. If a grammar is ambiguous,
      bison reports <span><em>conflicts</em></span>, places where there are two
      different possible parses for a given bit of input. It creates a parser
      anyway, picking one option in each conflict, but that choice means the
      language it’s parsing isn’t necessarily the one you tried to specify. We
      discuss this at length in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch07.html">Chapter&nbsp;7</a>.</p><p>Bison’s usual parsing algorithm can look ahead one token to decide
      what rules match the input. Some grammars aren’t ambiguous but have
      places that require more than one token of lookahead to decide what
      rules will match. These also cause conflicts, although it is usually
      possible to rewrite the grammar so that one token lookahead is
      enough.</p><p>Actually, the previous discussion about ambiguity is not quite
      true. Since expression grammars are so common and useful, and since
      writing separate rules for each precedence level is tedious, bison has
      some special features that let you write an expression grammar in the
      natural way with one rule per operator in the form <code>exp OP exp</code> and just tell it what precedence
      and grouping rules to use to resolve the ambiguity. We’ll learn about
      these in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch03.html">Chapter&nbsp;3</a>. Also, bison has an alternative
      parsing technique called GLR that can handle ambiguous grammars and
      arbitrary lookahead, tracking all the possible parses that match the
      input in parallel. We cover this in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch09.html">Chapter&nbsp;9</a>.</p></div><div><h2>Adding a Few More Rules</h2><p>One of the nicest things about using flex and bison to
      handle a program’s input is that it’s often quite easy to make small
      changes to the grammar. Our expression language would be a lot more
      useful if it could handle parenthesized expressions, and it would be
      nice if it could handle comments, using <code>//</code> syntax. To do this, we need only add one
      rule to the parser and three to the scanner.</p><p>In the parser we define two new tokens, <code>OP</code> and <code>CP</code>
      for open and close parentheses, and add a rule to make a parenthesized
      expression a term:</p><div style="overflow: auto;"><pre>%token OP CP  in the declaration section
 ...
%%
term: NUMBER
 | ABS term { $$ = $2 &gt;= 0? $2 : - $2; }
 | OP exp CP { $$ = $2; } New rule
 ;</pre></div><p>Note the action code in the new rule assigns <code>$2</code>, the value of the expression in the
      parentheses, to <code>$$</code>.</p><p>The scanner has two new rules to recognize the two new tokens and
      one new rule to ignore two slashes followed by arbitrary text. Since a
      dot matches anything except a newline, <code>.*</code> will gobble up the rest of the line.</p><div style="overflow: auto;"><pre>"("     { return OP; }
")"     { return CP; }
"//".*  /* ignore comments */</pre></div><p>That’s it—rebuild the calculator, and now it handles parenthesized
      expressions and comments.</p></div><div><h2>Flex and Bison vs. Handwritten Scanners and Parsers</h2><p>The two example programs in this chapter, word count and a
      calculator, are both simple enough that we could without too much
      trouble have written them directly in C. But there is little reason to
      do so when developing a program. The pattern-matching technique that
      flex uses is quite fast and is usually about the same speed as a
      handwritten scanner. For more complex scanners with many patterns, a
      flex scanner may even be faster, since handwritten code will usually do
      many comparisons per character, while flex always does one. The flex
      version of a scanner is invariably much shorter than the equivalent C,
      which makes it a lot easier to debug. In general, if the rules for
      breaking an input stream into tokens can be described by regular
      expressions, flex is the tool of choice.</p><div><div>A Handwritten Scanner</div><p>If the lexical syntax of a language isn’t too complicated, a
        handwritten scanner can be a reasonable alternative to a flex scanner.
        Here’s a handwritten C equivalent of the scanner in <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#clex2">Example&nbsp;1-6</a>. This scanner will probably run a little faster
        than the flex version, but it’s a lot harder to modify to add or
        change token types. If you do plan to use a handwritten scanner,
        prototype it in flex first.</p><div style="overflow: auto;"><pre>/*
 * Handwritten version of scanner for calculator
 */

# include &lt;stdio.h&gt;
# include "fb1-5.tab.h"

FILE *yyin;
static int seeneof = 0;

int
yylex(void)
{
  if(!yyin) yyin = stdin;
  if(seeneof) return 0;		/* saw EOF last time */

  while(1) {
    int c = getc(yyin);

    if(isdigit(c)) {
      int i = c - '0';

      while(isdigit(c = getc(yyin)))
        i = (10*i) + c-'0';
      yylval = i;
      if(c == EOF) seeneof = 1;
      else ungetc(c, yyin);
      return NUMBER;
    }

    switch(c) {
    case '+': return ADD; case '-': return SUB;
    case '*': return MUL; case '|': return ABS;
    case '(': return OP;  case ')': return CP;
    case '\n': return EOL;
    case ' ': case '\t': break;	/* ignore these */
    case EOF: return 0;		/* standard end-of-file token */

    case '/': c = getc(yyin);
      if(c == '/') {		/* it's a comment */
	while((c = getc(yyin)) != '\n')
	  if(c == EOF) return 0; /* EOF in comment line */
	break;
      }
      if(c == EOF) seeneof = 1; /* it's division */
      else ungetc(c, yyin);
      return DIV;

    default: yyerror("Mystery character %c\n", c); break;
    }
  }
}</pre></div></div><p>Similarly, a bison parser is much shorter and easier to debug than
      the equivalent handwritten parser, particularly because of bison’s
      verification that the grammar is unambiguous.</p></div><div><h2>Exercises</h2><ol><li><p>Will the calculator accept a line that contains only a
          comment? Why not? Would it be easier to fix this in the scanner or
          in the parser?</p></li><li><p>Make the calculator into a hex calculator that accepts both
          hex and decimal numbers. In the scanner add a pattern such as
          <code>0x[a-f0-9]+</code> to match a hex
          number, and in the action code use <code>strtol</code> to convert the string to a number
          that you store in <code>yylval</code>; then
          return a <code>NUMBER</code> token. Adjust the
          output <code>printf</code> to print the result
          in both decimal and hex.</p></li><li><p>(extra credit) Add bit operators such as <code>AND</code> and <code>OR</code> to the calculator. The obvious operator
          to use for <code>OR</code> is a vertical bar,
          but that’s already the unary absolute value operator. What happens
          if you also use it as a binary <code>OR</code>
          operator, for example, <code>exp ABS factor</code>?</p></li><li><p>Does the handwritten version of the scanner from <a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#clex1">Example&nbsp;1-4</a> recognize exactly the same tokens as the flex
          version?</p></li><li><p>Can you think of languages for which flex wouldn’t be a good
          tool to write a scanner?</p></li><li><p>Rewrite the word count program in C. Run some large files
          through both versions. Is the C version noticeably faster? How much
          harder was it to debug?</p></li></ol></div><div><br><p><sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#id333485">1</a>] </sup>The internal form is known as a deterministic finite
          automation (DFA). Fortunately, the only thing you really need to
          know about DFAs at this point is that they’re fast, and the speed is
          independent of the number or complexity of the patterns.</p><p><sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#id347971">2</a>] </sup>The observant reader may ask, if a dot matches anything,
            won’t it also match the letters the first pattern is supposed to
            match? It does, but flex breaks a tie by preferring longer
            matches, and if two patterns match the same thing, it prefers the
            pattern that appears first in the flex program. This is an utter
            hack, but a very useful one we’ll see frequently.</p><p><sup>[<a href="https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html#id302969">3</a>] </sup>CFGs are also known as <span><em>phrase-structure
            grammars</em></span> or <span><em>type-2 languages</em></span>.
            Computer theorists and natural-language linguists independently
            developed them at about the same time in the late 1950s. If you’re
            a computer scientist, you usually call them CFGs, and if you’re a
            linguist, you usually call them PSGs or type-2, but they’re the
            same thing.</p></div>