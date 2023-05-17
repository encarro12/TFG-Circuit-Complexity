#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "equanimities.h"
#include "entanglement.h"
using namespace std;

// MIN and MAX size of input in functions to analyze
const int MIN_N = 4;
const int MAX_N = 10;

// Constant that states the number of functions to analyze
const int SAMPLES = 1000000;

void functions_generator(const int N) {
	// Initialize random seed
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned int> dis(0, pow(2, 16) - 1);

	// To memorize the functions that are already visited
	unordered_set<string> used;

	// Open the csv file where the results are going to be stored 
	string filename = "functions " + to_string(N) + " bits to 1.csv";
	ofstream output(filename);

	// Write the header for the csv file
	output << "function,equanimity_subsets,equanimity_subsets_normalized,equanimity_importance,entanglement,\n";

	if (output.is_open()) {
		// Get functions randomly outside the dataset and not visited
		for (int i = 0; i < SAMPLES; i++) {
			int pos = 0;
			string bin = ""; vector<int> f(pow(2, N), 0);
			while (pos < pow(2, N)) {
				unsigned int dec = dis(gen);

				for (int j = pos; dec > 0; j++)
				{
					f[j] = dec % 2;
					bin += dec % 2 == 0 ? '0' : '1';
					dec = dec / 2;
				}
				pos += 16;
			}
			if (used.count(bin))
				i--;
			else {
				used.insert(bin);
				output << bin << "," << equanimity_subsets(f, N) << "," << equanimity_subsets_normalized(f, N) << "," << equanimity_importance(f, N) << "," << entanglement(f, N) << endl;
			}
			if (i >= pow(2, pow(2, N)) - 1)
				break;
		}
	}

	cout << "nivel " << N << "terminado" << endl;

	// Close the file
	output.close();
}


int main() {
	// Initialize random seed
	random_device rand;
	mt19937 gen(rand());

	// For each N analyze the sample of functions of N bits in 1
	for (int N = MIN_N; N <= MAX_N; N++)
		functions_generator(N);

	return 0;
}