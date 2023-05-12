#include "benchmarks.h"
#include "equanimities.h"
#include "entanglement.h"
#include <iostream>
using namespace std;

// Number of vertices in the graph
const int V = 5;
// Size of CLIQUE
const int K = 3;

int main() {
	// Calculate the chain of the alternative version of clique, CLIQUE'
	vector<int> f = clique_nxor_parity(false);

	// Calculate the equanimity
	double eq = equanimity_subsets(f, V);

	// Calculate the entanglement
	int ent = entanglement(f, V);

	cout << "Equanimity: " << eq << " Entanglement: " << ent << endl;
	return 0;
}