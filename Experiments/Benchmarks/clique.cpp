#include "benchmarks.h"

/*
given a graph represented as its adjacency matrix G, a subgraph, and
k \in N, it returns whether the subgraph forms a clique or not
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
int max_clique(const vector<vector<int>>& G, vector<int>& subgraph, const int i, const int l, const int V) {
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
            k = max(k, max_clique(G, subgraph, j, l + 1, V));
        }
    }
    return k;
}

/*
given input x, which represents the edges of a graph, ir returns
its correspondent adjacency matrix
*/
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


/*
it returns the boolean function asociated with the clique problem by
iterating through the columns of its truth table and calculating
the associated outputs
*/
void fill_chains(vector<int>& x, const int depth, vector<int> & chain, const int K, const int V) {
    // Base condition
    if (depth == x.size() - 1) { // The -1 must be deleted for the generic version
        vector<vector<int>> G = binary_to_graph(x);
        vector<int> subgraph(V, 0);
        chain.push_back(K <= max_clique(G, subgraph, 0, 0, V));
    }
    // Recursive conditions
    else {
        x[depth] = 1;
        fill_chains(x, depth + 1, chain, K, V);
        x[depth] = 0;
        fill_chains(x, depth + 1, chain, K, V);
    }
}

// calculates N C k
int binomial_coefficients(int n, int k) {
    vector<int> C(k + 1);
    C[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = min(i, k); j > 0; j--)
            C[j] = C[j] + C[j - 1];
    }
    return C[k];
}

// generic version
vector<int> clique(int V, int K) {
    vector<int> x(binomial_coefficients(V, 2)), chain;
    fill_chains(x, 0, chain, K, V);
    return chain;
}

/*
especial case: in order to be able to create a complete graph of six vertices with N = E = 5,
we consider the sixth edge is always (or never) added depending of the value of with
*/
vector<int> clique(bool with) {
    vector<int> x(6), chain;
    x[5] = with;
    fill_chains(x, 0, chain, 3, 4);
    return chain;
}