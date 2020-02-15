#ifndef UNTITLED_ASMDEFINES_H
#define UNTITLED_ASMDEFINES_H

//Default sizes
#define INT_SIZE 4
#define FLOAT_SIZE 4
#define STRING_SIZE 4
#define POINTER_SIZE 1
#define BASE_OFFSET_PARAMS 4
#define BASE_OFFSET_LOCAL_VARS 0

//Default registers
#define ACC_REG "%eax"
#define ACC_BYTE_0_REG "%al"
#define DATA_STACK_REG "%ebp"
#define STACK_POINTER "%esp"
#define RETURN_REG "%eax"
#define UNARY_OP_REG "%eax"
#define EDX_REG "%edx"
#define ECX_REG "%ecx"

//Instruciton set
#define I_MOVE "movl"
#define I_ADD "addl"
#define I_SUB "subl"
#define I_MUL "imull"
#define I_DIV "idivl"
#define I_AND "andl"
#define I_OR "orl"
#define I_XORL "xorl"
#define I_JUMP "jmp"
#define I_CJUMP "jne"
#define I_PUSH "pushl"
#define I_CMP "cmpl"
#define I_CALL "call"
#define I_CONV_SLONG_TO_SDOUBLE "cltd"
#define I_SETE "sete"
#define I_SETNE "setne"
#define I_SETL "setl"
#define I_SETG "setg"
#define I_SETLE "setle"
#define I_SETGE "setge"
#define I_MOVZBL "movzbl"
#define I_LEAL "leal"


//Float instructions
#define I_FLDS "flds"
#define I_FSTP "fstp"
#define I_FSTPS "fstps"
#define I_FADDS "fadds"
#define I_FSUBS "fsubs"
#define I_FMULS "fmuls"
#define I_FDIVS "fdivs"
#define I_FCHS "fchs"
#define I_FCOMIP "fcomip"
#define I_SETA "seta"
#define I_SETB "setb"
#define I_SETAE "setae"
#define I_SETBE "setbe"



#define I_FLOAT ".float"
#define I_STRING ".string"


//Stuff
#define ENTRYPOINT "main"
#define CONDITION_FLAG_REG "%al"
#define FLOAT_STACK_TOP_REG "%st"
#define FLOAT_STACK_SEC_REG "%st(1)"
#define DEFAULT_RETURN_LABEL "return"


#endif //UNTITLED_ASMDEFINES_H
