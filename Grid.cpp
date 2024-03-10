#include<bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();

const int MAX_ROW = 100;
const int MAX_COL = 100;

// Define directions: up, down, left, right
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

class Grid {
private:
    int numRows, numCols;
    vector<vector<char>> grid;

public:
    Grid(int rows, int cols) {
        numRows = rows;
        numCols = cols;
        grid.resize(rows, vector<char>(cols));
    }

    void setCell(int row, int col, char val) {
        grid[row][col] = val;
    }

    void printGrid() {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfsTraversal(int startRow, int startCol) {
        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
        queue<pair<int, int>> q;

        visited[startRow][startCol] = true;
        q.push({startRow, startCol});

        while (!q.empty()) {
            int currentRow = q.front().first;
            int currentCol = q.front().second;
            q.pop();

            cout << grid[currentRow][currentCol] << " ";

            for (int i = 0; i < 4; ++i) {
                int newRow = currentRow + dr[i];
                int newCol = currentCol + dc[i];
                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                    grid[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
    }
     void dijkstra(int startRow, int startCol) {
        vector<vector<int>> dist(numRows, vector<int>(numCols, INF));
        dist[startRow][startCol] = 0;

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({0, {startRow, startCol}});

        while (!pq.empty()) {
            int uRow = pq.top().second.first;
            int uCol = pq.top().second.second;
            int uDist = pq.top().first;
            pq.pop();

            if (dist[uRow][uCol] < uDist) {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                int newRow = uRow + dr[i];
                int newCol = uCol + dc[i];

                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                    grid[newRow][newCol] != '#' && dist[uRow][uCol] + 1 < dist[newRow][newCol]) {
                    dist[newRow][newCol] = dist[uRow][uCol] + 1;
                    pq.push({dist[newRow][newCol], {newRow, newCol}});
                }
            }
        }

        cout << "Shortest distances from source cell (" << startRow << ", " << startCol << "):\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (dist[i][j] == INF) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    void dfsTraversal(int row, int col, vector<vector<bool>>& visited) {
        visited[row][col] = true;
        cout << grid[row][col] << " ";

        for (int i = 0; i < 4; ++i) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols &&
                grid[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                dfsTraversal(newRow, newCol, visited);
            }
        }
    }

    void dfsTraversal(int startRow, int startCol) {
        vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
        dfsTraversal(startRow, startCol, visited);
    }
};

int main() {
    Grid grid(5, 5);
    grid.setCell(0, 0, '.');
    grid.setCell(0, 1, '#');
    grid.setCell(0, 2, '.');
    grid.setCell(0, 3, '.');
    grid.setCell(0, 4, '.');
    grid.setCell(1, 0, '.');
    grid.setCell(1, 1, '.');
    grid.setCell(1, 2, '#');
    grid.setCell(1, 3, '#');
    grid.setCell(1, 4, '.');
    grid.setCell(2, 0, '.');
    grid.setCell(2, 1, '.');
    grid.setCell(2, 2, '.');
    grid.setCell(2, 3, '#');
    grid.setCell(2, 4, '.');
    grid.setCell(3, 0, '.');
    grid.setCell(3, 1, '#');
    grid.setCell(3, 2, '.');
    grid.setCell(3, 3, '.');
    grid.setCell(3, 4, '#');
    grid.setCell(4, 0, '.');
    grid.setCell(4, 1, '.');
    grid.setCell(4, 2, '.');
    grid.setCell(4, 3, '#');
    grid.setCell(4, 4, '.');

    cout << "Grid:" << endl;
    grid.printGrid();

    cout << "BFS Traversal: ";
    grid.bfsTraversal(0, 0);
    cout << endl;

    cout << "DFS Traversal: ";
    grid.dfsTraversal(0, 0);
    cout << endl;
    cout << "DIJKSTRA : ";
    grid.dijkstra(0, 0);
    return 0;
}
