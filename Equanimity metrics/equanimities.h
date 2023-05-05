#ifndef _EQUANIMITIES_H
#define _EQUANIMITIES_H

#include <vector>
#include <unordered_map>
using namespace std;

double equanimity_subsets(const vector<int>& f, const int N);

double equanimity_subsets_normalized(const vector<int>& f, const int N);

double equanimity_avg(const vector<int>& f, const int N);

double equanimity_var(const vector<int>& f, const int N);

double equanimity_avg_with_negative_variables(const vector<int>& f, const int N);

double equanimity_var_with_negative_variables(const vector<int>& f, const int N);

#endif