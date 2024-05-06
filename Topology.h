#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "Edge.h"
#include "Node.h"
#include <vector>
#include <string>
#include <set> 
#include <fstream>
#include <unordered_map>
#include <map>

using std::set;
using std::unordered_map;
using std::ifstream;


class Topology{
  private:
    map<int, Node*> nodeMap;
    int V;

    void addNodesToMap(int node_1, int node_2, int cost);
    void printNodesAndEdges(int randomInt);
    void dijkstra(int srcNodeID);
    void setNumberOfVertices();

  public:
    Topology();
    void generateTopology(ifstream& fileStream);
    void applyChangesFile(string lineFromFile);
    void printNodesAndEdges();
    void computeShortestPaths();
    void printDistAndPredecessorsForEveryNode();
    void generateNodeForwardingTables();
    void writeOutForwardingTablesForAllNodes(ofstream& fileStreamOut);
    void writeOutMessages(ofstream& fileStreamOut, string messagefile);

};

#endif