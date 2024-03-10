#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class GraphAdjList {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;

public:
    GraphAdjList(int vertices) {
        numVertices = vertices + 1; // Adjusting for one-based indexing
        adjList.resize(numVertices);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight});
    }

    // Breadth-first search traversal
    void bfsTraversal(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            cout << currentVertex << " "; // Print the current vertex
            q.pop();

            for (auto& neighbor : adjList[currentVertex]) {
                int neighborVertex = neighbor.first;
                if (!visited[neighborVertex]) {
                    visited[neighborVertex] = true;
                    q.push(neighborVertex);
                }
            }
        }
    }

    // Depth-first search traversal
    void dfsTraversal(int startVertex) {
        vector<bool> visited(numVertices, false);
        dfsUtil(startVertex, visited);
    }

    // Depth-first search utility function
    void dfsUtil(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " "; // Print the current vertex

        for (auto& neighbor : adjList[vertex]) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                dfsUtil(neighborVertex, visited);
            }
        }
    }

    // Prim's algorithm to find minimum spanning tree
    void prim() {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        vector<int> key(numVertices, INT_MAX);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int src = 1; // Start from vertex 1
        pq.push({0, src});
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            visited[u] = true;

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }

        // Print the minimum spanning tree
        cout << "Edges in the Minimum Spanning Tree (Prim's Algorithm):\n";
        for (int i = 2; i < numVertices; ++i) {
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << endl;
        }
    }

    // Kruskal's algorithm to find minimum spanning tree
    void kruskal() {
        vector<pair<int, pair<int, int>>> edges;

        // Populate edges vector
        for (int u = 1; u < numVertices; ++u) {
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                edges.push_back({weight, {u, v}});
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end());

        vector<int> parent(numVertices);
        for (int i = 1; i < numVertices; ++i) {
            parent[i] = i;
        }

        int mstWeight = 0;
        cout << "Edges in the Minimum Spanning Tree (Kruskal's Algorithm):\n";
        for (auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int weight = edge.first;

            int parentU = findParent(u, parent);
            int parentV = findParent(v, parent);

            if (parentU != parentV) {
                cout << "Edge: " << u << " - " << v << " Weight: " << weight << endl;
                mstWeight += weight;
                parent[parentU] = parentV;
            }
        }
    }

private:
    int findParent(int vertex, vector<int>& parent) {
        if (parent[vertex] != vertex) {
            parent[vertex] = findParent(parent[vertex], parent);
        }
        return parent[vertex];
    }
};

int main() {
    GraphAdjList graph(5); // Create a graph with 5 vertices

    // Add edges to the graph
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 5, 6);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 5, 8);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 5, 7);
    graph.addEdge(4, 5, 9);

    // Perform BFS traversal starting from vertex 1
    cout << "BFS Traversal using Adjacency List: ";
    graph.bfsTraversal(1);
    cout << endl;

    // Perform DFS traversal starting from vertex 1
    cout << "DFS Traversal using Adjacency List: ";
    graph.dfsTraversal(1);
    cout << endl;

    // Apply Prim's algorithm to find the minimum spanning tree
    graph.prim();
    cout << endl;

    // Apply Kruskal's algorithm to find the minimum spanning tree
    graph.kruskal();

    return 0;
}
