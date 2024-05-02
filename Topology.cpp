#include "Topology.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <iostream>
#include <set>

// using namespace std;
using std::cout;
using std::endl;
using std::getline;

// Constructor 
Topology::Topology() {
    cout << "Initializing Topology object... \n" << endl;
}




void Topology::addNodesToMap(int node_1, int node_2, int cost) {
    // if node_1 exists in nodeMap
        // nodeIt will be an iterator pointing to the element with key node_1 if it exists in nodeMap
        // or it will be equal to nodeMap.end() if node_1 is not found in nodeMap. 
    auto nodeIt = this->nodeMap.find(node_1);
    if (nodeIt != this->nodeMap.end()) {
        // Node node_1 exists in nodeMap
            // nodeIt->second returns a pointer to a Node object
        Node* node = nodeIt->second;

        // Check if node_2 exists as a destination in any edge
        bool node_2_found = false;

        for (auto it = node->getEdges().begin(); it != node->getEdges().end(); ++it) {
            // The *it expression dereferences the iterator it, which means it accesses the value pointed to by the iterator. 

            //Edge edge = *it;
            Edge& edge = *it;
            if (edge.dest == node_2) {
                // Node node_2 found as a destination in an existing edge
                if (cost == -999) {
                    // Delete the corresponding edge
                    node->getEdges().erase(it);
                } else {
                    // Update the cost of the edge
                    edge.cost = cost;
                }
                node_2_found = true;
                break;
            }
        }

        // if node_1 exists in nodeMap, and node_2 is NOT found in existing edges, create a new edge
        if (!node_2_found && cost != -999) {
            // Create a new Edge dynamically
            // Edge* newEdge = createEdge(node_2, cost);
            // Add the new edge to the node
            // node->addEdge(newEdge);

            // I need to add a new Edge to the node's edges vector
            Edge newEdge;
            newEdge.dest = node_2;
            newEdge.cost = cost;
            node->addEdge(newEdge);

        }

    // if node_1 does NOT exist in nodeMap
    } else {
        // Node node_1 does not exist in nodeMap, add it and create a new edge
        Node* newNode = new Node(node_1); // Create a new Node

        // I need to add a new Edge to the node's edges vector
        Edge newEdge;
        newEdge.dest = node_2;
        newEdge.cost = cost;
        newNode->addEdge(newEdge);


        // Edge* newEdge = createEdge(node_2, cost);
        // newNode->addEdge(newEdge); // Add edge to the new Node
        this->nodeMap[node_1] = newNode; // Add the new Node to nodeMap
    }
}



// Generate Set of Nodes
void Topology::updateNodes(ifstream& fileStream){

    cout << "updateNodes()... " << endl;


    int node_1, node_2, cost;
    string lineFromFile; 

    while(!fileStream.eof()){
        getline(fileStream, lineFromFile);

        // if there are other incorrect formats for a line (other than being empty, we will need to expand this condition)
        if (lineFromFile.empty()) {
            continue;
        }

        istringstream iss(lineFromFile);

        iss >> node_1 >> node_2 >> cost;


        // Output the parsed numbers
        cout << "1st print: node_1: " << node_1 << endl;
        cout << "1st print: node_2: " << node_2 << endl;
        cout << "1st print: cost: " << cost << endl;
        cout << "\n" << endl;




        // ***create nodes if they are not already present in the nodeMap, add/modify edges if they are
        addNodesToMap(node_1, node_2, cost);
        addNodesToMap(node_2, node_1, cost);






        // Output the parsed numbers
        cout << "2nd print: node_1: " << node_1 << endl;
        cout << "2nd print: node_2: " << node_2 << endl;
        cout << "2nd print: cost: " << cost << endl;
        cout << "\n" << endl;


        printNodesAndEdges(999);

        // this->nodeSet.insert(node_1);
        // this->nodeSet.insert(node_2);

    }

    cout << "nodeSet generated successfully! \n" << endl;
}





void Topology::printNodesAndEdges() {
    cout << "Printing Nodes and Edges:" << endl;
    for (const auto& pair : this->nodeMap) {
        int nodeId = pair.first;
        Node* node = pair.second;
        cout << "Node ID: " << nodeId << endl;
        cout << "Edges:" << endl;
        vector<Edge>& edges = node->getEdges();
        for (const Edge& edge : edges) {
            cout << "    Destination: " << edge.dest << ", Cost: " << edge.cost << endl;
        }
        cout << endl;
    }
}

void Topology::printNodesAndEdges(int randomInt) {
    cout << "Printing Nodes and Edges:" << endl;
    for (const auto& pair : this->nodeMap) {
        int nodeId = pair.first;
        Node* node = pair.second;
        cout << "Node ID: " << nodeId << endl;
        cout << "Edges:" << endl;
        vector<Edge>& edges = node->getEdges();
        for (const Edge& edge : edges) {
            cout << "    Destination: " << edge.dest << ", Cost: " << edge.cost << endl;
        }
        cout << endl;
    }
}








// Edge* Topology::createEdge(int dest, int cost) {
//     // Create a new Edge object dynamically using new
//     Edge* newEdge = new Edge;
//     newEdge->dest = dest;
//     newEdge->cost = cost;
//     return newEdge;
// }

// void Topology::addNodesToMap(int node_1, int node_2, int cost) {
//     // if node_1 exists in nodeMap
//         // nodeIt will be an iterator pointing to the element with key node_1 if it exists in nodeMap
//         // or it will be equal to nodeMap.end() if node_1 is not found in nodeMap. 
//     auto nodeIt = this->nodeMap.find(node_1);
//     if (nodeIt != this->nodeMap.end()) {
//         // Node node_1 exists in nodeMap
//             // nodeIt->second returns a pointer to a Node object
//         Node* node = nodeIt->second;

//         // Check if node_2 exists as a destination in any edge
//         bool node_2_found = false;
//         for (auto it = node->getEdges().begin(); it != node->getEdges().end(); ++it) {
//             Edge* edge = *it;
//             if (edge->dest == node_2) {
//                 // Node node_2 found as a destination in an existing edge
//                 if (cost == -999) {
//                     // Delete the corresponding edge
//                     delete edge;
//                     node->getEdges().erase(it);
//                 } else {
//                     // Update the cost of the edge
//                     edge->cost = cost;
//                 }
//                 node_2_found = true;
//                 break;
//             }
//         }

//         // if node_1 exists in nodeMap, and node_2 is NOT found in existing edges, create a new edge
//         if (!node_2_found && cost != -999) {
//             // Create a new Edge dynamically
//             Edge* newEdge = createEdge(node_2, cost);
//             // Add the new edge to the node
//             node->addEdge(newEdge);
//         }

//     // if node_1 does NOT exist in nodeMap
//     } else {
//         // Node node_1 does not exist in nodeMap, add it and create a new edge
//         Node* newNode = new Node(node_1); // Create a new Node
//         Edge* newEdge = createEdge(node_2, cost);
//         newNode->addEdge(newEdge); // Add edge to the new Node
//         this->nodeMap[node_1] = newNode; // Add the new Node to nodeMap
//     }
// }
