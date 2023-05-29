#include <iostream>
#include <fstream>
#include "benchmarks.h"
#include "entanglement.h"
#include "equanimities.h"
using namespace std;

const int MIN_N = 2;
const int MAX_N = 10;

const int MIN_V = 3;
const int MAX_V = 6;

int main() {
	// Create files to store the results for each benchmark
	ofstream parity_file("parity.csv"),
		majority_file("majority.csv"),
		primality_file("primality.csv");
		clique_file("clique.csv"),
		clique_comma_file("clique_comma.csv");;

	// Initialize header of all files
	string header = "N,equanimity_subsets,equanimity_subsets_normalized,equanimity_importance,entanglement\n";
	parity_file << header;
	majority_file << header;
	primality_file << header;
	clique_file << header;
	clique_comma_file << header;

	// Obtain values of the metrics for different size of input for the Ppoly problems
	for (int N = MIN_N; N <= MAX_N; N++) {
		parity_file << N << "," << equanimity_subsets(parity(N), N) << "," << equanimity_subsets_normalized(parity(N), N) << "," << equanimity_importance(parity(N), N) << ","
			<< entanglement(parity(N), N) << endl;
		majority_file << N << "," << equanimity_subsets(majority(N), N) << "," << equanimity_subsets_normalized(majority(N), N) << "," << equanimity_importance(majority(N), N) << ","
			<< entanglement(majority(N), N) << endl;
		primality_file << N << "," << equanimity_subsets(primality_test(N), N) << "," << equanimity_subsets_normalized(primality_test(N), N) << "," << equanimity_importance(primality_test(N), N) << ","
			<< entanglement(primality_test(N), N) << endl;
	}

	// Same for CLIQUE problems
	for (int V = MIN_V; V <= MAX_V; V++) {
		int k = ceil((V + 0.0) / 2), N = binomial_coefficients(V, 2);
		clique_file << N << "," << equanimity_subsets(clique(V, k), N) << "," << equanimity_subsets_normalized(clique(V, k), N) << "," << equanimity_importance(clique(V, k), N) << ","
			<< entanglement(clique(V, k), N) << endl;
		clique_comma_file << N << "," << equanimity_subsets(clique_nxor_parity(V, k), N) << "," << equanimity_subsets_normalized(clique_nxor_parity(V, k), N) << "," << equanimity_importance(clique_nxor_parity(V, k), N) << "," 
			<< entanglement(clique_nxor_parity(V, k), N) << endl;
	}

	return 0;
}