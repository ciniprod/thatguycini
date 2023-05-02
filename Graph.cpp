#include "Graph.h"

Graph::Graph(){
    num_vertex = 0;
    for(int i = 0; i < MAX; i++){
        vertices[i].name = "";
        vertices[i].head_edge = nullptr;
    }
}

void Graph::addVertex(const string& vertex){
    if(num_vertex == MAX){
        return;
    }
    vertices[num_vertex].name = vertex;
    vertices[num_vertex].head_edge = nullptr;
    num_vertex++;
}

int Graph::findVertex(const string& vertex){
    for (int i = 0; i < num_vertex; i++) {
        if (vertices[i].name == vertex) {
            return i;
        }
    }
    return -1;
}

void Graph::addEdge(const string& input){
    stringstream ss(input);
    string start, end;
    int weight;
    ss >> start >> end >> weight;

    int start_index = findVertex(start);
    int end_index = findVertex(end);

    if (start_index == -1 || end_index == -1) {
        return;
    }

    Edge* new_edge = new Edge;
    new_edge->dest_vertex = end_index;
    new_edge->weight = weight;
    new_edge->next_edge = vertices[start_index].head_edge;
    vertices[start_index].head_edge = new_edge;
}



int Graph::dijkstra(const string& start_vertex, const string& end_vertex, string path[]) {
    int start_index = findVertex(start_vertex);
    if (start_index == -1) {
    return -1; // start vertex not found
    }
    int end_index = findVertex(end_vertex);
    if (end_index == -1) {
    return -1; // end vertex not found
    }
    int dist[MAX];
    bool visited[MAX];
    int prev[MAX];
    for (int i = 0; i < num_vertex; i++) {
        dist[i] = INFINITY;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[start_index] = 0;

    MinHeap min_heap(num_vertex);
    min_heap.push(start_index);

    while (!min_heap.empty()) {
        int curr_index = min_heap.pop();
        if (visited[curr_index]) {
            continue;
        }
        
        Edge* curr_edge = vertices[curr_index].head_edge;
        while (curr_edge != nullptr) {
            int dest_index = curr_edge->dest_vertex;
            int new_dist = dist[curr_index] + curr_edge->weight;
            if (!visited[dest_index] && new_dist < dist[dest_index]) {
                dist[dest_index] = new_dist;
                prev[dest_index] = curr_index;
                min_heap.push(dest_index);
            }
            curr_edge = curr_edge->next_edge;
            visited[curr_index] = true;
        }
    }

    int path_index = 0;
    int curr_index = end_index;
    while (curr_index != start_index && prev[curr_index] != -1) {
        path[path_index++] = vertices[curr_index].name;
        curr_index = prev[curr_index];
    }
    path[path_index++] = start_vertex;
    reverse(path, path + path_index);

    return dist[end_index];
}

void Graph::print_graph(){
        for (int i = 0; i < num_vertex; i++) {
        cout << "Vertex " << vertices[i].name << ": ";
        Edge* curr_edge = vertices[i].head_edge;
        while (curr_edge != nullptr) {
            cout << "(" << vertices[i].name << ", " << vertices[curr_edge->dest_vertex].name << ", " << curr_edge->weight << ") ";
            curr_edge = curr_edge->next_edge;
        }
        cout << endl;
    }
}