#include <iostream>
#include <cmath>
#include <vector>
#include "equanimities.h"
using namespace std;

const int V = 4;
const int K = 3;

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

vector<vector<int>> binary_to_graph(const vector<int>& x) {
    // Adjacency matrix's lower triangle representation of graph
    vector<vector<int>> G;
    // Number of elements in each row
    int n = 0;
    for (int i = 0; i < x.size(); i += n) {
        vector<int> row;
        n++;
        for (int j = i; j < i + n; j++)
            row.push_back(x[j]);
        G.push_back(row);
    }
    return G;
}

void fill_chain(vector<int>& x, const int depth, vector<int>& chain) {
    // Base condition
    if (depth == x.size() - 1) {
        vector<vector<int>> G = binary_to_graph(x);
        vector<int> subgraph(V, 0);
        chain.push_back(K <= max_clique(G, subgraph, 0, 0));
    }
    // Recursive conditions
    else {
        x[depth] = 1;
        fill_chain(x, depth + 1, chain);
        x[depth] = 0;
        fill_chain(x, depth + 1, chain);
    }
}

double equanimity_clique(bool with) {
	// Adjacency matrix for a graph with 4 nodes
	vector<int> x(6);
	// We consider 2 versions: with or without the last edge
	x[5] = with;
	// Obtain the chain value of this version
	vector<int> chain;
    fill_chain(x, 0, chain);

    return equanimity_ism(chain, 5);
}

int main() {
    cout << "Equanimity of 3-CLIQUES IN A GRAPH WITH 4 NODES" << endl;
    cout << "Equanimity with the last edge: " << equanimity_clique(true) << endl;
    cout << "Equanimity without the last edge: " << equanimity_clique(false) << endl;

	system("pause");
	return 0;
}