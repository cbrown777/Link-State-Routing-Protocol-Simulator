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
    unordered_map<int, Node*> nodeMap;
    int V;


    void addNodesToMap(int node_1, int node_2, int cost);


    void printNodesAndEdges(int randomInt);

    void dijkstra(int src);

    void setNumberOfVertices();


  public:
    Topology();
    void updateNodes(ifstream& fileStream);
    void printNodesAndEdges();
    void computeShortestPaths();


};


#endif