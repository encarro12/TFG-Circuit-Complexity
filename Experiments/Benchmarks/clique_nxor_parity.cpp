#include "benchmarks.h"

vector<int> nxor(const vector<int>& f1, const vector<int> f2) {
	vector<int> f;
	for (int i = 0; i < f1.size(); i++)
		f.push_back((f1[i] && f2[i]) || (!f1[i] && !f2[i]));
	return f;
}

vector<int> clique_nxor_parity(int V, int K) {
	return nxor(parity(binomial_coefficients(V, 2)), clique(V, K));
}

vector<int> clique_nxor_parity(bool with) {
	return nxor(parity(5), clique(with));
}