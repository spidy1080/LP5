#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>
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
        adj[w].push_back(v);
    }--
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
                if (!visit[adj[u][i]]) {
                    visit[adj[u][i]] = true;
                    q.push(adj[u][i]);
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

        // Process neighbors serially (not parallel)
        for (int i = 0; i < adj[u].size(); i++) {
            if (!visited[adj[u][i]]) {
                dfs_helper(adj[u][i], visited);
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