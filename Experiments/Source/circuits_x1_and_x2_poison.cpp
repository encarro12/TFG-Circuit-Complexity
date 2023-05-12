#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <functional>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <queue>
#include "benchmarks.h"
#include "entanglement.h"
#include "equanimities.h"
using namespace std;

// Alias for the script
struct gate {
	unsigned int function; // Function that represents
	gate *input_left, *input_right; // Implementation as a binary tree
	string name; // To represent the circuit
	bool counted_size = false, counted_width = false; // To know if already been visited in the different procedures

	// Empty constructor
	gate() {}
	// Constructor
	gate(const unsigned int function, gate* input_left, gate* input_right, string name) {
		this->function = function;
		this->input_left = input_left;
		this->input_right = input_right;
		this->name = name;
	}
};
using gates = vector<gate*>;

// Hash function for pair structure
struct hash_fn {
	size_t operator()(const pair<int, int>& x) const {
		return x.first ^ x.second;
	}
};

// Constant that determines the limit number of gates
const int GATES = 50;

// Constant for the number of inputs
const int N = 5;

// Set to avoid repetition of functions when generating them randomly
unordered_set<unsigned int> used_functions;

// Function that given a certain variable it generates the chain
gates level0(gates & gates_created) {
	int group = 1;
	gates level0(2 * N);

	for (int i = 0; i < N; i++) {
		int power = pow(2, N) - 1;
		unsigned int dec = 0;
		while (power >= 0) {
			for (int j = 0; j < group; j++) {
				dec += pow(2, power);
				power--;
			}
			// 0s
			power -= group;
		}
		group *= 2;
		level0[i] = new gate(dec, NULL, NULL, "x" + to_string(i)); gates_created.push_back(level0[i]);
		level0[N + i] = new gate(~dec, NULL, NULL, "not(x" + to_string(i) + ")"); gates_created.push_back(level0[N + i]);
	}
	return level0;
}

// Operator OR and Operator AND
unsigned int op(const unsigned int f1, const unsigned int f2, int level) {
	return (level % 2 != 0) ? f1 | f2 : f1 & f2;
}

// Function that generate the circuit recursively
gate * generate_circuit(gates& last_V, const int gates_left, int & level, mt19937 gen, gates & gates_created) {
	// Generate randomly the number of gates
	int max_gates_superior_level = min(binomial_coefficients(last_V.size(), 2), gates_left);
	uniform_int_distribution<int> max_gates(0, max_gates_superior_level), input(0, last_V.size() - 1);
	int p = max_gates(gen);

	// Base case
	if (p == 0)
		return last_V[input(gen)];

	

	// Let x1 and x2 be an input of every gate of the second level
	if (level == 1) {
		unordered_set<int> used;
		int a; p = min(p, (int)last_V.size());
		gates V(p);
		for (int i = 0; i < p; i++) {
			// generate random input to mix x1 and x2 with
			a = input(gen);

			if (used.insert(a).second) {
				V[i] = new gate(op(last_V[0]->function, last_V[a]->function, level), last_V[0], last_V[a],
					"(" + last_V[0]->name + ((level % 2) ? " OR " : " AND ") + last_V[a]->name + ")");
				gates_created.push_back(V[i]);
			}
			else i--;
		}
		return generate_circuit(V, gates_left - p, ++level, gen, gates_created);
	}

	// Recursive case
	else {
		// Create the gates for the level i
		gates V(p);
		int a, b; unordered_set<pair<int, int>, hash_fn> used;
		for (int i = 0; i < p; i++) {
			// Choose the inputs for gate i in V
			a = input(gen);
			b = input(gen);

			if (a > b) {
				int aux = b; b = a; a = aux;
			}

			if (used.insert({ a,b }).second) { // Create the gate V[i]
				V[i] = new gate(op(last_V[a]->function, last_V[b]->function, level), last_V[a], last_V[b],
					"(" + last_V[a]->name + ((level % 2) ? " OR " : " AND ") + last_V[b]->name + ")");
				gates_created.push_back(V[i]);
			}
			else i--;
		}
		return (p == 1) ? V[0] : generate_circuit(V, gates_left - p, ++level, gen, gates_created);
	}
	
}

int size(const gate *circuit) {
	if (circuit != NULL && circuit->input_left != NULL) {
		// If the circuit in the left is not counted
		int size_left = 0, size_right = 0;
		if (!circuit->input_left->counted_size) {
			size_left = size(circuit->input_left);
			circuit->input_left->counted_size = true;
		}
		// If the circuit in the right is not counted
		if (!circuit->input_right->counted_size) {
			size_right = size(circuit->input_right);
			circuit->input_right->counted_size = true;
		}
		// The number of gates is the number of gates of the left and right gates and itself
		return 1 + size_left + size_right;
	}
	else
		return 0;
}

