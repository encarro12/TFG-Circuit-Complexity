#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Number of vertices of the graph
const int V = 5;

float equanimity(string f) {
    int I = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 0; j < pow(2, 5); j += pow(2, i))
            for (int k = 0; k < pow(2, i - 1); k++)
                if (f[k + j] != f[(k + j) + pow(2, i - 1)])
                    I++;
    return (I + 0.0) / (5 * 16);
}

/*

*/
bool is_clique(const vector<vector<int>>& G, const int k, vector<int>& subgraph) {
    // Run a loop for all set of edges
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++)
            // If any edge is missing
            if (G[subgraph[i]][subgraph[j]] == 0)
                return false;
    }
    return true;
}

/*
    i : Last vertex added to form a clique
    l : Size of current clique
    G : Adjacency matrix's lower triangular
*/
int max_clique(const vector<vector<int>> & G, vector<int> & subgraph, const int i, const int l) {
    // Maximal clique size
    int k = 0; 
    // Check if any vertices from i+1 can be inserted
    for (int j = i + 1; j <= V; j++) {
        subgraph[l] = j;
        // If the subgraph is not a clique of size l + 1 then
        // it cannot be a clique by adding another vertex
        if (is_clique(l + 1, subgraph)) {
            // Update max
            k = max(k, l + 1);
            // Check if another vertex can be added
            k = max(k, max_clique(G, subgraph, j, l + 1)
        }
    }
    return k;
}

int main() {
    int edges[][2] = { { 1, 2 }, { 2, 3 }, { 3, 1 },
                       { 4, 3 }, { 4, 1 }, { 4, 2 } };

    int size = sizeof(edges) / sizeof(edges[0]);
    n = 4;

    vector<vector<int>(4, 0)>(4) G;
    vector<int>(4, 0) subgraph;

    for (int i = 0; i < size; i++) {
        G[edges[i][0]][edges[i][1]] = 1;
        G[edges[i][1]][edges[i][0]] = 1;
    }

    cout << max_clique(G, subgraph, 0, 0);

    system("pause");
    return 0;
}