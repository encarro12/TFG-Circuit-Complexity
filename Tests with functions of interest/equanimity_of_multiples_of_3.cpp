#include <iostream>
#include "equanimities.h"
using namespace std;

vector<int> multiples_of_3(const int N) {
	vector<int> chain;
	for (int column = pow(2, N) - 1; column >= 0; column--)
		chain.push_back(column % 7 == 0);
	return chain;
}

int main() {
	for (int N = 3; N <= 20; N++) {
		vector<int> chain_multiples_of_3 = multiples_of_3(N);
		cout << "SIZE: " << N << endl;
		cout << "Equanimity of Ismael: " << equanimity_ism(chain_multiples_of_3,N) << endl;
		cout << "Equanimity ours average: " << equanimity_ours_avg(chain_multiples_of_3,N) << endl;
		cout << "Equanimity ours variance: " << equanimity_ours_var(chain_multiples_of_3,N) << endl;
	}

	return 0;
}
