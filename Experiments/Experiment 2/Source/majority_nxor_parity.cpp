#include "benchmarks.h"

vector<int> nxor(const vector<int>& f1, const vector<int> f2) {
	vector<int> f;
	for (int i = 0; i < f1.size(); i++)
		f.push_back((f1[i] && f2[i]) || (!f1[i] && !f2[i]));
	return f;
}

vector<int> majority_nxor_parity(const int N) {
	return nxor(parity(N), majority(N));
}
