#include "MinHeap.h"
#include <sstream>
#include <algorithm>

const int MAX = 50;

class Graph{
private:
    struct Edge {
        int dest_vertex;
        int weight;
        Edge* next_edge;
    };
    struct Vertex {
        string name;
        Edge* head_edge;
    };
    Vertex vertices[MAX];
    string path[MAX];
    int num_vertex;
public:
    Graph();
    void addVertex(const string& vertex);
    int findVertex(const string& vertex);
    void addEdge(const string& );
    int dijkstra(const string&, const string&, string[]);
    void print_graph();
};