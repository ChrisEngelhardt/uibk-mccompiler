//
// Created by Chris Engelhardt on 2019-04-03.
//

#ifndef __DOT_DOTTREE_HPP__
#define __DOT_DOTTREE_HPP__

#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

/**
 * A class which represents a tree structure and can be exported in the .dot format
 */
class DOTTree;
typedef std::shared_ptr<DOTTree> DOTTree_p;

class DOTTree {

public :
    struct CustomEdge{
        std::weak_ptr<DOTTree> a;
        std::weak_ptr<DOTTree> b;
        std::string label;

        CustomEdge(std::weak_ptr<DOTTree> a, std::weak_ptr<DOTTree> b, std::string label): a(a), b(b), label(label) {  }

    };

private:
    std::string identifier;
    std::string label;
    std::string edgeLabel;
    std::string customBoxAttributes;
    std::string customEdgeAttributes;
    std::vector<std::tuple<DOTTree_p,bool>> subtrees;
    std::vector<CustomEdge> customEdges;

protected:


    std::string getAttributes();

    std::string getEdgeAttributes();

    std::string getAllIdentifiers();

    std::string getAllEdges();

    std::string getAllCustomEdges();


public:
    std::string &getIdentifier();

    std::string &getLabel();

    std::string &getCustomBoxAttributes();

    /**
     * Create an DOT tree with an UUID as identifier
     */
    DOTTree();

    /**
     * Create an DOT tree with an UUID as identifier and label
     * @param label Label of the box
     */
    DOTTree(std::string label);

    /**
     * Create an DOT tree with a custom UUID and label
     * @param identifier The identifier of this box (must be unique)
     * @param label Label of the box
     */
    DOTTree(std::string identifier, std::string &label);


    /**
     * Set custom attributes for this box like shape or color
     * @param customBoxAttributes Attribute string withouth []
     */
    void setCustomBoxAttributes(std::string customBoxAttributes);

    /**
     * Set custom attributes for outgoing getAllEdges like color and thickness
     * @param customEdgeAttributes Attribute string withouth []
     */
    void setCustomEdgeAttributes(std::string customEdgeAttributes);

    /**
     * Set the label of the box
     * @param identifier the new label
     */
    void setLabel(std::string identifier);


    /**
     * Set the label of the ingoing edge
     * @param edgeLabel incoming edge label
     */
    void setEdgeLabel(std::string edgeLabel);

    /**
     * Add some subtree as child
     * Note child will be added from left to right depending on the insertion sequence
     * @param tree The dotTree to add
     */
    void addSubtree(DOTTree_p tree, bool visbileEdge = true);

    /**
    * Add some custom edge
    * @param custom edge to add
    */
    void addCustomEdge(CustomEdge e);


    /**
     * Generate a .dot file and save under path
     * @param path path to save
     */
    void saveDotTo(std::string path);

    /**
     * Generate .dot and return as string
     * @return .dot as string
     */
    std::string getString();

    /**
     * Set custom box attributes the box itself and all childs and subchilds
     * @param customBoxAttributes the box attribute withouth []
     */
    void setCustomBoxAttributesForEach(std::string customBoxAttributes);

    /**
     * Set custom edge attributes for the incoming edge including all edges below
     * @param customEdgeAttributes edge options withouth []
     */
    void setCustomEdgeAttributesForEach(std::string customEdgeAttributes);
};



#endif /* END __DOT_DOTTREE_HPP__ */
