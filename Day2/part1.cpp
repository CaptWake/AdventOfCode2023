#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <regex>


using namespace std;

int main()
{
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }


    regex r("(\\d+)\\s+(blue|red|green)");

    int res = 0;
    string line;

    unordered_map<string, int> colorCounts = {
        {"blue", 14},
        {"green", 13},
        {"red", 12}
    };

    int id = 1;
    while (getline(infile, line)) {
        string token;
        istringstream str(line);
        bool cheated = false;
        while (getline(str, token, ';')) {
            auto words_begin = sregex_iterator(token.begin(), token.end(), r);
            auto words_end = sregex_iterator();

            for (sregex_iterator i = words_begin; i != words_end; ++i) {
                smatch match = *i;
                if (stoi(match[1].str()) > colorCounts[match[2].str()])
                    cheated=true;
            }
        }
        if (!cheated)
            res += id;
        id++;
    }
    
    cout << res << endl;
    return 0;
}