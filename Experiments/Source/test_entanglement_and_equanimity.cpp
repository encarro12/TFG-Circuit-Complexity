#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "entanglement.h"
#include "equanimities.h"
using namespace std;

// Constant that represents the number of input bits in the studied functions
const int N = 5;

// Constant that states the number of functions outside the dataset
const int NON_DATASET_SAMPLES = 500000000;

// To memorize the functions that are already visited
unordered_set<unsigned int> used;

void test_non_dataset() {
	// Initialize random seed
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned int> dis(0, pow(2, 32) - 1);

	// Open the csv file where the results are going to be stored 
	ofstream output("non_dataset.csv");

	// Write the header for the csv file
	output << "function,equanimity_subsets,equanimiy_subsets_normalized,equanimity_importance,entanglement\n";

	if (output.is_open()) {
		// Get functions randomly outside the dataset and not visited
		for (int i = 0; i < NON_DATASET_SAMPLES; i++) {
			string bin = ""; vector<int> f(32, 0);
			unsigned int dec = dis(gen);
			unsigned int aux = dec;

			for (int i = 0; dec > 0; i++)
			{
				f[i] = dec % 2;
				bin += dec % 2 == 0 ? '0' : '1';
				dec = dec / 2;
			}
			if (used.count(aux))
				i--;
			else {
				used.insert(aux);
				reverse(f.begin(), f.end());
				reverse(bin.begin(), bin.end());
				output << bin << "," << equanimity_subsets(f, N) << "," << equanimity_subsets_normalized(f, N) << "," << equanimity_importance(f, N) << "," << entanglement(f, N) << endl;
			}
		}
	}

	// Close the file
	output.close();
}

void test_dataset() {
	// Open the dataset
	ifstream input("fun1804");

	// Open the csv file where the results are going to be stored
	ofstream output("dataset.csv");

	// Write the header for the csv file
	output << "function,size,equanimity_subsets,equanimiy_subsets_normalized,equanimity_importance,entanglement\n";

	// For each function in dataset we calculate the entanglement
	// and the equanimity and we store the result in the csv.
	if (input.is_open() && output.is_open()) {
		while (input) {
			unsigned int dec,aux; short size; vector<int> f(32, 0); string bin;
			// Read the function
			input >> dec >> size;
			aux = dec;
			for (int i = 0; dec > 0; i++)
			{
				f[i] = dec % 2;
				bin += dec % 2 == 0 ? '0' : '1';
				dec = dec / 2;
			}
			reverse(f.begin(), f.end());
			reverse(bin.begin(), bin.end());
			// Store the function as used for the analysis of non_dataset functions
			used.insert(aux);
			// Calculate the entanglement and the equanimity and store the result in the csv
			output << bin << "," << size << "," << equanimity_subsets(f, N) << "," << equanimity_subsets_normalized(f, N) << "," << equanimity_importance(f, N) << "," << entanglement(f, N) << endl;
		}
	}
	else {
		cout << "ERROR when opening the files\n";
	}
	// Close all files
	input.close(); output.close();
}

int main() {
	// Initialize random seed
	random_device rand;
	mt19937 gen(rand());

	// Analyze the entanglement in dataset and record all functions in dataset
	test_dataset();

	// Analyze random functions outside the dataset and not repeated
	test_non_dataset();

	return 0;
}