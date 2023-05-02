#include "Graph.h"

Graph::Graph(){
    for(int i = 0; i < MAX; i++){
        vertices[i].name = "";
        vertices[i].head_edge = nullptr;
    }
}

void Graph::addVertex(const string& vertex){
    int index = hash(vertex);
    int index2 = hash2(vertex);

    for(int i = 1; i < MAX; i++){
        if(vertices[index].name == ""){
                vertices[index].name = vertex;
                return;
        }
        else{
            index = (index + (i*index2)) % MAX;
        }
    }
}

unsigned int Graph::hash(const string & word){
        unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return key % MAX;
}

unsigned int Graph::hash2(const string & word){
    unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return 13 - (key % 13);
}


int Graph::findVertex(const string& vertex){
    int index = hash(vertex);
    int index2 = hash2(vertex);

    for(int i = 1; i < MAX; i++){
        if(vertices[index].name == ""){
            return -1;
        }
        if(vertices[index].name == vertex){return index;}
        else{index = (index + (i*index2))%MAX;}
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
    return -1;
    }
    int end_index = findVertex(end_vertex);
    if (end_index == -1) {
    return -1;
    }
    int dist[MAX];
    bool visited[MAX];
    int prev[MAX];
    for (int i = 0; i < MAX; i++) {
        dist[i] = INFINITY;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[start_index] = 0;

    MinHeap min_heap(MAX);
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
            if (new_dist < dist[dest_index]) {
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
        for (int i = 0; i < MAX; i++) {
        cout << "Vertex " << vertices[i].name << ": ";
        Edge* curr_edge = vertices[i].head_edge;
        while (curr_edge != nullptr) {
            cout << "(" << vertices[i].name << ", " << vertices[curr_edge->dest_vertex].name << ", " << curr_edge->weight << ") ";
            curr_edge = curr_edge->next_edge;
        }
        cout << endl;
    }
}