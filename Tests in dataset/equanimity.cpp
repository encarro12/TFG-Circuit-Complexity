#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <ctime>
using namespace std;

unordered_set<string> used;

using counters = unordered_map<string, int>;
const vector<char> to_char = { '0','1','2','3','4','5','6', '7','8','9' };

/*
* Combinations without repetitions.
* Althoug it is not possible to obtain a subset with a variable and its negated.
*/
void update_counters(vector<counters>& count, string& subset, string& sx, int index) {
	// Update the counter of the corresponding subset
	count[subset.size()][subset]++;

	// Loop to choose from different elements present
	// after the current index 'index'
	for (int i = index; i < sx.size(); i++) {

		// include the sx[i] in subset.
		subset.push_back(sx[i]);

		// move onto the next element.
		update_counters(count, subset, sx, i + 1);

		// exclude the sx[i] from subset and triggers
		// backtracking.
		subset.pop_back();
	}
}

/*
*/
void truth_table(string& sx, const int index, const vector<int>& f, int& pos, vector<counters>& count) {
	// Base condition
	if (index < 0) {
		if (f[pos] == 1) {
			string subset = "";
			update_counters(count, subset, sx, 0);
		}
		pos++;
	}
	// Recursive conditions
	else {
		sx[4 - index] = to_char[index];
		truth_table(sx, index - 1, f, pos, count);
		sx[4 - index] = to_char[index + 5];
		truth_table(sx, index - 1, f, pos, count);
	}
}

/*
*/
float equanimity_ism(const vector<int>& f) {
	string sx = "     ";
	vector<counters> v_count(6);
	int pos = 0;
	// Obtain the counters
	truth_table(sx, 4, f, pos, v_count);

	float eq = 0;
	for (counters count : v_count) {
		float variance, avg, sum = 0;
		// Calculate the average
		for (pair<string, int> item : count)
			sum += item.second;
		avg = sum / count.size();
		// Calculate the variance
		sum = 0;
		for (pair<string, int> item : count)
			sum += pow(item.second - avg, 2);
		variance = sum / count.size();
		eq += variance;
	}
	return eq;
}

float equanimity_ours_avg(vector<int>& f) {
	int I = 0;
	for (int i = 1; i <= 5; i++)
		for (int j = 0; j < pow(2, 5); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)])
					I++;

	return (I + 0.0) / (5 * 16);
}

float equanimity_ours_var(vector<int>& f) {
	vector<int> I_i(5, 0);
	int I = 0;
	for (int i = 1; i <= 5; i++)
		for (int j = 0; j < pow(2, 5); j += pow(2, i))
			for (int k = 0; k < pow(2, i - 1); k++)
				if (f[k + j] != f[(k + j) + pow(2, i - 1)]) {
					I_i[i - 1]++; I++;
				}
	float avg = (I + 0.0) / (5);
	float sum = 0;
	for (int var : I_i)
		sum += pow(var - avg, 2);
	return sum / 5;
}

/*
*/
void equanimities_of_dataset() {
	ifstream input;
	input.open("myfile.txt");
	ofstream output1;
	output1.open("equanimities_of_dataset_ours_var3.csv");
	output1 << "function,equanimity\n";
	ofstream output2;
	output2.open("equanimities_of_dataset_ours_avg3.csv");
	output2 << "function,equanimity\n";
	ofstream output3;
	output3.open("equanimities_of_dataset_ismael3.csv");
	output3 << "function,equanimity\n";
	if (input.is_open()) {
		unsigned int dec, aux;
		string bin;
		while (input) {
			vector<int> fun(32, 0);
			input >> dec >> bin;
			aux = dec;
			for (int i = 0; dec > 0; i++)
			{
				fun[i] = dec % 2;
				dec = dec / 2;
			}
			reverse(fun.begin(), fun.end());
			float eq_ours_var = equanimity_ours_var(fun);
			float eq_ours_avg = equanimity_ours_avg(fun);
			float eq_ism = equanimity_ism(fun);
			used.insert(bin);
			output1 << bin << "," << eq_ours_var << "\n";
			output2 << bin << "," << eq_ours_avg << "\n";
			output3 << bin << "," << eq_ism << "\n";
		}
	}
	input.close();
	output1.close();
	output2.close();
	output3.close();
}

/*
*/
void equanimities_of_non_dataset() {
	ofstream output1;
	output1.open("equanimities_of_non_dataset_ours_var3.csv");
	output1 << "function,equanimity\n";
	ofstream output2;
	output2.open("equanimities_of_non_dataset_ours_avg3.csv");
	output2 << "function,equanimity\n";
	ofstream output3;
	output3.open("equanimities_of_non_dataset_ismael3.csv");
	output3 << "function,equanimity\n";
	for (int i = 0; i < 5000000; i++) {
		string fun = "";
		vector<int> v_fun;
		for (int j = 0; j < 32; j++) {
			if (rand() % 2) {
				fun += '1';
				v_fun.push_back(1);
			}
			else {
				fun += '0';
				v_fun.push_back(0);
			}
		}
		if (used.count(fun)) i--;
		else {float eq_ours_var = equanimity_ours_var(v_fun);
		float eq_ours_avg = equanimity_ours_avg(v_fun);
		float eq_ism = equanimity_ism(v_fun);
		used.insert(fun);
		output1 << fun << "," << eq_ours_var << "\n";
		output2 << fun << "," << eq_ours_avg << "\n";
		output3 << fun << "," << eq_ism << "\n";}
	}
	output1.close();
	output2.close();
	output3.close();
}

int main() {
	srand(time(NULL));
	equanimities_of_dataset();
	equanimities_of_non_dataset();

	return 0;
}
