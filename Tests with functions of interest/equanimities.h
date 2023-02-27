#ifndef _EQUANIMITIES_H
#define _EQUANIMITIES_H

#include <vector>
#include <unordered_map>
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

void update_counters(vector<counters>& count, vector<int>& subset, vector<int>& x, int index);

void truth_table(vector<int>& x, const int index, const vector<int>& f, int& pos, vector<counters>& count, const int N);

double equanimity_ism(const vector<int>& f, const int N);

double equanimity_ours_avg(const vector<int>& f, const int N);

double equanimity_ours_var(const vector<int>& f, const int N);

#endif