//
// Created by Chris Engelhardt on 2019-04-19.
//
#ifndef UNTITLED_SYMBOLTABLE_H
#define UNTITLED_SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>

#include "include/SymbolTable/Symbol.hpp"

namespace MC{
    class SymbolTable {
    protected:
        std::unordered_map<std::string,Symbol_p> um;
        std::unordered_map<std::string,Symbol_p> getMap();
    public:
        virtual ~SymbolTable(){};
        void insert(Symbol_p s);
        Symbol_p get(SymIdent ident);
        bool contains(SymIdent ident);
        void erase(SymIdent ident);
        void merge(SymbolTable inTable);
        unsigned long size();
        virtual std::ostream& printContent(std::string header, std::ostream& os);
    };
}


#endif //UNTITLED_SYMBOLTABLE_H
