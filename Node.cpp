#include "Node.h"

set<int> Node::getEdges()
{
  return edges;
}

void Node::addEdge(int nodeID)
{
  edges.insert(nodeID);
}

bool Node::checkIfVisited()
{
  if(visited)
  {
    return true;
  }
  else
  {
    visited = true;
    return false;
  }
}

bool Node::checkForSelfDependence(int nodeID)
{
  for(set<int>::iterator it = edges.begin(); it != edges.end(); it++)
  {
    if(*it == nodeID)
    {
      return true;
    }
  }

  return false;
}

void Node::printEdges()
{
  if(edges.empty())
  {
    return;
  }
  for(set<int>::iterator it = edges.begin(); it != edges.end(); it++)
  {
    cout << "R" << *it;
    it++;
    if(it == edges.end())
    {
      return;
    }
    cout << ",";
    it--;
  }
}
