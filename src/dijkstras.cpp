#include "dijkstras.h" 

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    const int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > distances[u]) continue;

        for (const Edge& e : G[u]) {
            int new_dist = distances[u] + e.weight;
            if (new_dist < distances[e.dst]) {
                distances[e.dst] = new_dist;
                previous[e.dst] = u;
                pq.emplace(new_dist, e.dst);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path;

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}