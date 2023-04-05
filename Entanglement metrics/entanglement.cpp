#include "entanglement.h"

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

using truth_table = unordered_map<vector<int>, int, hash_fn>;

void create_map_truth_table(truth_table & TT, vector<int>& x, const int depth, const vector<int>& f) {
	// Base condition
	if (depth == x.size())
		TT[x] = f[TT.size()];

	// Recursive conditions
	else {
		x[depth] = 1;
		create_map_truth_table(TT, x, depth + 1, f);
		x[depth] = 0;
		create_map_truth_table(TT, x, depth + 1, f);
	}
}

void complementary_subset(const vector<int>& subset, vector<int>& subset_compl, const int N) {
	int pos = 0;
	for (int i = 0; i < N; i++) {
		if (pos < subset.size() && subset[pos] == i) pos++;
		else subset_compl.push_back(i);
	}
}

void calculate_n_or_m(vector<int>& x, const vector<int>& subset, const int pos_s, const bool S, 
	vector<int>& fun, unordered_set<vector<int>, hash_fn>& fun_set, const int N, const truth_table & TT) {
	// Base condition
	if (pos_s < 0) {
		// S1
		if (S) {
			vector<int> subset_c;
			complementary_subset(subset, subset_c, N);
			vector<int> fun;
			calculate_n_or_m(x, subset_c, subset_c.size() - 1, false, fun, fun_set, N, TT);
			fun_set.insert(fun);
		}
		// S2
		else {
			fun.push_back(TT.at(x));
		}
	}
	// Recursive conditions
	else {
		x[subset[pos_s]] = 1;
		calculate_n_or_m(x, subset, pos_s - 1, S, fun, fun_set, N, TT);
		x[subset[pos_s]] = 0;
		calculate_n_or_m(x, subset, pos_s - 1, S, fun, fun_set, N, TT);
	}
}

int calculate_nplusm(const vector<int>& subset, const int N, const truth_table & TT) {
	vector<int> subset_c;
	complementary_subset(subset, subset_c, N);

	vector<int> x(N); vector<int> fun;
	unordered_set<vector<int>, hash_fn> fun_set;
	calculate_n_or_m(x, subset, subset.size() - 1, true, fun, fun_set, N, TT);
	int n = fun_set.size();

	unordered_set<vector<int>, hash_fn> fun_set2;
	calculate_n_or_m(x, subset_c, subset_c.size() - 1, true, fun, fun_set2, N, TT);
	int m = fun_set2.size();

	return n + m;
}

int entanglement_recursive(vector<int>& subset, vector<int>& C, int index, const int N, const truth_table & TT) {
	// Calculate n+m 
	int ent = subset.size() != N / 2 ? INT_MAX : calculate_nplusm(subset, N, TT);

	// Loop to choose from different elements present
	// after the current index 
	for (int i = index; i < N; i++) {

		// include the C[i] in subset.
		subset.push_back(C[i]);

		// move onto the next element.
		ent = min(ent, entanglement_recursive(subset, C, i + 1, N, TT));

		// exclude the C[i] from subset and triggers
		// backtracking.
		subset.pop_back();
	}

	return ent;
}

// Function that given a certain boolean function it returns
// its entanglement value.
int entanglement(const vector<int>& f, const int N) {
	// Initialize the truth table
	truth_table TT;
	// Fill the truth table hash map from the function f
	vector<int> x(N); create_map_truth_table(TT, x, 0, f);
	// Initialize the set where the partitions (S1,S2) are made.
	// This is the set {0, ..., N - 1}.
	vector<int> C(N);
	for (int i = 0; i < N; i++) { C[i] = i; }
	// Call the recursive entanglement function which is 
	// a backtracking algorithm
	vector<int> subset;  
	return entanglement_recursive(subset, C, 0, N, TT);
}