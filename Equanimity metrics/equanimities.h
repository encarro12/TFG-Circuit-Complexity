#ifndef _EQUANIMITIES_H
#define _EQUANIMITIES_H

#include <vector>
#include <unordered_map>
using namespace std;

double equanimity_subsets(const vector<int>& f, const int N);

double equanimity_subsets_normalized(const vector<int>& f, const int N);

double equanimity_importance(const vector<int>& f, const int N);

#endif