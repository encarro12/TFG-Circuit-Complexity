#include <iostream>
#include <cmath>
#include <string>
using namespace std;

float equanimity(string f) {
    int I = 0;
    for(int i = 1; i <= 5; i++)
        for (int j = 0; j < pow(2, 5); j += pow(2, i))
            for (int k = 0; k < pow(2, i - 1); k++)
                if(f[k + j] != f[(k + j) + pow(2, i - 1)])
                    I++;
    return (I + 0.0)/(5*16);
}

int main() {
    cout << equanimity("10000000000000000000000000000000") << endl;
    system("pause");
    return 0;
}