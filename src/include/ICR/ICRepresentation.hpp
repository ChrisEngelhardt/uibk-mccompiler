#ifndef UNTITLED_ICREPRESENTATION_H
#define UNTITLED_ICREPRESENTATION_H

#include <iostream>
#include <vector>

#include "include/ICR/OPQuadruple.hpp"
#include "include/ICR/Quadruple.hpp"
#include "include/utils/DOTTree.hpp"
#include "include/utils/Singleton.hpp"

namespace MC{
  class ICRepresentation: public Singleton <ICRepresentation>{
  private:
    friend class Singleton <ICRepresentation>;

    std::vector<Quadruple_p> list;
    int variableCounter = 0;
    int labelCounter = 0;
    int isGeneratingICR = false;

  protected:
    ICRepresentation(){}

  public:

    /**
     * Static function that converts fiven enum type to string
     * @param  ot Enum operation type
     * @return    associated string to type
     */
    static std::string convertOPTypeToString(Quadruple::OperationType ot);


    /**
     * Adds a quadruple to the ICRepresentation
     * @param quadruple Quadruple to add to the ICRepresentation
     */
    void insert(Quadruple_p quadruple);

    /**
     * Gets unique variable name for usage within the ICRepresentation
     * @return unique variable name
     */
    std::string getUniqueVariableName();

    /**
     * Gets unique label name for usage within the ICRepresentation
     * @return unique label name
     */
    std::string getUniqueLabelName();

    /**
     * Prints content of ICRepresentation to o stream
     * @param  function function, for which we want to print the ICR
     * @return o stream
     */
    std::ostream& printContent(std::ostream& os, const std::string function = "");

    /**
     * Prints content of ICRepresentation to o stream
     * @return o stream
     */
    bool getIsGeneratingICR();

    /**
     * Generates the cfg
     * @param  os out stream
     * @param  function function, for which we want to create the CFG
     * @return cfg as stream
     */
    std::ostream& generateCFG(std::ostream& os, const std::string function = "");

    /**
     * Getter for the ICR list
     * @return ICR list
     */
    std::vector<Quadruple_p>* getICRList();

  };
}

#endif
