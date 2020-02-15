#ifndef __ASM_GENERATOR_HPP__
#define __ASM_GENERATOR_HPP__

#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include "include/ASM/ASMDefines.hpp"
#include "include/ICR/OPQuadruple.hpp"
#include "include/ICR/Quadruple.hpp"

  class ASMGenerator {
  private:
    static std::map<std::string, int> calculateByteCounterPerMethod(std::vector<MC::Quadruple_p> *icr);

    static std::ostream& copyExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, MC::Quadruple_p p, int& floatStringCounter, std::ostream& floatStringHolderOS, std::ostream& asmOs);

    static std::ostream& pCallExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, MC::Quadruple_p p, std::ostream& asmOs, bool isFloat = false);

    static std::ostream& floatCalculusExpression(std::string op,std::map<std::string, int>& variableMap, MC::Quadruple_p p, std::ostream& asmOs);

    static std::ostream& floatBoolExpression(std::string op,std::map<std::string, int>& variableMap, MC::Quadruple_p p, std::ostream& asmOs);

    static std::ostream& binaryExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, MC::Quadruple_p p, std::ostream& asmOs);

    static std::ostream& unaryExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, MC::Quadruple_p p, std::ostream& asmOs);

    static std::ostream& execExpression(int offset, std::string op, std::ostream& asmOs);

    static std::ostream& moveToStackExpression(int offset, std::ostream& asmOs);

    static std::ostream& parameterFExpression(std::map<std::string, int>& variableMap, int& stackOffsetCounter, MC::Quadruple_p p, int parameterCounter, std::ostream& asmOs);

    static std::ostream& binaryBoolExpression(std::string op, std::ostream& asmOs);

  public:
    /**
     * Create an the asm representation
     * @param astType type of the ast node
     * @param os output stream for debugging
     * @param asm output stream for asm
     */
    static std::ostream& generate(std::vector<MC::Quadruple_p> *icr, std::ostream& os, std::ostream& asmOs, std::string name = "a", const std::string function = "");
  };

#endif
