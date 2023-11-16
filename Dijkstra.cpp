#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<pair<int, int>>> adj;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    vector<int> dijkstra(int start);
};

Graph::Graph(int vertices) : vertices(vertices) {
    adj.resize(vertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adj[src].emplace_back(dest, weight);
}

vector<int> Graph::dijkstra(int start) {
    vector<int> distance(vertices, numeric_limits<int>::max());
    distance[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distance[currentVertex]) {
            continue;
        }

        for (const auto &neighbor : adj[currentVertex]) {
            int newDistance = currentDistance + neighbor.second;

            if (newDistance < distance[neighbor.first]) {
                distance[neighbor.first] = newDistance;
                pq.push({newDistance, neighbor.first});
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

    int startVertex = 0;
    vector<int> distances = g.dijkstra(startVertex);

    cout << "Shortest distances from vertex " << startVertex << " to all other vertices:" << endl;
    for (int i = 0; i < g.vertices; ++i) {
        cout << "To vertex " << i << ": " << distances[i] << endl;
    }

    return 0;
}
