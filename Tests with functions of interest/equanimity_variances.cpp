#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

using counters = unordered_map<string, int>;
const vector<char> to_char = { '0','1','2','3','4','5','6', '7','8','9' };

/*
*/
unordered_map<string, double> ds_equanimity_of;


/*
* Combinations without repetitions. 
* Althoug it is not possible to obtain a subset with a variable and its negated.
*/
void update_counters(vector<counters> & count, string & subset, string & sx, int index) {
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
void truth_table(string & sx, const int index, const vector<int> & f, int & pos, vector<counters> & count) {
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
double equanimity(const vector<int>& f) {
    string sx = "     ";
    vector<counters> v_count(6);
    int pos = 0;
    // Obtain the counters
    truth_table(sx, 4, f, pos, v_count);
    
    double eq = 0;
    for (counters count : v_count) {
        double variance, avg, sum = 0;
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

/*
*/
void equanimities_of_dataset() {
    ifstream input;
    input.open("myfile.txt");
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
            ds_equanimity_of[bin] = equanimity(fun);
        }
    }
    input.close();

    ofstream output;
    output.open("equanimities_of_dataset.csv");
    output << "function,equanimity\n";
    for (pair<string, double> item : ds_equanimity_of)
        output << item.first << "," << item.second << endl;
    output.close();
}

int main() {
    equanimities_of_dataset();

    system("pause");
    return 0;
}