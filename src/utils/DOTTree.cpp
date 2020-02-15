//
// Created by Chris Engelhardt on 2019-04-03.
//

#include "../include/utils/DOTTree.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>

char randchar(){
  const char charset[] =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz";
  const size_t max_index = (sizeof(charset) - 1);
  return charset[ rand() % max_index ];
}

std::string random_string( size_t length ) {

   std::string str(length,0);
   std::generate_n( str.begin(), length, randchar );
   return str;
}

DOTTree::DOTTree() {
   identifier = random_string(25);
}

DOTTree::DOTTree(std::string label) : label(label) {
 identifier = random_string(25);
}

DOTTree::DOTTree(std::string identifier, std::string &label) : identifier(identifier), label(label) { }

std::string &DOTTree::getIdentifier() {
   return identifier;
}

std::string &DOTTree::getLabel()  {
   return label;
}

void DOTTree::setLabel(std::string label) {
   this->label = label;
}

void DOTTree::setEdgeLabel(std::string edgeLabel) {
   this->edgeLabel=edgeLabel;
}

void DOTTree::addSubtree(DOTTree_p tree, bool visbileEdge){
   subtrees.push_back(std::make_tuple(tree, visbileEdge));
}

std::string &DOTTree::getCustomBoxAttributes() {
   return customBoxAttributes;
}

void DOTTree::setCustomBoxAttributes(std::string customBoxAttributes) {
   this->customBoxAttributes = customBoxAttributes;
}

void DOTTree::setCustomEdgeAttributes(std::string customEdgeAttributes) {
   this->customEdgeAttributes = customEdgeAttributes;
}

std::string DOTTree::getAttributes() {
   std::string attrb = " [";
   if(label != ""){
       attrb += "label=" + label+ ",";
   }
   return attrb + customBoxAttributes + "]";
}

std::string DOTTree::getEdgeAttributes() {
   std::string attrb = " [";
   if(edgeLabel != ""){
       attrb += "label=" + edgeLabel+ ",";
   }
   return attrb + customEdgeAttributes + "]";
}

   std::string DOTTree::getAllIdentifiers() {
   std::string elementList = "";
   elementList += "\t" + identifier + getAttributes() + "\n";
   for (auto tuple : subtrees){
       auto t = std::get<0>(tuple);
       elementList = elementList + t->getAllIdentifiers();
   }
   return elementList;
}

std::string DOTTree::getAllEdges() {
   std::string elementList = "";
   for (auto tuple : subtrees){
       auto t = std::get<0>(tuple);
       if (std::get<1>(tuple)) {
           elementList += "\n\t" + identifier + "->" + t->identifier + " " + t->getEdgeAttributes();
           elementList += t->getAllEdges();
       } else {
           elementList += t->getAllEdges();
       }
   }
   return elementList;
}

void DOTTree::saveDotTo(std::string path) {
   std::string dot = "digraph A {\n";
   dot += getAllIdentifiers();
   dot += getAllEdges();

   dot += "\n}";
   std::ofstream outfile;
   outfile.open(path, std::ios::trunc);
   outfile << dot << std::endl;
   outfile.close();
}


std::string DOTTree::getAllCustomEdges(){
   std::string stringBuilder = "\t";
   for(auto edge : customEdges){
       std::string label = "";
       if (edge.label == ""){
           label = "";
       }else{
           label = "label = " + edge.label;
       }

       if (auto edgeA = edge.a.lock()){
         if (auto edgeB = edge.b.lock()){
           stringBuilder += edgeA->identifier + "->" + edgeB->identifier + "  [" + label + "]\n\t";
         }
       }

   }
   return stringBuilder;
}

std::string DOTTree::getString(){
 std::string dot = "digraph A {\n";
 dot += getAllIdentifiers();
 dot += getAllEdges();
 dot += "\n";
 dot += getAllCustomEdges();
 dot += "\n}";
 return dot;
}

void DOTTree::addCustomEdge(CustomEdge e){
   customEdges.push_back(e);
}



void DOTTree::setCustomBoxAttributesForEach(std::string customBoxAttributes) {
   setCustomBoxAttributes(customBoxAttributes);
   for (auto tuple : subtrees){
       auto t = std::get<0>(tuple);
       t->setCustomBoxAttributesForEach(customBoxAttributes);
   }
}

void DOTTree::setCustomEdgeAttributesForEach(std::string customEdgeAttributes) {
   setCustomEdgeAttributes(customEdgeAttributes);
   for (auto tuple : subtrees){
       auto t = std::get<0>(tuple);
       t->setCustomEdgeAttributesForEach(customEdgeAttributes);
   }
}
