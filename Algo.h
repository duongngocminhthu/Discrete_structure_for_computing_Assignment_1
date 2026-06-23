#ifndef ALGO_H
#define ALGO_H

#include "PathNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// TASK 1
PathNode *aStarShortestPath(double adjMatrix[100][100], double heuristic[100], int n, int startPerson, int goalPerson);

void computeMinStepsTogoalPerson(double adjMatrix[100][100], int n, int goalPerson, double heuristic[100]);

PathNode *findSocialPath(double adjMatrix[100][100], int startPerson, int goalPerson);

// TASK 2
PathNode *findDronePath(double adjMatrix[100][100], int coords[100][2], int startPoint, int goalPoint, int mode);

// TASK 3
PathNode *findWarehousePath(int warehouse[100][100], int m, int n, int startX, int startY, int goalX, int goalY, int mode);

// TASK 4
PathNode *findEvacuationPath(int floorPlan[100][100], int m, int n, int startX, int startY, int exitX, int exitY, double weightMatrix[100][100], int mode);
void buildWeightMatrix(int floorPlan[100][100], int m, int n, double weightMatrix[100][100]);

#endif