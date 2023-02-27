#include <iostream>
#include "equanimities.h"
using namespace std;


// Function from N bits to 1 that represent parity function
// PARAMETERS
//		* int N: Number of bits of the function
// RETURNS
//		* vector<int> chain: Chain of the function
void majority_recursive(vector<int>& chain, const int i, const int one_counter, const int N) {
	// Base condition
	if (i < 0)
		chain.push_back(one_counter > N/2);
	// Recursive condition
	else {
		// if x_i = 1, then update the one counter
		majority_recursive(chain, i - 1, one_counter + 1,N);
		// if x_i = 0, the one counter stays the same.
		majority_recursive(chain, i - 1, one_counter,N);
	}
}

vector<int> majority(const int N) {
	vector<int> chain;
	majority_recursive(chain, N - 1, 0, N);
	return chain;
}

int main() {
	for (int N = 3; N <= 20; N++) {
		vector<int> chain_majority = majority(N);
		cout << "SIZE: " << N << endl;
		cout << "Equanimity of Ismael: " << equanimity_ism(chain_majority, N) << endl;
		cout << "Equanimity ours average: " << equanimity_ours_avg(chain_majority, N) << endl;
		cout << "Equanimity ours variance: " << equanimity_ours_var(chain_majority, N) << endl;
	}

	return 0;
}