int width(gate* circuit) {
	// If the circuit is nullptr then return
	if (circuit == NULL) return 0;
	// Store the maximum width
	int width = 0;
	// Queue to separate levels
	queue<gate*> q;
	q.push(circuit);
	while (!q.empty()) {
		int width_level = q.size();
		// Update the maximum width
		width = max(width, width_level);
		// Store the next level
		for (int i = 0; i < width_level; i++) {
			gate* node = q.front(); q.pop();
			// If it is a variable or is already been counted then we do not count it
			if (node->input_left->input_left && !node->input_left->counted_width) {
				q.push(node->input_left);
				node->input_left->counted_width = true;
			}
			if (node->input_right->input_left && !node->input_right->counted_width) {
				q.push(node->input_right);
				node->input_right->counted_width = true;
			}
		}
	}
	return width;
}

// Function that compares x1^x2 with x3^x4
pair<int, int> histogram(const vector<int> & f) {
	// Calculate the ones in x1^x2
	int x1andx2 = 0;
	for (int i = 0; i < pow(2, N); i += pow(2, 3)) {
		for (int j = i; j < (2 + i); j++) {
			if (f[j] == 1)
				x1andx2++;
		}
	}
	// Calculate the ones in x3^x4
	int x3andx4 = 0;
	for (int i = 0; i < pow(2, N); i += pow(2, 5)) {
		for (int j = i; j < (pow(2, 3) + i); j++) {
			if (f[j] == 1)
				x3andx4++;
		}
	}
	return { x1andx2, x3andx4 };
}

int main() {
	// Initialize random seed
	random_device rand;
	mt19937 gen(rand());

	// Create the file to store all data for posterior analysis
	ofstream file("circuits x1 AND x2 poison 50 gates.csv");

	// Header of the file
	file << "function,entanglement,equanimity,x1 AND x2,x3 AND x4,circuit,depth,width,size\n";

	for (;;) {
		// Generate first level of the circuit
		gates gates_created;

		// Generate randomly the number of gates for the first level
		uniform_int_distribution<int> max_gates(1, GATES);
		int p = max_gates(gen);

		// Initialize
		gates V0 = level0(gates_created), V1(p);

		// The first gate must be x1 ^ x2
		V1[0] = new gate(V0[1]->function & V0[2]->function, V0[1], V0[2],
			"(" + V0[1]->name + " AND " + V0[2]->name + ")");
		gates_created.push_back(V1[0]);
		// Generate randomly the rest of the inputs
		std::uniform_int_distribution<int> input(0, 2 * N - 1);
		int a, b; unordered_set<pair<int, int>, hash_fn> used;
		used.insert({ 3,4 }); used.insert({ 1,2 });
		for (int i = 1; i < p; i++) {
			// Choose the inputs for gate i in V1
			a = input(gen);
			b = input(gen);

			if (a > b) {
				int aux = b; b = a; a = aux;
			}

			if (used.insert({ a,b }).second) { // Create the gate V[i]
				V1[i] = new gate(V0[a]->function & V0[b]->function, V0[a], V0[b], "(" + V0[a]->name + " AND " + V0[b]->name + ")");
				gates_created.push_back(V1[i]);
			}
			else i--;
		}

		// Generate the circuit recursively
		int level = 1; gate* circuit = generate_circuit(V1, GATES - p, level, gen, gates_created);

		// Convert it to binary
		vector<int> f(pow(2, N));
		unsigned int dec = circuit->function;
		for (int i = 0; dec > 0; i++)
		{
			f[i] = dec % 2;
			dec = dec / 2;
		}
		reverse(f.begin(), f.end());

		// Obtain the histogram
		auto his = histogram(f);

		// Store the data in the csv file "function,entanglement,equanimity,x1 AND x2,x3 AND x4,circuit,depth,width,size\n";
		if (used_functions.insert(circuit->function).second) {
			file << circuit->function << "," << entanglement(f, N) << "," << equanimity_subsets(f, N) << "," << his.first << "," << his.second
				<< "," << circuit->name << "," << level << "," << width(circuit) << "," << size(circuit) << "\n";
		}

		// Delete all gates created
		for (gate* g : gates_created)
			delete g;
	}
	return 0;
}