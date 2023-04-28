#include "benchmarks.h"

vector<bool> isPrime;
vector<int> primes;

// Criba de Eratóstenes
void criba(int n) {
	isPrime = vector<bool>(n, true);
	primes = vector<int>();
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i < n; ++i) {
		if (isPrime[i]) {
			primes.push_back(i);
			for (int h = 2; h * i < n; ++h) isPrime[i * h] = 0;
		}
	}
}

vector<int> primality_test(const int N) {
	criba(pow(2, N));
	vector<int> chain;
	for (int column = pow(2, N) - 1; column >= 0; column--)
		chain.push_back(isPrime[column]);
	return chain;
}