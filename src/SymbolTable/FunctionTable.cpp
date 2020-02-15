#include "include/SymbolTable/FunctionTable.hpp"

#include "include/utils/VariadicTable.hpp"

using namespace MC;

std::ostream& FunctionTable::printContent(std::string header, std::ostream& os){
  if (size() == 0) {return os;}
  os << header << std::endl;
  VariadicTable<std::string, std::string, std::string, std::string, int> vt({"Identifier", "Type", "Parameters", "Return-Type", "Reference Counter"});
    for(auto p : um) {
      auto x = std::dynamic_pointer_cast<BuiltInFunctionSymbol> (p.second);
      vt.addRow({p.first, x->type, x->getParameters(), x->getReturnType(), x->getReferencesCount()});
    }
  vt.print(os);
  os << std::endl << std::endl;
  return os;
}
