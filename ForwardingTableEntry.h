#ifndef FORWARDINGTABLEENTRY_H
#define FORWARDINGTABLEENTRY_H

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;


// Structure to represent a Forwarding Table Entry
struct ForwardingTableEntry{
    int dest;
    bool isReachable;
    int cost;
    int nextHop = -1;
    // unique_ptr<string> nextHop;
    //string* path;
    unique_ptr<string> path; // Using smart pointer here


};

#endif