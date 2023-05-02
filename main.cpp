#include "Graph.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
    string fname = argv[1];

    ifstream input_file(fname);

    if(!input_file){
        cout << "Error couldn't open file" << endl;
        return 1;
    }

    Graph graph;

    string start_node, end_node, query, extra_char;
    getline(input_file, query);
    istringstream iss(query);
    iss >> start_node >> end_node;
    getline(input_file, extra_char);

    graph.addVertex(start_node);
    graph.addVertex(end_node);     

    string start, end, line;
    int weight;

    while(getline(input_file, line)){
        istringstream ss(line);
        ss >> start >> end >> weight;
        graph.addVertex(start);
        graph.addVertex(end);
        graph.addEdge(line);
    }

    string path[MAX];

    int total_distance = graph.dijkstra(start_node, end_node, path);
    cout << start_node << " to " << end_node << " total distance is " << total_distance << endl;
    cout << "Path : ";
    for(int i = 0; i < MAX && !path[i].empty(); i++){
        cout << path[i] << " ";
    }

    cout << endl;



}
