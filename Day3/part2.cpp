
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "stdlib.h"

using namespace std;

unordered_map<string, vector<int>> gearMap; 

vector<pair<size_t, size_t>> getCoordinates(string str){
    size_t first = 0;
    size_t last = 0;
    bool lastDigit = false;
    vector<pair<size_t, size_t>> res {};
    for(size_t i = 0; i < str.size(); i++){
        if(isdigit(str[i])){
            if(!lastDigit){
                first = i;
                lastDigit = true;
            }
        } else {
            if(lastDigit){
                last = i - 1;
                pair<size_t, size_t> p {first, last};
                res.push_back(p);
                lastDigit = false;
            } 
        }
    }
    if(lastDigit){
        last = str.size() - 1;
        std::pair<size_t, size_t> p {first, last};
        res.push_back(p);
    }
    return res;
}

void updateGearMap(pair<int, int> gearCoords, int payload) {
    cout << "ciao" << endl;
    string key = "" + to_string(gearCoords.first) + "," + to_string(gearCoords.second);
    if (gearMap.find(key) != gearMap.end()) {
        gearMap[key].push_back(payload);
    } else {
        gearMap.insert({key, vector<int>{payload}}); 
    }
}

void checkGear(pair<int, int> gearCoords, vector<string> lines, size_t line, pair<size_t, size_t> coordinates) {
    cout << gearCoords.first << "\t" << gearCoords.second << endl;
    bool isGear = lines[gearCoords.first][gearCoords.second] == '*';
    if (isGear) {
        string n = lines[line].substr(coordinates.first, coordinates.second - coordinates.first + 1);
        updateGearMap(gearCoords, stoi(n));
    }
}

bool leftCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(coordinates.first > 0){
        if(line > 0){
            auto c = lines[line - 1][coordinates.first - 1];
            checkGear(pair<int,int>{line - 1, coordinates.first - 1}, lines, line, coordinates);
        }
        auto c = lines[line][coordinates.first - 1];
        checkGear(pair<int,int>{line, coordinates.first - 1}, lines, line, coordinates);
        if(line < lines.size() - 1){
            auto c = lines[line + 1][coordinates.first - 1];
            checkGear(pair<int,int>{line + 1, coordinates.first - 1}, lines, line, coordinates);
        }
    }
    return false;
}

bool rightCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(coordinates.second < lines[0].size() - 1){
        if(line > 0){
            auto c = lines[line - 1][coordinates.second + 1];
            checkGear(pair<int,int>{line - 1, coordinates.second + 1}, lines, line, coordinates);
        }
        auto c = lines[line][coordinates.second + 1];
        checkGear(pair<int,int>{line, coordinates.second + 1}, lines, line, coordinates);
        if(line < lines.size() - 1){
            auto c = lines[line + 1][coordinates.second + 1];
            checkGear(pair<int,int>{line + 1, coordinates.second + 1}, lines, line, coordinates);
        }
    }
    return false;
}

bool topCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(line > 0){
        for(size_t i = coordinates.first; i <= coordinates.second; i++ ){
            auto c = lines[line - 1][i];
            checkGear(pair<int,int>{line - 1, i}, lines, line, coordinates);
        }
    }
    return false;
}

bool botCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(line < lines.size() - 1){
        for(size_t i = coordinates.first; i <= coordinates.second; i++ ){
            auto c = lines[line + 1][i];
            //if(c != '.' && !isdigit(c) ){
            //    return true;
            //}
            checkGear(pair<int,int>{line + 1, i}, lines, line, coordinates);
        }
    }
    return false;
}
bool check(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    bool isTop = topCheck(lines, line, coordinates);  
    bool isBot = botCheck(lines, line, coordinates); 
    bool isRight = rightCheck(lines, line, coordinates); 
    bool isLeft = leftCheck(lines, line, coordinates);
    return isTop || isBot || isRight || isLeft;
}


int main() {
    
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }

    string line;
    vector<string> lines; 
    
    while(getline(infile >> std::ws, line)) {
        lines.push_back(line);
    }
    
    for(size_t i = 0; i < lines.size(); i++){
        auto ns = getCoordinates(lines[i]);
        for(auto n : ns)
            check(lines, i, n);
    }

    vector<int> partialProd(gearMap.size(), 0);

    std::transform(gearMap.begin(), gearMap.end(), partialProd.begin(), 
    [](auto& x) { 
        if (x.second.size() >= 2)
            return accumulate(x.second.begin(), x.second.end(), 1, multiplies<int>());
        else
            return 0;
    });

    std::cout << accumulate(partialProd.begin(), partialProd.end(), 0) << endl;  
}
