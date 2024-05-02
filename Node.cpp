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



Node::Node(int id) : _id(id){

}



vector<Edge>& Node::getEdges() {
    return edges;
}


void Node::addEdge(const Edge& newEdge){
    edges.push_back(newEdge);
}




void Node::assignDist(unordered_map<int, int> dist){
    this->dist = dist;
}

void Node::assignPredecessors(unordered_map<int, int> predecessors){
    this->predecessors = predecessors;
}


void Node::printDist(){
    cout << "node " << this->_id << "dist map: \n" << endl;
    cout << "Dest_id \t\t Dist"<< endl;
    for (auto it = dist.begin(); it != dist.end(); ++it){
        cout << it->first << "\t\t" << it->second << endl;
    }
}

void Node::printPredecessors(){
    cout << "node " << this->_id << "predecessors map: \n" << endl;
    cout << "Key: \t\t Value: "<< endl;
    for (auto it = predecessors.begin(); it != predecessors.end(); ++it){
        cout << it->first << "\t\t" << it->second << endl;
    }
}