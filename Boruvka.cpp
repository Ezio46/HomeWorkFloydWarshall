#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int find(vector<int> &parent, int i) {
    if (parent[i] == -1) {
        return i;
    }
    return find(parent, parent[i]);
}

void unionSets(vector<int> &parent, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    parent[rootX] = rootY;
}

class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class Graph {
public:
    int vertices;
    vector<Edge> edges;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    vector<Edge> boruvka();
};

Graph::Graph(int vertices) : vertices(vertices) {}

void Graph::addEdge(int src, int dest, int weight) {
    edges.emplace_back(src, dest, weight);
}

vector<Edge> Graph::boruvka() {
    vector<Edge> result;
    vector<int> parent(vertices, -1);
    vector<int> cheapest(vertices, -1);

    while (true) {
        
        for (const Edge &edge : edges) {
            int set1 = find(parent, edge.src);
            int set2 = find(parent, edge.dest);

            if (set1 != set2) {
                if (cheapest[set1] == -1 || edge.weight < edges[cheapest[set1]].weight) {
                    cheapest[set1] = edge.dest;
                }

                if (cheapest[set2] == -1 || edge.weight < edges[cheapest[set2]].weight) {
                    cheapest[set2] = edge.dest;
                }
            }
        }

        for (int i = 0; i < vertices; i++) {
            if (cheapest[i] != -1) {
                int set1 = find(parent, i);
                int set2 = find(parent, cheapest[i]);

                if (set1 != set2) {
                    result.emplace_back(i, cheapest[i], edges[cheapest[i]].weight);
                    unionSets(parent, set1, set2);
                }

                cheapest[i] = -1;
            }
        }

        int numTrees = 0;
        for (int i = 0; i < vertices; i++) {
            if (parent[i] == -1) {
                numTrees++;
            }
        }

        if (numTrees == 1) {
            break;
        }
    }

    return result;
}

int main() {
    Graph g(8);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 4);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(5, 4, 1);
    g.addEdge(6, 5, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(6, 7, 1);

    vector<Edge> result = g.boruvka();

    cout << "Minimum spanning tree edges:" << endl;
    for (const Edge &edge : result) {
        cout << edge.src << " -- " << edge.dest << " Weight: " << edge.weight << endl;
    }

    return 0;
}
