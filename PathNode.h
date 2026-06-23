#ifndef PATHNODE_H
#define PATHNODE_H

#include <string>

struct PathNode
{
    std::string name; // node label (e.g. vertex name)
    double f;         // total estimated cost (for A*)
    double g;         // actual cost from start
    double h;         // heuristic estimate to goal
    PathNode *next;   // pointer to next node in the path
};

void printPath(PathNode *head);
void freePath(PathNode *head);

#endif