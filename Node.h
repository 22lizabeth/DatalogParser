#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<set>

using namespace std;

class Node
{
  private:
    set<int> edges;
    bool visited;
  public:
    Node(){ visited = false; };
    set<int> getEdges();
    void addEdge(int nodeID);
    bool checkIfVisited();
    bool checkForSelfDependence(int nodeID);
    void printEdges();
};

#endif
