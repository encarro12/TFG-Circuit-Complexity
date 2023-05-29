#include "benchmarks.h"

void parity_recursive(vector<int>& chain, const int i, const int one_counter) {
	// Base condition
	if (i < 0)
		chain.push_back(one_counter % 2 == 0);
	// Recursive condition
	else {
		// if x_i = 1, then update the one counter
		parity_recursive(chain, i - 1, one_counter + 1);
		// if x_i = 0, the one counter stays the same.
		parity_recursive(chain, i - 1, one_counter);
	}
}

vector<int> parity(const int N) {
	vector<int> chain;
	parity_recursive(chain, N - 1, 0);
	return chain;
}


