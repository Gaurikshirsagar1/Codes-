#include <iostream>      // for input-output
#include <vector>        // for dynamic array (graph)
#include <queue>         // for BFS queue
#include <omp.h>         // for OpenMP
using namespace std;

// Graph and visited array
vector<vector<int>> g;
vector<bool> visited;

// ----------- Parallel BFS -----------
void bfs(int start) {
    queue<int> q;                      // queue for BFS

    visited.assign(g.size(), false);  // mark all nodes unvisited
    visited[start] = true;            // mark start node visited
    q.push(start);                    // push start node

    cout << "BFS: ";

    while (!q.empty()) {              // run until queue is empty
        int node = q.front();         // get front node
        q.pop();                      // remove it

        cout << node << " ";          // print node

        // Parallel loop for neighbors
        #pragma omp parallel for
        for (int i = 0; i < g[node].size(); i++) {
            int neigh = g[node][i];   // get neighbor

            if (!visited[neigh]) {   // if not visited
                #pragma omp critical
                {
                    // check again inside critical (safe update)
                    if (!visited[neigh]) {
                        visited[neigh] = true;  // mark visited
                        q.push(neigh);          // add to queue
                    }
                }
            }
        }
    }
    cout << endl;
}

// ----------- Parallel DFS -----------
void dfs(int node) {
    cout << node << " ";          // print node
    visited[node] = true;         // mark visited

    // Parallel loop for neighbors
    #pragma omp parallel for
    for (int i = 0; i < g[node].size(); i++) {
        int neigh = g[node][i];   // get neighbor

        if (!visited[neigh]) {   // if not visited
            #pragma omp critical
            {
                if (!visited[neigh]) {
                    dfs(neigh);  // recursive DFS call
                }
            }
        }
    }
}

// ----------- Main Function -----------
int main() {
    int n = 6;
    g.resize(n);   // create graph with 6 nodes

    // Undirected graph (adjacency list)
    g[0] = {1, 2};
    g[1] = {0, 3, 4};
    g[2] = {0, 5};
    g[3] = {1};
    g[4] = {1};
    g[5] = {2};

    bfs(0);   // call BFS from node 0

    visited.assign(n, false);   // reset visited array

    cout << "DFS: ";
    dfs(0);   // call DFS from node 0

    return 0;
}