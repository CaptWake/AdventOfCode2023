#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }

    int res = 0;
    string line;

    while (getline(infile, line)) {
        int N = line.length()-1;
        int first = -1, last = -1;
        for (int i = 0; first<0 || last<0 ; ++i) {
            if (first < 0 & isdigit(line[i]))
                first = i;
            if (last < 0 & isdigit(line[N-i]))
                last = N-i;
        }
        string number = string() + line[first] + line[last];
        res += stoi(number);
    }
    
    cout << res << endl;
    return 0;
}