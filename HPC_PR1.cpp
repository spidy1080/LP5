#include <iostream>
#include <queue>
#include <vector>
#include <omp.h> // Required for parallelism
using namespace std;

class Graph {
private:
    int V;
    vector<int>* adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);  // Undirected graph
    }

    void bfs(int s) {
        vector<bool> visit(V, false);
        queue<int> q;

        visit[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int i = 0; i < adj[u].size(); i++) {
                int neighbor = adj[u][i];
                if (!visit[neighbor]) {
                    visit[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void dfs(int s) {
        vector<bool> vis(V, false);
        dfs_helper(s, vis);
    }

private:
    void dfs_helper(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";

        for (int i = 0; i < adj[u].size(); i++) {
            int neighbor = adj[u][i];
            if (!visited[neighbor]) {
                dfs_helper(neighbor, visited);
            }
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);

    cout << "BFS starting from vertex 3: ";
    g.bfs(3);
    cout << endl;

    cout << "DFS starting from vertex 5: ";
    g.dfs(5);
    cout << endl;

    return 0;
}
