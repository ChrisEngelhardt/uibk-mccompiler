#include "../include/ICR/ICRepresentation.hpp"

#include <map>

#include "../include/ast/AST.hpp"
#include "include/utils/VariadicTable.hpp"

using namespace MC;

void ICRepresentation::insert(Quadruple_p quadruple) {
    list.push_back(quadruple);
}

std::string ICRepresentation::getUniqueVariableName() {
    variableCounter++;
    return "t" + std::to_string(variableCounter - 1);
}

std::string ICRepresentation::getUniqueLabelName() {
    labelCounter++;
    return "L" + std::to_string(labelCounter - 1);
}

std::ostream &ICRepresentation::printContent(std::ostream &os, const std::string function) {
    int i = 0;
    VariadicTable<int, std::string, std::string, std::string, std::string, std::string> vt(
            {"#", "Instruction", "Operation", "Arg1", "Arg2", "Result"});

    std::string currentFunction = "";

    for (auto p : list) {
        if (function != ""){
            if (p->ot == Quadruple::OperationType::labelF){
                currentFunction = p->arg1;
            }
            if (currentFunction != function){
                continue;
            }
        }
        vt.addRow({i++, ICRepresentation::convertOPTypeToString(p->ot), p->op, p->arg1, p->arg2, p->result});
    }
    vt.print(os);
    os << std::endl << std::endl;
    return os;
}


std::ostream &ICRepresentation::generateCFG(std::ostream &os, const std::string function) {
    if (list.empty()) {
        throw(ICR_Exception("Please generated ICR before"));
    }
    DOTTree_p root = std::make_shared<DOTTree>();
    std::map<std::string, DOTTree_p> labelMap;
    std::vector<std::tuple < DOTTree_p, std::string, std::string >> edges;
    DOTTree_p currentTree = root;
    bool firstFunc = true;
    DOTTree_p tmp;
    std::string stringBuilder = "\"";

    bool visbileEdge = true;

    std::string currentFunction = "";

    for (auto p : list) {
        if (function != ""){
            if (p->ot == Quadruple::OperationType::labelF){
                currentFunction = p->arg1;
            }
            if (currentFunction != function){
                continue;
            }
        }

        switch (p->ot) {
            case Quadruple::OperationType::copyI:
            /* FALLTHRU */
            case Quadruple::OperationType::copyF:
                stringBuilder += p->result + " = " + p->arg1 + "\n";
                break;
            case Quadruple::OperationType::copyS:
                if(p->arg1.at(0) == 't'){
                    stringBuilder += p->result + " = " + p->arg1 + "\n";
                } else {
                    stringBuilder += p->result + " = \\" + p->arg1.substr(0, p->arg1.size()-1) + "\\\"\n";
                }
                break;
            case Quadruple::OperationType::declarationArray:
                stringBuilder += p->result + "[" + p->arg1 + "]\n";
                break;
            case Quadruple::OperationType::copyFromArrayI:
            /* FALLTHRU */
            case Quadruple::OperationType::copyFromArrayF:
            /* FALLTHRU */
            case Quadruple::OperationType::copyFromArrayS:
                stringBuilder += p->result + " = " + p->arg1 + "[" + p->arg2 +"]\n";
                break;
            case Quadruple::OperationType::copyToArrayI:
            /* FALLTHRU */
            case Quadruple::OperationType::copyToArrayF:
                stringBuilder += p->result + "[" + p->arg2 + "] = " + p->arg1 + "\n";
                break;
            case Quadruple::OperationType::copyToArrayS:
                if(p->arg1.at(0) == 't'){
                    stringBuilder += p->result + "[" + p->arg2 + "] = " + p->arg1 + "\n";
                } else {
                    stringBuilder += p->result + "[" + p->arg2 + "] = \\" + p->arg1.substr(0, p->arg1.size()-1) + "\\\"\n";
                }
                break;
            case Quadruple::OperationType::binaryI:
            /* FALLTHRU */
            case Quadruple::OperationType::binaryF:
                stringBuilder += p->result + " = " + p->arg1 + " " + p->op + " " + p->arg2 + "\n";
                break;
            case Quadruple::OperationType::label:
                tmp = std::make_shared<DOTTree>();
                currentTree->addSubtree(tmp,visbileEdge);
                visbileEdge = true;
                currentTree = tmp;
                labelMap[p->arg1] = currentTree;
                stringBuilder = "\"";
                break;
            case Quadruple::OperationType::labelF:
                if(!firstFunc){
                    tmp = std::make_shared<DOTTree>();
                    currentTree->addSubtree(tmp,false);
                    visbileEdge = true;
                    currentTree = tmp;
                } else {
                    firstFunc = false;
                }
                labelMap[p->arg1] = currentTree;
                stringBuilder = "\"" + p->arg1 +":\n";
                break;
            case Quadruple::OperationType::ucJump:
                edges.push_back(std::make_tuple(currentTree, p->arg1, ""));
                visbileEdge = false;
                break;
            case Quadruple::OperationType::parameter:
                stringBuilder += "parameter " + p->arg1 + "\n";
                break;
            case Quadruple::OperationType::parameterF:
                stringBuilder += p->result + " = parameterF\n";
                break;
            case Quadruple::OperationType::pCall:
            /* FALLTHRU */
            case Quadruple::OperationType::pCallF:
                stringBuilder += p->result + " = pCall " + p->arg1 + "\n";
                break;
            case Quadruple::OperationType::unaryI:
            /* FALLTHRU */
            case Quadruple::OperationType::unaryF:
                stringBuilder += p->result + " = " + p->op + p->arg1 + "\n";
            /* FALLTHRU */
            case Quadruple::OperationType::cJump:
                stringBuilder += "if "+p->arg1+" goto"+ "\n";
                currentTree->setLabel(stringBuilder + "\"");
                tmp = std::make_shared<DOTTree>();
                edges.push_back(std::make_tuple(currentTree, p->result, "F"));
                currentTree->addSubtree(tmp);
                tmp->setEdgeLabel("T");
                currentTree = tmp;
                stringBuilder = "\"";
                break;
            case Quadruple::OperationType::rtrn:
            /* FALLTHRU */
            case Quadruple::OperationType::rtrnF:
                if (p->arg1 != ""){
                    stringBuilder += "return "+p->arg1 + "\n";
                } else {
                    stringBuilder += "return\n";
                }
        }

        currentTree->setLabel(stringBuilder + "\"");
    }

    for (auto edge : edges){
        DOTTree_p tree = std::get<0>(edge);
        root->addCustomEdge(DOTTree::CustomEdge(tree, labelMap[std::get<1>(edge)], std::get<2>(edge)));
    }



    root->setCustomBoxAttributesForEach("shape=box");
    os << root->getString() << std::endl;
    return os;
}


