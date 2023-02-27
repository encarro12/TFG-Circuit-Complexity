#include <iostream>
#include "equanimities.h"
using namespace std;

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

vector<int> is_prime(const int N) {
	vector<int> chain;
	for (int column = pow(2, N) - 1; column >= 0; column--)
		chain.push_back(isPrime[column]);
	return chain;
}

int main() {
	for (int N = 3; N <= 20; N++) {
		criba(pow(2, N));
		vector<int> chain_is_prime = is_prime(N);
		cout << "SIZE: " << N << endl;
		cout << "Equanimity of Ismael: " << equanimity_ism(chain_is_prime,N) << endl;
		cout << "Equanimity ours average: " << equanimity_ours_avg(chain_is_prime, N) << endl;
		cout << "Equanimity ours variance: " << equanimity_ours_var(chain_is_prime, N) << endl;
	}

	return 0;
}
