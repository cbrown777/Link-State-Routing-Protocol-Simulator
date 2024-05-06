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
    for(auto it = this->dist.begin(); it != this->dist.end(); ++it){
        int destNodeID = it->first;
        //cout << "current dest node id: " << destNodeID << endl;
        forwardingTable[destNodeID] = ForwardingTableEntry{};
    }
    cout << "\n\n";
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
    //oss << "Shortest path from " << this->_id << " to " << destination << ": ";
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
            bestPath = generateBestPathToDestination(destNodeID);

            //cout << "\nbestPath returned is: " << bestPath << endl;
        }

        //cout << "destination node " << destNodeID << " is reachable: " << isReachable << ", and the path there is: " << bestPath << endl;

        this->forwardingTable[destNodeID].dest = destNodeID;
        this->forwardingTable[destNodeID].cost = dist[destNodeID];
        this->forwardingTable[destNodeID].isReachable = isReachable;
        this->forwardingTable[destNodeID].path = make_unique<string>(bestPath);
    }

    //cout << "\n\n\n" << endl;
}





int Node::getSecondNumber(const string& path) {
    istringstream iss(path); // Create an input string stream
    string token;

    // Extract the second token
    if (getline(iss, token, ' ')) { // Tokenize based on space
        if (getline(iss, token, ' ')) { // Get the second token
            // Convert the second token to an integer and return
            return stoi(token);
        }
    }

    // Return a default value (you might want to handle this differently based on your requirements)
    return -1;
}





void Node::generateNextHops(){
    for(auto it = forwardingTable.begin(); it != forwardingTable.end(); ++it){
        ForwardingTableEntry& entry = it->second;

        cout << "\n\n";
        cout << "forwardingTable index: " << it->first << endl;
        cout << "entry.isReachable: "<< entry.isReachable << endl;
        cout << "entry.cost: "<< entry.cost << endl;
        cout << "entry.dest: " << entry.dest << endl;
        cout << "*entry.path: " << *entry.path << endl;
        cout << "\n\n";

        if(entry.isReachable){
            if(this->_id == entry.dest){
                entry.nextHop = entry.dest;
            }else{
                entry.nextHop = getSecondNumber(*entry.path);
                // entry.nextHop = (*entry.path)[1];
            }
        }
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
    this->generateNextHops();
    this->printAllPaths();
}



void Node::printAllPaths(){
    for(auto it = forwardingTable.begin(); it != forwardingTable.end(); ++it){
        ForwardingTableEntry& entry = it->second;
        cout << "Path from " << this->_id << " to " << entry.dest << " isReachable: " << entry.isReachable << ", and the path is: " << *entry.path << " and the cost is: " << entry.cost << ", and the next hop is: " << entry.nextHop << endl;
    }
    cout << "\n\n";
}




void Node::writeOutForwardingTable(ofstream& fileStreamOut){
    fileStreamOut << "Node " << this->_id << " Forwarding Table..." << endl;
    for(auto it = this->forwardingTable.begin(); it != this->forwardingTable.end(); ++it){
        ForwardingTableEntry& entry = it->second;
        if(entry.isReachable){
            fileStreamOut << entry.dest << " " << entry.nextHop << " " << entry.cost << endl;
        }
    }
}




string Node::extractNumbersExceptLast(const string& path) {
    istringstream iss(path);
    ostringstream oss;
    
    string number;
    string lastNumber;
    bool isFirstNumber = true;
    bool hasMoreThanOneNumber = false;
    
    // Read numbers separated by space
    while (iss >> number) {
        if (!isFirstNumber) {
            if (!lastNumber.empty()) {
                oss << lastNumber << " "; // Add space before adding the number
            }
            hasMoreThanOneNumber = true;
        }
        lastNumber = number; // Store the current number for the next iteration
        isFirstNumber = false;
    }
    
    // If there's only one number, return it immediately
    if (!hasMoreThanOneNumber) {
        return lastNumber + " ";
    }
    
    return oss.str();
}



void Node::writeOutMessage(int dest_node, string& message, ofstream& fileStreamOut){
    ForwardingTableEntry& entry = forwardingTable[dest_node];
    if(entry.cost == INF){
        fileStreamOut << "from " << this->_id << " to " << dest_node << " cost infinite hops unreachable message " << message << endl;
    }else{
        string shortenedPath = extractNumbersExceptLast(*entry.path);
        fileStreamOut << "from " << this->_id << " to " << dest_node << " cost " << entry.cost << " hops " << shortenedPath << "message " << message << endl;
    }
}
