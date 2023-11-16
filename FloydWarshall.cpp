#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int>> adj;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    vector<vector<int>> floydWarshall();
};

Graph::Graph(int vertices) : vertices(vertices) {
    adj.resize(vertices, vector<int>(vertices, numeric_limits<int>::max()));
    for (int i = 0; i < vertices; ++i) {
        adj[i][i] = 0;
    }
}

void Graph::addEdge(int src, int dest, int weight) {
    adj[src][dest] = weight;
}

vector<vector<int>> Graph::floydWarshall() {
    vector<vector<int>> distance = adj;

    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (distance[i][k] != numeric_limits<int>::max() &&
                    distance[k][j] != numeric_limits<int>::max() &&
                    distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    return distance;
}

int main() {
    Graph g(8);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 4);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(0, 7, 3);


    vector<vector<int>> shortestDistances = g.floydWarshall();

    cout << "Shortest distances between all pairs of vertices:" << endl;
    for (int i = 0; i < g.vertices; ++i) {
        for (int j = 0; j < g.vertices; ++j) {
            cout << "From vertex " << i << " to vertex " << j << ": ";
            if (shortestDistances[i][j] == numeric_limits<int>::max()) {
                cout << "No path" << endl;
            } else {
                cout << shortestDistances[i][j] << endl;
            }
        }
    }

    return 0;
}
