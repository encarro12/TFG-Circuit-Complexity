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

/*
obtain number of subsets of a certain size
*/
int number_of_subsets(const int k, const int N) {
	int prod = 1;
	for (int i = 0; i <= k - 1; i++) {
		prod *= 2 * (N - i);
	}
	int k_fact = factorial(k);
	return prod / k_fact;
}

/*
* Combinations without repetitions.
* Althoug it is not possible to obtain a subset with a variable and its negated.
*/
void update_counters(vector<counters>& count, vector<int> & subset, vector<int>& x, int index) {
	// Update the counter of the corresponding subset
	count[subset.size()][subset]++;

	// Loop to choose from different elements present
	// after the current index 'index'
	for (int i = index; i < x.size(); i++) {

		// include the sx[i] in subset.
		subset.push_back(x[i]);

		// move onto the next element.
		update_counters(count, subset, x, i + 1);

		// exclude the sx[i] from subset and triggers
		// backtracking.
		subset.pop_back();
	}
}

/*
*/
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

/*
*/
double equanimity_subsets(const vector<int>& f, const int N) {
	vector<int> x(N);
	vector<counters> v_count(N + 1);
	int pos = 0;
	// Obtain the counters
	truth_table(x, N - 1, f, pos, v_count, N);

	double eq = 0;
	int k = 0;
	for (counters count : v_count) {
		double variance, avg, sum = 0;
		// Calculate the average
		int power = pow(2, N - k);
		for (auto item : count)
			sum += (item.second + 0.0)/power;
		int num_subsets = number_of_subsets(k, N);
		avg = sum / num_subsets;
		// Calculate the variance
		sum = 0;
		for (auto item : count)
			sum += pow(((item.second +0.0)/power) - avg, 2);
		variance = sum / num_subsets;
		eq += variance;
		k++;
	}
	return eq;
}

double equanimity_avg(const vector<int>& f, const int N) {
	int I = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < pow(2, N); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)])
					I++;
	return (I + 0.0) / (N * pow(2, N - 1));
}

double equanimity_var(const vector<int>& f, const int N) {
	vector<int> I_i(N, 0);
	int I = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < pow(2, N); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)]) {
					I_i[i - 1]++; I++;
				}
	double avg = (I + 0.0) / N;
	double sum = 0;
	for (int var : I_i)
		sum += pow(var - avg, 2);
	return sum / N;
}

double equanimity_avg_with_negative_variables(const vector<int>& f, const int N) {
	int I = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < pow(2, N); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)])
					I++;
	return (I + 0.0) / (2*N * pow(2, N - 1)); // The range of values oscilates between [0, 0.5]
}

double equanimity_var_with_negative_variables(const vector<int>& f, const int N) {
	vector<int> I_i(2*N, 0);
	int I = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j < pow(2, N); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)]) {
					(f[k + j]) ? I_i[i - 1]++ : I_i[N + i - 1]++;
					I++;
				}
	double avg = (I + 0.0) / 2*N;
	double sum = 0;
	for (int var : I_i)
		sum += pow(var - avg, 2);
	return sum / 2*N;
}