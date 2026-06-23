#include "Algo.h"

// TASK 1
PathNode* aStarShortestPath(double adjMatrix[100][100], double heuristic[100],int n,int startPerson,int goalPerson){
    double g[100];
    double f[100];

    bool closed[100];
    vector<int> openSet;
    int parent[100];

    for(int i = 0; i < n; i++){
        g[i] = INFINITY;
        f[i] = INFINITY;
        closed[i] = false;
        parent[i] = -1;
    }

    g[startPerson] = 0;
    f[startPerson] = heuristic[startPerson];

    openSet.push_back(startPerson);

    while(!openSet.empty()){

        int current = -1;
        int currentIndex = -1;

        for(int i = 0; i < openSet.size(); i++){

            int node = openSet[i];

            if(current == -1 || f[node] < f[current] ||
              (f[node] == f[current] && heuristic[node] < heuristic[current]) ||
              (f[node] == f[current] && heuristic[node] == heuristic[current] && node < current))
            {
                current = node;
                currentIndex = i;
            }
        }

        openSet.erase(openSet.begin() + currentIndex);
       
        if(current == goalPerson){

            vector<int> path;

            int temp = current;

            while(temp != -1){
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;

            for(int i = 0; i < path.size(); i++){

                PathNode* newNode = new PathNode;

                newNode->name = to_string(path[i]);
                newNode->g = g[path[i]];
                newNode->h = heuristic[path[i]];
                newNode->f = f[path[i]];
                newNode->next = nullptr;

                if(head == nullptr){
                    head = newNode;
                    tail = newNode;
                }
                else{
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            return head;
        }

         closed[current] = true;

        for(int neighbor = 0; neighbor < n; neighbor++){

            if(adjMatrix[current][neighbor] == 0)
                continue;

            if(closed[neighbor])
                continue;

            double tentativeG = g[current] + 1;

            bool inOpen = false;

            for(int i = 0; i < openSet.size(); i++){
                if(openSet[i] == neighbor){
                    inOpen = true;
                    break;
                }
            }

            if(tentativeG < g[neighbor]){

                parent[neighbor] = current;
                g[neighbor] = tentativeG;
                f[neighbor] = g[neighbor] + heuristic[neighbor];

                if(!inOpen){
                    openSet.push_back(neighbor);
                }
            }
        }
    }

    return nullptr;
}

void computeMinStepsTogoalPerson(double adjMatrix[100][100], int n, int goal, double heuristic[100]){
    for(int i = 0; i < n; i++){
        heuristic[i] = INFINITY;
    }

    heuristic[goal] = 0;

    vector<int> queue;
    queue.push_back(goal);

    while(!queue.empty()){

        int current = queue.front();
        queue.erase(queue.begin());

        for(int i = 0; i < n; i++){

            if(adjMatrix[i][current] > 0 &&
               heuristic[i] == INFINITY)
            {
                heuristic[i] = heuristic[current] + 1;
                queue.push_back(i);
            }
        }
    }
}

PathNode *findSocialPath(double adjMatrix[100][100],int startPerson,int goalPerson){
    
    double heuristic[100];
    int n = 0;

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(adjMatrix[i][j] != 0){
                n = max(n, max(i, j) + 1);
            }
        }
    }

    n = max(n, max(startPerson, goalPerson) + 1);

    computeMinStepsTogoalPerson(adjMatrix,n,goalPerson,heuristic);

    return aStarShortestPath(adjMatrix,heuristic,n,startPerson,goalPerson);
}

// TASK 2
PathNode *findDronePath(double weightMatrix[100][100], int coords[100][2],int startPoint, int goalPoint, int mode){
    double heuristic[100];
    const double EPS = 1e-9;
    int n = 0;

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){

            if(weightMatrix[i][j] != 0){
                n = max(n, max(i, j) + 1);
            }
        }
    }

    n = max(n, max(startPoint, goalPoint) + 1);

    for(int i = 0; i < n; i++) {
        int x1 = coords[i][0];
        int y1 = coords[i][1];

        int x2 = coords[goalPoint][0];
        int y2 = coords[goalPoint][1];

        if(mode == 1) {
            // Manhattan
            heuristic[i] = abs(x1 - x2) + abs(y1 - y2);
        }

        else if(mode == 2) {
            // Euclidean
            heuristic[i] = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        }

        else if(mode == 3) {
            // Chebyshev
            heuristic[i] = max(abs(x1 - x2), abs(y1 - y2));
        }

        else {
            heuristic[i] = 0;
        }
    }

    double g[100];
    double f[100];

    bool closed[100];
    vector<int> openSet;
    int parent[100];

    for(int i = 0; i < n; i++){
        g[i] = INFINITY;
        f[i] = INFINITY;
        closed[i] = false;
        parent[i] = -1;
    }

    g[startPoint] = 0;
    f[startPoint] = heuristic[startPoint];

    openSet.push_back(startPoint);

    while(!openSet.empty()){

        int current = -1;
        int currentIndex = -1;

        for(int i = 0; i < openSet.size(); i++){

            int node = openSet[i];

            if(current == -1 ||
            f[node] < f[current] ||
            (abs(f[node] - f[current]) < EPS &&
                heuristic[node] < heuristic[current]) ||
            (abs(f[node] - f[current]) < EPS &&
                heuristic[node] == heuristic[current] &&
                node < current))
            {
                current = node;
                currentIndex = i;
            }
        }

        openSet.erase(openSet.begin() + currentIndex);
       
        if(current == goalPoint){

            vector<int> path;

            int temp = current;

            while(temp != -1){
                path.push_back(temp);
                temp = parent[temp];
            }

            reverse(path.begin(), path.end());

            PathNode* head = nullptr;
            PathNode* tail = nullptr;

            for(int i = 0; i < path.size(); i++){

                PathNode* newNode = new PathNode;

                newNode->name = "(" + to_string(coords[path[i]][0]) + "," + to_string(coords[path[i]][1]) + ")"; // (1,1)
                newNode->g = g[path[i]];
                newNode->h = heuristic[path[i]];
                newNode->f = f[path[i]];
                newNode->next = nullptr;

                if(head == nullptr){
                    head = newNode;
                    tail = newNode;
                }
                else{
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            return head;
        }

         closed[current] = true;

        for(int neighbor = 0; neighbor < n; neighbor++){

            if(weightMatrix[current][neighbor] == 0)
                continue;

            if(closed[neighbor])
                continue;

            double tentativeG = g[current] + weightMatrix[current][neighbor];

            bool inOpen = false;

            for(int i = 0; i < openSet.size(); i++){
                if(openSet[i] == neighbor){
                    inOpen = true;
                    break;
                }
            }

            if(tentativeG < g[neighbor]){

                parent[neighbor] = current;
                g[neighbor] = tentativeG;
                f[neighbor] = g[neighbor] + heuristic[neighbor];

                if(!inOpen){
                    openSet.push_back(neighbor);
                }
            }
        }
    }

    return nullptr;
}

// TASK 3
double heuristicOfNode(int currentX, int currentY, int goalX, int goalY, int mode){
    int heuristic;
    if(mode == 1){
        //Manhattan
        heuristic = abs(currentX - goalX) + abs(currentY - goalY);
    }
    else{
        //Chebyshev
        heuristic = max(abs(currentX - goalX), abs(currentY - goalY));
    }
    return heuristic;
}

PathNode *findWarehousePath(int warehouse[100][100], int m, int n, int startX, int startY, int goalX, int goalY, int mode){
    int dx[8] = {
    -1,  1,  0,  0,
    -1, -1,  1,  1
    };

    int dy[8] = {
        0,  0, -1,  1,
        -1,  1, -1,  1
    };

    string dirName[8] = {
    "Up",
    "Down",
    "Left",
    "Right",
    "Up-Left",
    "Up-Right",
    "Down-Left",
    "Down-Right"
    };

    double g[100][100];
    double h[100][100];
    double f[100][100];

    bool closed[100][100];

    int parentX[100][100];
    int parentY[100][100];
    string parentDir[100][100];

    vector<pair<int,int>> openSet;

    for(int i = 0; i < m; i++) {

        for(int j = 0; j < n; j++) {

            g[i][j] = INFINITY;
            f[i][j] = INFINITY;

            closed[i][j] = false;

            parentX[i][j] = -1;
            parentY[i][j] = -1;
        }
    }

    g[startX][startY] = 0;
    f[startX][startY] = heuristicOfNode(startX,startY,goalX,goalY,mode);

    openSet.push_back({startX,startY});

    while(!openSet.empty()){

        int x = -1;
        int y = -1;
        int index = -1;

        for(int i = 0; i < openSet.size(); i++){
            if((x == -1 && y == -1) || f[openSet[i].first][openSet[i].second] < f[x][y]){
                x = openSet[i].first;
                y = openSet[i].second;
                index = i;
            }
        }
    
        openSet.erase(openSet.begin() + index);

        if(x == goalX && y == goalY){

            PathNode* head = nullptr;

            int cx = goalX;
            int cy = goalY;

            while(!(cx == startX && cy == startY)) {

                PathNode* newNode = new PathNode;

                newNode->name = parentDir[cx][cy];

                newNode->g = g[cx][cy];
                newNode->h = heuristicOfNode(cx,cy,goalX,goalY,mode);
                newNode->f = f[cx][cy];

                newNode->next = head;
                head = newNode;

                int px = parentX[cx][cy];
                int py = parentY[cx][cy];

                cx = px;
                cy = py;
            }

            return head;
        }

        closed[x][y] = true;

        for(int dir = 0; dir < 8; dir++) {

            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

            if(warehouse[nx][ny] == 1) continue;

            if(closed[nx][ny]) continue;

            double moveCost;

            if(dir < 4)
                moveCost = 1;
            else
                moveCost = 1.5;

            double tentativeG = g[x][y] + moveCost;

            if(tentativeG < g[nx][ny]) {

                parentX[nx][ny] = x;
                parentY[nx][ny] = y;

                parentDir[nx][ny] = dirName[dir];

                g[nx][ny] = tentativeG;

                f[nx][ny] = g[nx][ny] + heuristicOfNode(nx,ny,goalX,goalY,mode);

                bool inOpen = false;

                for(int i = 0;i < openSet.size();i++) {

                    if(openSet[i].first == nx && openSet[i].second == ny) {
                        inOpen = true;
                        break;
                    }
                }

                if(!inOpen) {
                    openSet.push_back({nx, ny});
                }
            }
        }
   }
   return nullptr;
}

// TASK 4
void buildWeightMatrix(int floorPlan[100][100],int m,int n,double weightMatrix[100][100]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            weightMatrix[i][j] = 0;
        }
    }
    
    int dx[8] = {-1,1,0,0,-1,-1,1,1};
    int dy[8] = {0,0,-1,1,-1,1,-1,1};

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (floorPlan[i][j] == 1) continue;

            int u = i * n + j;

            for (int k = 0; k < 8; k++){
                int ni = i + dx[k];
                int nj = j + dy[k];

                if (ni >= 0 && ni < m &&
                    nj >= 0 && nj < n &&
                    floorPlan[ni][nj] == 0){
                    int v = ni * n + nj;

                    double cost;

                    if (k < 4)
                        cost = 1;
                    else
                        cost = 1.5;

                    weightMatrix[u][v] = cost;
                }
            }
        }
    }
}

