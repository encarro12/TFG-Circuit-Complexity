#include "benchmarks.h"
#include "equanimities.h"
#include "entanglement.h"
#include <iostream>
using namespace std;

const int N = 10;

int main() {
	// Calculate the chain of the alternative majority
	vector<int> f = majority_nxor_parity(N);

	// Calculate the equanimity
	double eq = equanimity_subsets(f, N);

	// Calculate the entanglement
	int ent = entanglement(f, N);

	cout << "Equanimity: " << eq << " Entanglement: " << ent << endl;
	return 0;
}