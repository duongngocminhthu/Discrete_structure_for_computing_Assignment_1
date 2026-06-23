#include "Algo.h"

// BUILD: g++ -o main main.cpp Algo.cpp PathNode.cpp
// RUN: ./main

int main()
{
    //------------------------------------------
    // TASK 1
    //------------------------------------------
    cout << "========== TASK 1 ==========\n";

    double social[100][100] = {0};

    // Graph:
    //
    // 0--1
    // |  |
    // 3--2
    // |
    // 4
    //

    social[0][1] = social[1][0] = 1;
    social[1][2] = social[2][1] = 1;
    social[2][3] = social[3][2] = 1;
    social[3][0] = social[0][3] = 1;
    social[3][4] = social[4][3] = 1;

    PathNode *p1 = findSocialPath(social, 0, 4);

    printPath(p1);
    freePath(p1);

    //------------------------------------------
    // TASK 2
    //------------------------------------------
    cout << "\n========== TASK 2 ==========\n";

    double weightMatrix[100][100] = {0};

    int coords[100][2] = {
        {0, 0}, // 0
        {1, 0}, // 1
        {1, 1}, // 2
        {2, 1}, // 3
        {3, 2}  // 4
    };

    // GRAPH
    //
    // 0 --1--> 1 --1--> 2
    //             \       \
    //              2       1
    //               \       \
    //                -> 3 -> 4
    //

    weightMatrix[0][1] = 1;
    weightMatrix[1][2] = 1;
    weightMatrix[1][3] = 2;
    weightMatrix[2][4] = 1;
    weightMatrix[3][4] = 1;

    PathNode *p2 = findDronePath(weightMatrix,coords,0,4,2); // Euclidean

    printPath(p2);
    freePath(p2);

    //------------------------------------------
    // TASK 3
    //------------------------------------------
    cout << "\n========== TASK 3 ==========\n";

    int warehouse[100][100] = {
        {0, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 0, 0, 0},
        {0, 1, 1, 0}
    };

    PathNode *p3 =findWarehousePath(warehouse,4,4,0,0,3,3,1); // Manhattan

    printPath(p3);
    freePath(p3);

    //------------------------------------------
    // TASK 4
    //------------------------------------------
    cout << "\n========== TASK 4 ==========\n";

    int floorPlan[100][100] = {
        {0, 0, 0, 1},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    double evacuationMatrix[100][100];

    PathNode *p4 = findEvacuationPath(floorPlan,4,4,0,0,3,3,evacuationMatrix,1);

    printPath(p4);
    freePath(p4);

    return 0;
}