double heuristic(int x1, int y1, int x2, int y2, int mode){
    if (mode == 1){
        // Manhattan
        return abs(x1 - x2) + abs(y1 - y2);
    }
    else{
        // Chebyshev
        return max(abs(x1 - x2), abs(y1 - y2));
    }
}

PathNode *findEvacuationPath(int floorPlan[100][100], int m, int n, int startX, int startY,int exitX,int exitY,double weightMatrix[100][100],int mode){
    
    if(floorPlan[startX][startY] == 1 ||floorPlan[exitX][exitY] == 1) return nullptr;

    buildWeightMatrix(floorPlan,m,n,weightMatrix);

    int totalVertices = m * n;

    double g[10000];
    double h[10000];
    double f[10000];

    bool closed[10000];

    int parent[10000];

    vector<int> openSet;

    for(int i = 0; i < totalVertices; i++) {

        g[i] = INFINITY;
        h[i] = INFINITY;
        f[i] = INFINITY;

        closed[i] = false;

        parent[i] = -1;
    }

    int startVertex = startX * n + startY;

    int goalVertex = exitX * n + exitY;

    g[startVertex] = 0;

    h[startVertex] = heuristic(startX,startY,exitX,exitY,mode);

    f[startVertex] = g[startVertex] + h[startVertex];

    openSet.push_back(startVertex);

    while(!openSet.empty()) {

        int u = -1;
        int index = -1;

        for(int i = 0;i < openSet.size();i++) {
            if(u == -1 || f[openSet[i]] < f[u] ||
               (f[openSet[i]] == f[u] && openSet[i] < u)) {
                u = openSet[i];
                index = i;
            }
        }

        openSet.erase(openSet.begin() + index);

        closed[u] = true;

        int x = u / n;
        int y = u % n;

        if(u == goalVertex) {

            PathNode* head = nullptr;

            int cur = goalVertex;

            while(cur != -1) {

                int cx = cur / n;
                int cy = cur % n;

                PathNode* newNode = new PathNode;

                newNode->name =
                "(" +
                to_string(cx) +
                ", " +
                to_string(cy) +
                ")";

                newNode->g = g[cur];

                newNode->h = heuristic(cx,cy,exitX,exitY,mode);

                newNode->f = f[cur];

                newNode->next = head;
                head = newNode;

                cur = parent[cur];
            }

            return head;
        }

        for(int v = 0; v < totalVertices; v++) {

            if(weightMatrix[u][v] <= 0) continue;

            if(closed[v]) continue;

            double moveCost = weightMatrix[u][v];

            double tentativeG = g[u] + moveCost;

            if(tentativeG < g[v]) {

                parent[v] = u;

                g[v] = tentativeG;

                int vx = v / n;
                int vy = v % n;

                h[v] = heuristic(vx,vy,exitX,exitY,mode);

                f[v] = g[v] + h[v];

                openSet.push_back(v);
            }
        }
    }

    return nullptr;
}