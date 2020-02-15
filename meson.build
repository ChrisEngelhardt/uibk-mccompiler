project('mcc', 'cpp',
    default_options: [ 'buildtype=release',
                       'cpp_std=c++11',
                       'warning_level=3' ],
    meson_version: '>=0.44.0'
)
add_global_arguments('-Wno-deprecated-register', language : 'cpp')


# ------------------------------------------------------------------ Generators

flex = find_program('flex')
lgen = generator(flex,
                 output: ['@BASENAME@.cpp', '@BASENAME@.hh'],
                 arguments: [ '--outfile=@OUTPUT0@',
                              '--header-file=@OUTPUT1@',
                              '@INPUT@' ])

bison = find_program('bison')
pgen = generator(bison,
                 output: ['@BASENAME@.tab.cpp', '@BASENAME@.tab.hh'],
                 arguments: [ '-Wall',
                              '--output=@OUTPUT0@',
                              '--defines=@OUTPUT1@',
                              '@INPUT@' ])


# --------------------------------------------------------------------- Library

mcc_inc = include_directories('include')

mcc_src = [ 'src/mcc.cpp',
            'src/ast/StringLiteralAST.cpp', 'src/ast/FloatLiteralAST.cpp', 'src/ast/BinaryOpAST.cpp',
            'src/ast/ast.cpp', 'src/ast/ExpressionAST.cpp', 'src/ast/DeclarationStmtAST.cpp', 'src/ast/FunctionAST.cpp',
            'src/ast/StmtAST.cpp', 'src/ast/CallExprAST.cpp', 'src/ast/AssignmentStmtAST.cpp', 'src/ast/IfStmtAST.cpp',
            'src/ast/UnaryOpAST.cpp', 'src/ast/ReturnStmtAST.cpp', 'src/ast/ProgramAST.cpp', 'src/ast/BoolLiteralAST.cpp',
            'src/ast/StmtListAST.cpp', 'src/ast/WhileStmtAST.cpp', 'src/ast/LiteralAST.cpp', 'src/ast/IdentifierAST.cpp',
            'src/ast/IntLiteralAST.cpp', 'src/ast/CompoundStmtAST.cpp', 'src/ast/ExpressionStmtAST.cpp','src/utils/DOTTree.cpp',
            'src/ast/ArgumentsAST.cpp', 'src/ast/ParametersAST.cpp', 'src/ast/ArrayIdentifierAST.cpp',
            'src/SymbolTable/SymbolTable.cpp', 'src/SymbolTable/FunctionTable.cpp', 'src/SemanticChecks.cpp',
            'src/ICR/Quadruple.cpp', 'src/ICR/OPQuadruple.cpp', 'src/ICR/ICRepresentation.cpp', 'src/ASM/ASMGenerator.cpp',
            lgen.process('src/scanner.l'),
            pgen.process('src/parser.yy') ]

mcc_lib = library('mcc', mcc_src,
                  c_args: '-D_POSIX_C_SOURCE=200809L',
                  include_directories: [mcc_inc, include_directories('src')])


# ----------------------------------------------------------------- Arguments Library

arg_inc = include_directories('include')

arg_src = [ 'src/utils/ArgumentParser.cpp' ]

arg_lib = library('ArgumentParser', arg_src,
                  c_args: '-D_POSIX_C_SOURCE=200809L',
                  include_directories: [arg_inc, include_directories('src/utils')])


# ---------------------------------------------------------------- Applications
mcc_apps = [ 'mcc', 'mc_ast_to_dot', 'mc_symbol_table', 'mc_type_check_trace', 'mc_ir', 'mc_cfg_to_dot', 'mc_asm' ]

foreach app : mcc_apps
    executable(app, 'app/' + app + '.cpp',
               include_directories: mcc_inc,
               link_with: [mcc_lib,arg_lib])
endforeach


# ----------------------------------------------------------------------- Tests


gtest_dep = dependency('gtest', fallback: ['gtest', 'gtest_main_dep'])


if not gtest_dep.found()
  warning('MESON_SKIP_TEST: gtest not installed. Check scripts folder for installation')
endif

if gtest_dep.found()
  mcc_tests = [ 'MccTest' , 'SemanticTest', 'IRTest', 'AssemblyTest']
  foreach test : mcc_tests
    e = executable(test, 'test/unit/' + test + '.cpp', include_directories: mcc_inc, dependencies : gtest_dep, link_with: [mcc_lib,arg_lib])
    test(test, e)
  endforeach
endif
