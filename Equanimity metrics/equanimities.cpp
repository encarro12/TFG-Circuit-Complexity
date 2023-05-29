#include "equanimities.h"
using namespace std;

struct hash_fn
{
	std::size_t operator() (const vector<int>& V) const
	{
		size_t H = 0;
		for (int i = 0; i < V.size(); i++)
			H ^= V[i];

		return H;
	}
};

using counters = unordered_map<vector<int>, int, hash_fn>;

int factorial(int x) {
	if (x == 0) {
		return 1;
	}
	else {
		return x * factorial(x - 1);
	}
}

// obtain number of subsets of a certain size
int number_of_subsets(const int k, const int N) {
	unsigned int prod = 1;
	for (int i = 0; i <= k - 1; i++) {
		prod *= 2 * (N - i);
	}
	int k_fact = factorial(k);
	return prod / k_fact;
}

/*
* Combinations without repetitions.
* Although it is not possible to obtain a subset with a variable and its negated.
*/
void update_counters(vector<counters>& count, vector<int> & subset, vector<int>& x, int index) {
	// Update the counter of the corresponding subset
	count[subset.size()][subset]++;

	// Loop to create every subset of x
	for (int i = index; i < x.size(); i++) {

		// include x[i] in subset.
		subset.push_back(x[i]);

		// move onto the next element.
		update_counters(count, subset, x, i + 1);

		// exclude x[i] from subset and triggers
		// backtracking.
		subset.pop_back();
	}
}

void truth_table(vector<int> & x, const int index, const vector<int>& f, int& pos, vector<counters>& count, const int N) {
	// Base condition
	if (index < 0) {
		if (f[pos] == 1) {
			vector<int> subset;
			update_counters(count, subset, x, 0);
		}
		pos++;
	}
	// Recursive conditions
	else {
		x[N - 1 - index] = index;
		truth_table(x, index - 1, f, pos, count, N);
		x[N - 1 - index] = index + N;
		truth_table(x, index - 1, f, pos, count, N);
	}
}

// calculates the Equanimity based on the survival of subsets (normalized)
double equanimity_subsets_normalized(const vector<int>& f, const int N) {
	vector<int> x(N);
	// v_count[i] contains the values of c_\vec{x}_S for x \in Z_2^i
	vector<counters> v_count(N + 1);
	int pos = 0;
	// Obtain the counters
	truth_table(x, N - 1, f, pos, v_count, N);

	double eq = 0;
	int k = 0;
	for (int k = 1; k <= N; k++) {
		double variance, avg, sum = 0;
		// Calculate the average
		int power = pow(2, N - k);
		for (auto item : v_count[k])
			sum += (item.second + 0.0);
		int num_subsets = number_of_subsets(k, N);
		avg = sum / num_subsets;
		// Calculate the variance (sigma_k)
		sum = 0;
		for (auto item : v_count[k])
			sum += pow((item.second + 0.0) - avg, 2);
		int left = num_subsets - v_count[k].size();
		for (int i = 0; i < left; i++)
			sum += pow(avg, 2);

		variance = sum / num_subsets;
		// add the value of sigma_k normalized into eq
		eq += variance / pow(2,2*(N-k-1));
	}
	return 1-eq/N;
}

// calculates the Equanimity based on the survival of subsets
double equanimity_subsets(const vector<int>& f, const int N) {
	// Obtain the counters
	vector<int> x(N); vector<counters> v_count(N + 1); int pos = 0;
	truth_table(x, N - 1, f, pos, v_count, N);

	// Calculate the equanimity
	double eq = 0, variance, avg, sum = 0;
	int num_subsets;
	for (int k = 1; k <= N; k++) {
		// Obtain the number of subsets of size k
		num_subsets = number_of_subsets(k, N);
		// Calculate the average
		sum = 0;
		for (auto item : v_count[k])
			sum += (item.second + 0.0);
		avg = sum / num_subsets;
		// Calculate the variance (sigma_k)
		sum = 0;
		for (auto item : v_count[k])
			sum += pow((item.second + 0.0) - avg, 2);
		int left = num_subsets - v_count[k].size();
		for (int i = 0; i < left; i++)
			sum += pow(avg, 2);
	
		variance = sum / num_subsets;
		// add the value of sigma_k into eq
		eq += variance;
	}
	return -eq;
}

// calculates the Equanimity based on the importance of each variable
double equanimity_importance(const vector<int>& f, const int N) {
	int I = 0;
	// calculate I(i) for every 1<=i<=n and add it into I
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < pow(2, N); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)])
					I++;
	// return the value of Q_I(f)
	return (I + 0.0) / (N * pow(2, N - 1));
}