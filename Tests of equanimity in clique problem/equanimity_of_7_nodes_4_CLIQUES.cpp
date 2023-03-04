#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>
using namespace std;

struct hash_fn
{
    std::size_t operator() (const vector<int>& V) const
    {
        size_t H = 0;
        for (int i = 0; i < V.size(); i++)
            H ^= V[i];

        return H;
    }
};

unordered_set<vector<int>, hash_fn> valid_clique;

const vector<int> C = { 6,5,4,3,2,1,0 };

inline bool operator==(const vector<int>& A, const vector<int>& B) {
    if (A.size() > B.size()) {
        for (int i = 0; i < B.size(); i++)
            if (A[B[i]] == 0)
                return false;
    }
    else {
        for (int i = 0; i < A.size(); i++)
            if (B[A[i]] == 0)
                return false;
    }
    return true;
}

void subsets(vector<vector<int>>& P, const vector<int>& C, vector<int>& subset,
    const int size, const int index) {
    // Insert the subset if its size is the value indicated in the parameter
    if (subset.size() == size)
        P.push_back(subset);
    // Loop to choose from different elements present
    // after the current index 'index'
    for (int i = index; i < C.size(); i++) {
        // include the C[i] in subset.
        subset.push_back(C[i]);

        // move onto the next element.
        subsets(P, C, subset, size, i + 1);

        // exclude the C[i] from subset and triggers
        // backtracking.
        subset.pop_back();
    }
}

void initialize_valid_clique_set() {
    vector<vector<int>> subsets_size_4_on_7; vector<int> subset;
    subsets(subsets_size_4_on_7, C, subset, 4, 0);
    for (vector<int> S_4_7 : subsets_size_4_on_7) {
        vector<vector<int>> subsets_size_2_on_4;
        subsets(subsets_size_2_on_4, S_4_7, subset, 2, 0);
        vector<int> item;
        for (vector<int> S_2_4 : subsets_size_2_on_4)
            item.push_back(S_2_4[0] * (S_2_4[0] - 1) / 2 + S_2_4[1]);
        valid_clique.insert(item);
    }
}

void fill_chain(vector<int>& x, const int depth, vector<int>& chain) {
    // Base condition
    if (depth == x.size()) {
        chain.push_back(0);
        for (vector<int> subset : valid_clique) {
            if (subset == x) {
                chain[chain.size() - 1] = 1;
                break;
            }
        }
    }
    // Recursive conditions
    else {
        x[depth] = 1;
        fill_chain(x, depth + 1, chain);
        x[depth] = 0;
        fill_chain(x, depth + 1, chain);
    }
}

int main() {
    vector<int> x(21);
    vector<int> chain;
    initialize_valid_clique_set();
    fill_chain(x, 0, chain);
    system("pause");
    return 0;
}