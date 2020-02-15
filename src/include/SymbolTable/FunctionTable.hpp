#ifndef UNTITLED_FUNCTIONTABLE_H
#define UNTITLED_FUNCTIONTABLE_H

#include "include/SymbolTable/SymbolTable.hpp"

namespace MC{
	class FunctionTable: public SymbolTable{
	public:
	  ~FunctionTable(){};

	  std::ostream& printContent(std::string header, std::ostream& os);
	};
}
#endif //UNTITLED_FUNCTIONTABLE_H
