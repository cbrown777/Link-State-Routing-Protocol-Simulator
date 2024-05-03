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



void Topology::setNumberOfVertices(){
    this->V = nodeMap.size();
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
    setNumberOfVertices();
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



// params: topology, Node #, # of Nodes
void Topology::dijkstra(int src) {

    cout << "Calling dijkstra for src node: " << src << endl;

    // MAJOR FUNCTION: Generate (1) predecessors and (2) dist for the src Node
        // When while-loop is complete, we will assign predecessors and dist to the Node Object


    // Create a priority queue to store vertices and their distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // P[v]
    unordered_map<int, int> predecessors;

    // Create a map to store distances from source to all vertices
        // vector<int> dist(this->V, INF);
    // unordered_map<int, int> dist(this->V, INF);
    unordered_map<int, int> dist;
    for(auto it = this->nodeMap.begin(); it != nodeMap.end(); ++it){
        dist[it->first] = INF;
    }

    // Set distance from source to itself as 0
    dist[src] = 0;

    // Push the source vertex into the priority queue
        // dist, node #
    pq.push({0, src});

    // Loop until priority queue becomes empty
    while (!pq.empty()) {
        // Extract the node # with minimum distance from the priority queue
        int v_i = pq.top().second;
        pq.pop();

        // return the vector of edges for the v_i node
        Node* v_iNode = this->nodeMap[v_i];
        vector<Edge>& v_iNodeEdges = v_iNode->getEdges();

        // Iterate through all adjacent vertices of u
        for (const Edge& edge : v_iNodeEdges) {
            int w = edge.dest;
            int weight = edge.cost;

            // If a shorter path to v is found through u, update its distance
            if (dist[v_i] + weight < dist[w]) {
                dist[w] = dist[v_i] + weight;
                predecessors[w] = v_i;
                // Push the updated distance and vertex into the priority queue
                pq.push({dist[w], w});
            }

            // create tie-breaker: if a current-best-known path and newly found path are equal in cost:
			    // choose the path whose last node before the destination has the smaller ID**
            if (dist[v_i] + weight == dist[w]) {
                predecessors[w] = min(predecessors[w], v_i);
            }

        }

    }


    // return Node obj for the src
    Node* srcNode = this->nodeMap[src];

    // Now, we will assign predecessors and dist generated locally above to the src Node object
    srcNode->assignDist(dist);
    srcNode->assignPredecessors(predecessors);


    // // print out predecessors map
    // cout << "Predecessor Map: " << endl;
    // cout << "Key: \t Value: " << endl;
    // for (auto it = predecessors.begin(); it != predecessors.end(); ++it) {
    //     cout << it->first << "\t" << it->second << endl;
    // }
    // cout << "\n";

    // print out Vertex, Distance, Path
    // printSolution(dist, predecessors, V);
}







// // params: topology, Node #, # of Nodes
// void Topology::dijkstra(int src) {

//     // return Node obj for the src
//     Node* srcNode = this->nodeMap[src];   

//     // initialize containers needed for algorithm to baseline
//     srcNode->setContainersToEmpty(this->V);

//     // Set distance from source to itself as 0
//         // dist[src] = 0;
//     srcNode->setDistanceToAnotherNode(src, 0);  

//     // Push the source vertex into the priority queue
//         // node #, dist
//         // pq.push({src, 0});
//     srcNode->pushPairOnToQueue(src, 0);  


//     // Loop until priority queue becomes empty
//     while (!srcNode->isPQEmpty()) {
//         // Extract the node # with minimum distance from the priority queue

//         int v_i = pq.top().first;
//         pq.pop();

//         // Iterate through all adjacent vertices of u
//         for (const Edge& edge : adjList[v_i]) {
//             int w = edge.dest;
//             int weight = edge.cost;

//             // If a shorter path to v is found through u, update its distance
//             if (dist[v_i] + weight < dist[w]) {
//                 dist[w] = dist[v_i] + weight;
//                 predecessors[w] = v_i;
//                 // Push the updated distance and vertex into the priority queue
//                 pq.push({w, dist[w]});
//             }

//             // create tie-breaker: if a current-best-known path and newly found path are equal in cost:
// 			    // choose the path whose last node before the destination has the smaller ID**
//             if (dist[v_i] + weight == dist[w]) {
//                 predecessors[w] = min(predecessors[w], v_i);
//             }

//         }

//     }


//     // print out predecessors map
//     cout << "Predecessor Map: " << endl;
//     cout << "Key: \t Value: " << endl;
//     for (auto it = predecessors.begin(); it != predecessors.end(); ++it) {
//         cout << it->first << "\t" << it->second << endl;
//     }
//     cout << "\n";

//     // print out Vertex, Distance, Path
//     printSolution(dist, predecessors, V);
// }






// Compute Paths for Nodes

void Topology::computeShortestPaths(){
    // loop through keys of nodeMap, and pass to dijkstra to compute all shortest paths from srcNode
    for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        int srcNodeID = it->first;
        dijkstra(srcNodeID);
    }
}




void Topology::printDistAndPredecessorsForEveryNode(){
    for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        Node* node = it->second;
        node->printDist();
        node->printPredecessors();
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
