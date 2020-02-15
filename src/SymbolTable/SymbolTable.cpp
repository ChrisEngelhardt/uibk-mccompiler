//
// Created by Chris Engelhardt on 2019-04-19.
//

#include "include/SymbolTable/SymbolTable.hpp"

#include <sstream>

#include "include/SemanticChecks.hpp"
#include "include/utils/VariadicTable.hpp"

using namespace MC;

void SymbolTable::insert(Symbol_p s){

    //Remove if already from merge in list to achieve shadowing
    try{
      auto sym = get(s->identifier);
      if (sym->merged)
        erase(sym->identifier);
    }catch (std::out_of_range msg){}

    SemanticChecks::instance()->checkForUniqueSymbol(this, s->getIdentifier());

    um.insert({s->getIdentifier(),s});
}

Symbol_p SymbolTable::get(SymIdent ident){
    return um.at(ident);
}

bool SymbolTable::contains(SymIdent ident){
    return um.find(ident) != um.end();
}

void SymbolTable::erase(SymIdent ident){
    um.erase(ident);
}


unsigned long SymbolTable::size(){
    return um.size();
}


std::ostream& SymbolTable::printContent(std::string header, std::ostream& os){
  if (size() == 0) {return os;}
  os << header << std::endl;
  VariadicTable<std::string, std::string, int> vt({"Identifier", "Type", "Reference Counter"});
    for(auto p : um) {
      auto x = std::dynamic_pointer_cast<VarSymbol> (p.second);
      vt.addRow({p.first, x->getVarTypeAsString(), x->getReferencesCount()});
    }
  vt.print(os);
  os << std::endl << std::endl;
  return os;
}

std::unordered_map<std::string,Symbol_p> SymbolTable::getMap(){
  return um;
}

void SymbolTable::merge(SymbolTable inTable){
  std::unordered_map<std::string,Symbol_p> in = inTable.getMap();

  um.insert(in.begin(), in.end());

  for (auto& s: um) {
    s.second->merged = true;
  }
}
