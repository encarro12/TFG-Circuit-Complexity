#include "benchmarks.h"

void majority_recursive(vector<int>& chain, const int i, const int one_counter, const int N) {
	// Base condition
	if (i < 0)
		chain.push_back(one_counter > N / 2);
	// Recursive condition
	else {
		// if x_i = 1, then update the one counter
		majority_recursive(chain, i - 1, one_counter + 1, N);
		// if x_i = 0, the one counter stays the same.
		majority_recursive(chain, i - 1, one_counter, N);
	}
}

vector<int> majority(const int N) {
	vector<int> chain;
	majority_recursive(chain, N - 1, 0, N);
	return chain;
}