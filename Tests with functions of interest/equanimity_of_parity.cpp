#include <iostream>
#include "equanimities.h"
using namespace std;


// Function from N bits to 1 that represent parity function
// PARAMETERS
//		* int N: Number of bits of the function
// RETURNS
//		* vector<int> chain: Chain of the function
void parity_recursive(vector<int> & chain, const int i, const int one_counter) {
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

int main() {
	for (int N = 3; N <= 20; N++) {
		vector<int> chain_parity = parity(N);
		cout << "SIZE: " << N << endl;
		cout << "Equanimity of Ismael: " << equanimity_ism(chain_parity,N) << endl;
		cout << "Equanimity ours average: " << equanimity_ours_avg(chain_parity,N) << endl;
		cout << "Equanimity ours variance: " << equanimity_ours_var(chain_parity,N) << endl;
	}

	return 0;
}
