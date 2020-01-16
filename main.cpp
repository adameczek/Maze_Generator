//
//  main.cpp
//  labirynth
//
//  Created by Adam on 11/12/2019.
//  Copyright © 2019 Adam. All rights reserved.
//

#include <iostream>
using namespace std;
#include <time.h>       /* time */
#include <cstdlib>
#include <vector>
#include <stack>


int randomNumber(int min, int max) {
    int randNum = min + (rand() % static_cast<int>(max - min + 1));
    return randNum;
}
void printMaze(vector<vector<bool> > grid) {
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] == true) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << " " << row << endl;
    }
}

vector<vector<int> > checkForNeighbours(int x, int y, vector<vector<bool> > grid) {
    vector<vector<int>>  neighbours;
    //top
    if (y - 2 > 0 && grid[y - 2][x] == true) {
        neighbours.push_back({y - 2, x, y - 1, x});
    }
    //bottom
    if (y + 2 < grid.size() && grid[y+2][x] == true) {
        neighbours.push_back({y + 2, x, y + 1, x});
    }
    // left
    if (x - 2 > 0 && grid[y][x - 2] == true) {
        neighbours.push_back({y, x - 2, y, x - 1});
    }
    // right
    if (x + 2 < grid[y].size() && grid[y][x + 2] == true) {
        neighbours.push_back({y, x +2, y, x + 1});
    }
    cout << "Neighbours found: " << endl;
    for (int i = 0; i < neighbours.size(); i++) {
        cout << i << ". y: " << neighbours[i][0] << " x: " << neighbours[i][1] << endl;
    }
    return neighbours;
}
void makePath(vector<int> coordinates, vector<vector<bool> >& grid) {
    int x1 = coordinates[1];
    int y1 = coordinates[0];
    int x2 = coordinates[3];
    int y2 = coordinates[2];
    grid[y1][x1] = false;
    grid[y2][x2] = false;
}

int main(int argc, const char * argv[]) {
    srand (time(NULL));
    int x = 1;
    int y = 1;
    int rows = 21;
    int cols = 81;
    stack<vector<int>> visitedCells;
    vector<vector<bool> > grid(rows, vector<bool>(cols));
    // Fill grid with walls
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            grid[row][col] = true;
        }
    }
    grid[y][x] = false;
    visitedCells.push({y, x});
    printMaze(grid);
 
    
    while (!visitedCells.empty()) {
        vector<vector<int>> neighbours = checkForNeighbours(x, y, grid);
        if (!neighbours.empty()) {
            int random = randomNumber(0, neighbours.size() - 1);
            cout << "Random number: " << random << endl;
            vector<int> randomNeighbour = neighbours[random];
            makePath(randomNeighbour, grid);
            printMaze(grid);
            x = randomNeighbour[1];
            y = randomNeighbour[0];
            visitedCells.push({y, x});
        } else {
            vector<int> cell = visitedCells.top();
            visitedCells.pop();
            x = cell[1];
            y = cell[0];
        }
    }
}



