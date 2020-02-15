#ifndef UNTITLED_OPQUADRUPLE_H
#define UNTITLED_OPQUADRUPLE_H

#include "include/ICR/Quadruple.hpp"

namespace MC{
	struct OPQuadruple: public Quadruple{
	public:
	  OPQuadruple(OperationType ot, std::string arg1, std::string arg2, std::string result, std::string op) : Quadruple(ot,arg1,arg2,result) {
	    this->op = op;
	  }

	  OPQuadruple(OperationType ot, std::string arg1, std::string result, std::string op) : Quadruple(ot,arg1,result) {
	    this->op = op;
	  }


	};

	typedef std::shared_ptr<OPQuadruple> OPQuadruple_p;
}


#endif
