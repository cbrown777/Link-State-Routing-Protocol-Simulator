#include "Node.h"
#include "Edge.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;



Node::Node(int id) : id(id){

    


}



vector<Edge*> Node::getEdges() const{
    return edges;
}


void Node::addEdge(Edge* newEdge){
    edges.push_back(newEdge);
}
