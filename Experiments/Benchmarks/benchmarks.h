#ifndef _BENCHMARKS_H
#define _BENCHMARKS_H

#include <vector>
#include <numeric>
using namespace std;

vector<int> clique_nxor_parity(int V, int K);
vector<int> clique_nxor_parity(bool with);
int binomial_coefficients(int n, int k);
vector<int> parity(int N);
vector<int> clique(int N, int K);
vector<int> clique(bool with);
vector<int> majority(const int N);
vector<int> majority_nxor_parity(const int N);
vector<int> primality_test(const int N);

#endif