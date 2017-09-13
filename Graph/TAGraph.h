//
// Created by bmuscede on 05/11/16.
//

#ifndef CLANGEX_TAGRAPH_H
#define CLANGEX_TAGRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include "ClangNode.h"
#include "ClangEdge.h"
#include "../Printer/VerbosePrinter.h"

class TAGraph {
public:
    TAGraph(Printer* print = new VerbosePrinter());
    ~TAGraph();

    void setPrinter(Printer* newPrint);

    bool addNode(ClangNode* node, bool assumeValid = false);
    bool addEdge(ClangEdge* edge, bool assumeValid = false);

    ClangNode* findNodeByID(std::string ID);
    std::vector<ClangNode*> findNodeByName(std::string name);
    ClangEdge* findEdgeByIDs(std::string IDOne, std::string IDTwo, ClangEdge::EdgeType type);
    std::vector<ClangNode*> findSrcNodesByEdge(ClangNode* dst, ClangEdge::EdgeType type);
    std::vector<ClangNode*> findDstNodesByEdge(ClangNode* src, ClangEdge::EdgeType type);
    std::vector<ClangEdge*> findEdgesBySrcID(ClangNode* src);
    std::vector<ClangEdge*> findEdgesByDstID(ClangNode* dst);

    bool nodeExists(std::string ID);
    bool edgeExists(std::string IDOne, std::string IDTwo, ClangEdge::EdgeType type);

    bool addAttribute(std::string ID, std::string key, std::string value);
    bool addAttribute(std::string IDSrc, std::string IDDst, ClangEdge::EdgeType type, std::string key, std::string value);

    std::string generateTAFormat();
    void addNodesToFile(std::map<std::string, ClangNode*> fileSkip);

    void addUnresolvedRef(std::string callerID, std::string calleeID, ClangEdge::EdgeType type);
    void addUnresolvedRefAttr(std::string callerID, std::string calleeID, std::string attrName, std::string attrValue);
    void resolveExternalReferences(bool silent = false);

    std::vector<ClangNode*> getNodes();
    std::vector<ClangEdge*> getEdges();

    void removeNode(ClangNode* node, bool unsafe = true);
    void removeEdge(ClangEdge* edge);

    static const std::string FILE_ATTRIBUTE;

private:
    std::unordered_map<std::string, ClangNode*> nodeList;
    std::unordered_map<std::string, std::vector<std::string>> nodeNameList;
    std::unordered_map<std::string, std::vector<ClangEdge*>> edgeSrcList;
    std::unordered_map<std::string, std::vector<ClangEdge*>> edgeDstList;

    std::vector<std::pair<std::pair<std::string, std::string>, ClangEdge::EdgeType>> unresolvedRef;
    std::vector<std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::vector<std::string>>>*> unresolvedRefAttr;

    Printer *clangPrinter;

    std::string const TA_HEADER = "//Generated TA File";
    std::string const TA_SCHEMA = "//Author: Jingwei Wu & Bryan J Muscedere\n\nSCHEME TUPLE :\n//Nodes\n$INHERIT\tcArch"
            "itecturalNds\tcRoot\n$INHERIT\tcAsgNds\t\t\tcRoot\n$INHERIT\tcSubSystem\t\tcArchitecturalNds\n$INHERIT\tcF"
            "ile\t\t\tcArchitecturalNds\n$INHERIT\tcClass\t\t\tcAsgNds\n$INHERIT\tcFunction\t\tcAsgNds\n$INHERIT\tcVari"
            "able\t\tcAsgNds\n$INHERIT\tcLang\t\t\tcAsgNds\n$INHERIT\tcEnum\t\t\tcLang\n$INHERIT\tcEnumConst\t\tcLang\n"
            "$INHERIT\tcStruct\t\t\tcLang\n$INHERIT\tcUnion\t\t\tcLang\n\n//Relationships\ncontain\t\tcRoot\t\t\tcRoot\n"
            "call\t\tcFunction\t\tcFunction\nreference\tcAsgNds\t\t\tcAsgNds\ninherit\t\tcClass\t\t\tcClass\nfContain\t"
            "cArchitecturalNds\tcAsgNds\n\nSCHEME ATTRIBUTE :\n$ENTITY {\n\tx\n\ty\n\twidth\n\theight\n\tlabel\n}\n\ncR"
            "oot {\n\telision = contain\n\tcolor = (0.0 0.0 0.0)\n\tfile\n\tline\n\tname\n}\n\ncAsgNds {\n\tbeg\n\tend"
            "\n\tfile\n\tline\n\tvalue\n\tcolor = (0.0 0.0 0.0)\n}\n\ncArchitecturalNds {\n\tclass_style = 4\n\tcolor ="
            " (0.0 0.0 1.0)\n\tcolor = (0.0 0.0 0.0)\n}\n\ncSubSystem {\n\tclass_style = 4\n\tcolor = (1.0 1.0 1.0)\n\t"
            "labelcolor = (0.0 0.0 0.0)\n}\n\ncFile {\n\tclass_style = 2\n\tcolor = (1.0 0.04 1.0)\n\tlabelcolor = (0.0"
            " 0.0 0.0)\n}\n\ncFunction {\n\tfilename\n\tisStatic\n\tisConst\n\tisVolatile\n\tisVariadic\n\tvisibility\n"
            "\tcolor = (1.0 0.0 0.0)\n\tlabelcolor = (0.0 0.0 0.0)\n}\n\ncVariable {\n\tfilename\n\tscopeType\n\tisStat"
            "ic\n}\n\ncClass {\n\tfilename\n\tbaseNum\n\tcolor = (0.2 0.4 0.1)\n\tlabelcolor = (0.0 0.0 0.0)\n}\n\ncEnu"
            "m {\n\tfilename\n\tcolor = (0.9 0.2 0.5)\n\tlabelcolor = (0.0 0.0 0.0)\n}\n\ncEnumConst {\n\tfilename\n\tc"
            "olor = (0.9 0.2 0.5)\n\tlabelcolor = (0.0 0.0 0.0)\n}\n\n(reference) {\n\taccess\n}\n";

    std::string generateInstances();
    std::string generateRelationships();
    std::string generateAttributes();
    std::vector<std::pair<std::string, std::vector<std::string>>> findAttributes(std::string callerID, std::string calleeID);
};


#endif //CLANGEX_TAGRAPH_H
