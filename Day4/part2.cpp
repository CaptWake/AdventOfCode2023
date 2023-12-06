#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int getCardPoints(vector<int> cardNumbers, unordered_map<int, int> winningNumbers) {
    return count_if(cardNumbers.begin(), cardNumbers.end(), [winningNumbers](auto& cardNumber) { return winningNumbers.count(cardNumber) == 1; });
}

pair<vector<int>, unordered_map<int, int>> getCard(pair<string, string> str) {
    vector<int> cardNumbers;
    unordered_map<int, int> winningNumbers;
    string delimiter = " ";
    size_t pos = 0;
    string token;

    while ((pos = str.first.find(delimiter)) != std::string::npos) {
        token = str.first.substr(0, pos);
        if (token.length()) {
            //cout << token << endl;
            cardNumbers.push_back(stoi(token));
        }
        str.first.erase(0, pos + delimiter.length());
    }
    while ((pos = str.second.find(delimiter)) != std::string::npos) {
        token = str.second.substr(0, pos);
        if (token.length()) {
            //cout << token << endl;
            winningNumbers.insert({stoi(token), 1});
        }
        str.second.erase(0, pos + delimiter.length());
    }
    winningNumbers.insert({stoi(str.second), 1});
    pair<vector<int>, unordered_map<int, int>> card{cardNumbers, winningNumbers};
    return card;
}


pair<string, string> parseNumbers(string str) {
    string delimiter = "|";
    string cardNumbers = str.substr(0, str.find(delimiter));
    string winningNumbers = str.substr(str.find(delimiter)+1, str.size());
    pair<string, string> numbers{cardNumbers, winningNumbers};
    return numbers;
}

int main()
{
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }

    vector<int> copies;
    int res = 0;
    string line;

    while (getline(infile, line)) {
        string token;
        istringstream str(line);
        while (getline(str, token, ':')) {
            getline(str, token);
            auto r = parseNumbers(token);
            auto r_ = getCard(r);
            auto points = getCardPoints(r_.first, r_.second);
            if (points)
                res += pow(2, points -1);
        }
    }
    
    cout << res << endl;
    return 0;
}