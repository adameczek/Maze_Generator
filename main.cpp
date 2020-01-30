//
//  main.cpp
//  labirynth
//
//
//
//

#include <iostream>
using namespace std;
#include <time.h>       /* time */
#include <cstdlib>
#include <vector>
#include <stack>
#include <limits>

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
    cout << endl;

}

vector<vector<int> > checkForNeighbours(int x, int y, vector<vector<bool> > grid, bool printStep) {
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
    if (!neighbours.empty() && printStep) {
        cout << "Neighbours found: " << endl;
        for (int i = 0; i < neighbours.size(); i++) {
            cout << i << ". y: " << neighbours[i][0] << " x: " << neighbours[i][1] << endl;
        }
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

vector<vector<bool> > generateMaze(int width, int height, bool printStep) {
        srand (time(NULL));
        int x = 1;
        int y = 1;
        int rows = height;
        int cols = width;
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
        if (printStep) printMaze(grid);
        
        while (!visitedCells.empty()) {
            vector<vector<int>> neighbours;
            if (printStep)  {
                neighbours = checkForNeighbours(x, y, grid, true);
            } else {
                neighbours = checkForNeighbours(x, y, grid, false);
            }
            if (!neighbours.empty()) {
                int random = randomNumber(0, neighbours.size() - 1);
                if (printStep) cout << "Random neighbour: " << random << endl;
                vector<int> randomNeighbour = neighbours[random];
                makePath(randomNeighbour, grid);
                if (printStep) printMaze(grid);
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
        
        grid[0][1] = false;
        grid[rows - 1][cols - 2] = false;
        return grid;
}

void greet() {
    cout << "Witaj w programie generującym labirynty ASCII" << endl
    << "Autorzy: Adam Sawicki, Vitaliy Sklyar" << endl;
}
void showOptions() {
    cout << "Wybierz opcję: " << endl
    << "1. Wygeneruj Labirynt." << endl
    << "2. Wyjdź z programu." << endl;
}

int getWidth(){
    cout << "Podaj szerokość labiryntu (liczba nieparzysta od 21 do 201)" << endl;
    int width;
    while (!(cin >> width) || (width % 2 == 0) || ((width < 21) || (width > 201))) {
        cout << "Podaj szerokość labiryntu (liczba nieparzysta od 21 do 201)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return width;
}
int getHeight(){
    cout << "Podaj dlugość labiryntu (liczba nieparzysta od 11 do 101)" << endl;
    int height;
    while (!(cin >> height) || (height % 2 == 0) || ((height < 11) || (height > 201))) {
        cout << "Podaj dlugosc labiryntu (liczba nieparzysta od 21 do 101)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return height;
}


int main(int argc, const char * argv[]) {
    int rows;
    int cols;
    bool loop = true;
    int option;
    greet();
    while (loop) {
        showOptions();
        while (!(cin >> option) || ((option != 1) && (option != 2))) {
            showOptions();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (option) {
            case 1: {
                cols = getWidth();
                rows = getHeight();
                bool printStep;
                int stepOption;
                vector<vector<bool> > grid(rows, vector<bool>(cols));
                cout << "Czy wyświetlać kroki?" << endl
                << "1. Tak." << endl
                << "2. Nie." << endl;
                while (!(cin >> stepOption) || ((option != 1) && (option != 2))) {
                    cout << "Czy wyświetlać kroki?" << endl
                    << "1. Tak." << endl
                    << "2. Nie." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (stepOption == 1) {
                    grid = generateMaze(cols, rows, true);
                } else {
                    grid = generateMaze(cols, rows, false);
                }
                printMaze(grid);
                break;
            }
            case 2: {
                loop = false;
                break;
            }
        }
    }
    return 0;
}



