#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "Edge.h"
#include "Node.h"
#include <vector>
#include <string>
#include <set> 
#include <fstream>
#include <unordered_map>

using std::set;
using std::unordered_map;
using std::ifstream;


class Topology{
  private:
    set<int> nodeSet;
    unordered_map<int, Node*> nodeMap;


    void addNodesToMap(int node_1, int node_2, int cost);


  public:
    Topology();
    void updateNodes(ifstream& fileStream);
    void printNodeSet();
    Edge* createEdge(int dest, int cost);
    void printNodesAndEdges();


};


#endif