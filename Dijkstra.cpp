#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// dijkstra algo to find shortest path
void dijkstra(vector<vector<pair<int,int>>> &graph, int start, int end) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    // loop for each node
    for (int i = 0; i < n; i++) {
        // find node with min distance not visited yet
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1) break; // no node left
        visited[u] = true;

        // update neighbers
        for (auto edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }

    if (dist[end] == INT_MAX) {
        cout << "no path exist\n";
        return;
    }

    // build path backwards
    vector<int> path;
    for (int v = end; v != -1; v = prev[v]) {
        path.push_back(v);
    }

    cout << "shortest path: ";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << char('M' + path[i]);
        if (i > 0) cout << " -> ";
    }
    cout << "\ncost: " << dist[end] << endl;
}

int main() {
    // graph with 4 nodes: M=0, N=1, O=2, P=3
    vector<vector<pair<int,int>>> graph(4);
    graph[0] = {{1,5}, {2,1}};      // M
    graph[1] = {{0,5}, {2,2}, {3,3}}; // N
    graph[2] = {{0,1}, {1,2}, {3,7}}; // O
    graph[3] = {{1,3}, {2,7}};        // P

    char s, e;
    cout << "enter start node (M/N/O/P): ";
    cin >> s;
    cout << "enter end node (M/N/O/P): ";
    cin >> e;

    int start = s - 'M';
    int end = e - 'M';

    dijkstra(graph, start, end);
    return 0;
}