std::string ICRepresentation::convertOPTypeToString(Quadruple::OperationType ot) {
    switch (ot) {
        case Quadruple::copyI:
            return "copyI";
        case Quadruple::copyF:
            return "copyF";
        case Quadruple::copyS:
            return "copyS";
        case Quadruple::declarationArray:
            return "declarationArray";
        case Quadruple::copyToArrayI:
            return "copyToArrayI";
        case Quadruple::copyToArrayF:
            return "copyToArrayF";
        case Quadruple::copyToArrayS:
            return "copyToArrayS";
        case Quadruple::copyFromArrayI:
            return "copyFromArrayI";
        case Quadruple::copyFromArrayF:
            return "copyFromArrayF";
        case Quadruple::copyFromArrayS:
            return "copyFromArrayS";
        case Quadruple::unaryI:
            return "unaryI";
        case Quadruple::unaryF:
            return "unaryF";
        case Quadruple::binaryI:
            return "binaryI";
        case Quadruple::binaryF:
            return "binaryF";
        case Quadruple::ucJump:
            return "ucJump";
        case Quadruple::cJump:
            return "cJump";
        case Quadruple::label:
            return "label";
        case Quadruple::labelF:
            return "labelF";
        case Quadruple::parameter:
            return "parameter";
        case Quadruple::parameterF:
            return "parameterF";
        case Quadruple::pCall:
            return "pCall";
        case Quadruple::pCallF:
            return "pCallF";
        case Quadruple::rtrn:
            return "rtrn";
        case Quadruple::rtrnF:
            return "rtrnF";
        default:
            return "Unknown";
    }
}


std::vector<Quadruple_p>* ICRepresentation::getICRList(){
  return &list;
}
