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
#include <algorithm>

using namespace std;



Node::Node(int id) : _id(id){

}


int Node::getID(){
    return _id;
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
    cout << "node " << this->_id << " dist map: \n" << endl;
    cout << "Dest_id \t\t Dist"<< endl;
    for (auto it = dist.begin(); it != dist.end(); ++it){
        cout << it->first << "\t\t" << it->second << endl;
    }
    cout << "\n\n" << endl;
}

void Node::printPredecessors(){
    cout << "node " << this->_id << " predecessors map: \n" << endl;
    cout << "Key: \t\t Value: "<< endl;
    for (auto it = predecessors.begin(); it != predecessors.end(); ++it){
        cout << it->first << "\t\t" << it->second << endl;
    }
    cout << "\n\n" << endl;
}



void Node::emptyForwardingTable() {
    this->forwardingTable.clear();
}




void Node::generateForwardingTableKeys(){
    // clear the forwarding table out before re-filling it with data
    for(auto it = this->dist.begin(); it != this->dist.end(); ++it){
        int destNodeID = it->first;
        forwardingTable[destNodeID] = ForwardingTableEntry{};
    }
}




string Node::generateBestPathToDestination(int destination) {
    std::vector<int> path;

    // Start from the destination node
    int current = destination;
    
    // Backtrack from destination to source
    while (current != this->_id) {
        path.push_back(current);
        current = this->predecessors.at(current); // Access the predecessor of the current node
    }
    
    path.push_back(this->_id); // Add the source node to the path
    std::reverse(path.begin(), path.end()); // Reverse the path to get the source-to-destination path

    // Create a string representation of the path
    std::ostringstream oss;
    oss << "Shortest path from " << this->_id << " to " << destination << ": ";
    for (int node : path) {
        oss << node << " ";
    }

    return oss.str(); // Return the string representation of the path
}





// Adds isReachable to ForwardingTableEntry
// Loop through the destination nodes in dist
    // if the distance to the node is not INF, generate a path to it 
void Node::generateAllPaths(){
    for(auto it = this->dist.begin(); it != this->dist.end(); ++it){
        string bestPath = "";
        bool isReachable = false;

        int destNodeID = it->first;
        if( dist[destNodeID] != INF ){
            isReachable = true;
            string bestPath = generateBestPathToDestination(destNodeID);
        }
        this->forwardingTable[destNodeID].isReachable = isReachable;
        this->forwardingTable[destNodeID].path = make_unique<string>(bestPath);
    }
}




void Node::generateForwardingTable(){
    // Loop through each destination id (key) in dist map:
        // generate Path for each destination and store in Node Forwarding Table

    // clears the current forwarding table (making it empty), and generates keys to the map, as well
    // as empty ForwardingTableEntry structs 
    this->emptyForwardingTable();
    this->generateForwardingTableKeys();
    this->generateAllPaths();
    this->printAllPaths();



}



void Node::printAllPaths(){
    for(auto it = forwardingTable.begin(); it != forwardingTable.end(); ++it){
        ForwardingTableEntry& entry = it->second;
        cout << "Best path from " << this->_id << " to " << entry.dest << ": " << entry.path << endl;
    }
    cout << "\n\n";

}

