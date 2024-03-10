#include<bits/stdc++.h>
using namespace std;
const int INF = numeric_limits<int>::max(); // Define infinity as the maximum value for int

class GraphAdjMatrix {
private:
    int numVertices;
    vector<vector<int>> adjMatrix; // 2D vector to represent the adjacency matrix

    // Function to find the parent of a vertex in a disjoint set
    int findParent(int vertex, vector<int>& parent) {
        if (parent[vertex] != vertex) {
            parent[vertex] = findParent(parent[vertex], parent); // Path compression
        }
        return parent[vertex];
    }

    // Utility function for depth-first search traversal
    void dfsUtil(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        // Traverse all vertices adjacent to the current vertex
        for (int i = 1; i <= numVertices; ++i) {
            if (adjMatrix[vertex][i] != INF && !visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }

public:
    // Constructor to initialize the graph with a given number of vertices
    GraphAdjMatrix(int vertices) {
        numVertices = vertices;
        // Initialize the adjacency matrix with all weights set to infinity
        adjMatrix.resize(vertices + 1, vector<int>(vertices + 1, INF));
    }

    // Function to add an edge between two vertices with a given weight
    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight; // Undirected graph, so set both directions
    }

    // Breadth-first search traversal of the graph starting from a given vertex
    void bfsTraversal(int startVertex) {
        vector<bool> visited(numVertices + 1, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            cout << currentVertex << " ";
            q.pop();

            // Visit all vertices adjacent to the current vertex
            for (int i = 1; i <= numVertices; ++i) {
                if (adjMatrix[currentVertex][i] != INF && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    // Dijkstra's algorithm to find the shortest paths from a source vertex
    void dijkstra(int src) {
        vector<bool> visited(numVertices + 1, false);
        vector<int> dist(numVertices + 1, INF);
        dist[src] = 0;

        for (int count = 0; count < numVertices; ++count) {
            int u = -1;
            for (int i = 1; i <= numVertices; ++i) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }

            visited[u] = true;
            for (int v = 1; v <= numVertices; ++v) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        // Print the shortest distances from the source vertex
        cout << "Shortest distances from source vertex " << src << ":\n";
        for (int i = 1; i <= numVertices; ++i) {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }

    // Depth-first search traversal of the graph starting from a given vertex
    void dfsTraversal(int startVertex) {
        vector<bool> visited(numVertices + 1, false);
        dfsUtil(startVertex, visited);
    }

    // Prim's algorithm to find the minimum spanning tree of the graph
    void prim() {
        vector<bool> visited(numVertices + 1, false);
        vector<int> parent(numVertices + 1, -1);
        vector<int> key(numVertices + 1, INF);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int src = 1; // Start from vertex 1
        pq.push({0, src});
        key[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            visited[u] = true;

            for (int v = 1; v <= numVertices; ++v) {
                if (!visited[v] && adjMatrix[u][v] != INF && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                    pq.push({key[v], v});
                }
            }
        }

        // Print the edges of the minimum spanning tree (Prim's Algorithm)
        cout << "Edges in the Minimum Spanning Tree (Prim's Algorithm):\n";
        for (int i = 2; i <= numVertices; ++i) {
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << adjMatrix[parent[i]][i] << endl;
        }
    }

    // Kruskal's algorithm to find the minimum spanning tree of the graph
    void kruskal() {
        vector<pair<int, pair<int, int>>> edges;

        // Populate the edges vector with the edges of the graph
        for (int u = 1; u <= numVertices; ++u) {
            for (int v = u + 1; v <= numVertices; ++v) { // Consider each edge only once
                if (adjMatrix[u][v] != INF) {
                    edges.push_back({adjMatrix[u][v], {u, v}});
                }
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end());

        vector<int> parent(numVertices + 1);
        for (int i = 1; i <= numVertices; ++i) {
            parent[i] = i;
        }

        // Print the edges of the minimum spanning tree (Kruskal's Algorithm)
        cout << "Edges in the Minimum Spanning Tree (Kruskal's Algorithm):\n";
        for (auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int weight = edge.first;

            int parentU = findParent(u, parent);
            int parentV = findParent(v, parent);

            if (parentU != parentV) {
                cout << "Edge: " << u << " - " << v << " Weight: " << weight << endl;
                parent[parentU] = parentV;
            }
        }
    }
};

int main() {
    GraphAdjMatrix graph(5); // Create a graph with 5 vertices

    // Add edges to the graph with their weights
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 20);
    graph.addEdge(1, 5, 1);
    graph.addEdge(2, 4, 50);
    graph.addEdge(3, 5, 40);
    graph.addEdge(2, 5, 80);

    // Perform BFS traversal starting from vertex 1
    cout << "BFS Traversal using Adjacency Matrix: ";
    graph.bfsTraversal(1);
    cout << endl;

    // Perform DFS traversal starting from vertex 1
    cout << "DFS Traversal using Adjacency Matrix: ";
    graph.dfsTraversal(1);
    cout << endl;

    // Apply Dijkstra's algorithm to find shortest paths from vertex 1
    graph.dijkstra(1);
    cout << endl;

    // Apply Prim's algorithm to find the minimum spanning tree
    graph.prim();
    cout << endl;

    // Apply Kruskal's algorithm to find the minimum spanning tree
    graph.kruskal();

    return 0;
}
