#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

vector<vector<int>> g;
vector<bool> visited;

void bfs(int start) {

    queue<int> q;

    visited.assign(g.size(), false);

    visited[start] = true;

    q.push(start);

    cout << "BFS: ";

    while (!q.empty()) {

        int node = q.front();

        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < g[node].size(); i++) {

            int neigh = g[node][i];

            if (!visited[neigh]) {

                #pragma omp critical
                {
                    if (!visited[neigh]) {

                        visited[neigh] = true;

                        q.push(neigh);
                    }
                }
            }
        }
    }

    cout << endl;
}

void dfs(int node) {

    cout << node << " ";

    visited[node] = true;

    #pragma omp parallel for
    for (int i = 0; i < g[node].size(); i++) {

        int neigh = g[node][i];

        if (!visited[neigh]) {

            #pragma omp critical
            {
                if (!visited[neigh]) {

                    dfs(neigh);
                }
            }
        }
    }
}

int main() {

    int n = 6;

    g.resize(n);

    g[0] = {1, 2};
    g[1] = {0, 3, 4};
    g[2] = {0, 5};
    g[3] = {1};
    g[4] = {1};
    g[5] = {2};

    bfs(0);

    visited.assign(n, false);

    cout << "DFS: ";

    dfs(0);

    return 0;
}
