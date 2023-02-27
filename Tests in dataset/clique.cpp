#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
    TODO:
        - Calcular el valor de ecuanimidad por cada tabla de verdad.
*/

// Number of vertices of the graph
const int V = 6;

/*

*/
float equanimity(const vector<int> & f) {
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
            // As subgraph /in {1,...,V} and graph /in {{0}, {0,1}, {0,1,2}, ..., {0,...,V - 2}}
            // with V - 1 rows.
            if (G[subgraph[j] - 2][subgraph[i] - 1] == 0)
                return false;
    }
    return true;
}

/*
    i : Last vertex added to form a clique
    l : Size of current clique
    G : Adjacency matrix's lower triangular
*/
int max_clique(const vector<vector<int>>& G, vector<int>& subgraph, const int i, const int l) {
    // Maximal clique size
    int k = 0;
    // Check if any vertices from i+1 can be inserted
    for (int j = i + 1; j <= V; j++) {
        subgraph[l] = j;
        // If the subgraph is not a clique of size l + 1 then
        // it cannot be a clique by adding another vertex
        if (is_clique(G, l + 1, subgraph)) {
            // Update max
            k = max(k, l + 1);
            // Check if another vertex can be added
            k = max(k, max_clique(G, subgraph, j, l + 1));
        }
    }
    return k;
}

/*


*/
vector<vector<int>> binary_to_graph(const vector<int> & x) {
    // Adjacency matrix's lower triangle representation of graph
    vector<vector<int>> G;
    // Number of elements in each row
    int n = 0;
    for (int i = 0; i < x.size(); i+=n) {
        vector<int> row;
        n++;
        for (int j = i; j < i + n; j++)
            row.push_back(x[j]);
        G.push_back(row);
    }
    return G;
}

/*

*/
void fill_chains(vector<int> & x, const int depth, vector<vector<int>> & chain_k) {
    // Base condition
    if (depth == x.size()) {
        vector<vector<int>> G = binary_to_graph(x);
        vector<int> subgraph(V, 0);
        int k = max_clique(G, subgraph, 0, 0);
        for (int i = 0; i < V; i++)
            chain_k[i].push_back(i + 1 <= k);
    }
    // Recursive conditions
    else {
        x[depth] = 1;
        fill_chains(x, depth + 1, chain_k);
        x[depth] = 0;
        fill_chains(x, depth + 1, chain_k);
    }
}

int main() {
    vector<int> x(15);
    vector<vector<int>> chain_k(V);
    fill_chains(x, 0, chain_k);
    system("pause");
    return 0;
}