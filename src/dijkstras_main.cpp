#include "dijkstras.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input graph file>" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    int source, destination;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter destination vertex: ";
    cin >> destination;
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    vector<int> path = extract_shortest_path(distances, previous, destination);
    if (path.empty()) {
        cout << "No path exists from " << source << " to " << destination << "." << endl;
    } else {
        int total_weight = distances[destination];
        print_path(path, total_weight);
    }
    
    return 0;
}
