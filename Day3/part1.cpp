
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

std::vector<std::pair<size_t, size_t>> getCoordinates(std::string str){
    size_t first = 0;
    size_t last = 0;
    bool lastDigit = false;
    std::vector<std::pair<size_t, size_t>> res {};
    for(size_t i = 0; i < str.size(); i++){
        if(isdigit(str[i])){
            if(!lastDigit){
                first = i;
                lastDigit = true;
            }
        } else {
            if(lastDigit){
                last = i - 1;
                std::pair<size_t, size_t> p {first, last};
                cout << p.first << "\t" << p.second << endl;
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
    cout << endl;
    return res;
}

bool leftCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(coordinates.first > 0){
        if(line > 0){
            auto c = lines[line - 1][coordinates.first - 1];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
        auto c = lines[line][coordinates.first - 1];
        if(c != '.' && !isdigit(c) ){
            return true;
        }
        if(line < lines.size() - 1){
            auto c = lines[line + 1][coordinates.first - 1];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
    }
    return false;
}

bool rightCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(coordinates.second < lines[0].size() - 1){
        if(line > 0){
            auto c = lines[line - 1][coordinates.second + 1];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
        auto c = lines[line][coordinates.second + 1];
        if(c != '.' && !isdigit(c) ){
            return true;
        }
        if(line < lines.size() - 1){
            auto c = lines[line + 1][coordinates.second + 1];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
    }
    return false;
}

bool topCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(line > 0){
        for(size_t i = coordinates.first; i <= coordinates.second; i++ ){
            auto c = lines[line - 1][i];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
    }
    return false;
}

bool botCheck(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    if(line < lines.size() - 1){
        for(size_t i = coordinates.first; i <= coordinates.second; i++ ){
            auto c = lines[line + 1][i];
            if(c != '.' && !isdigit(c) ){
                return true;
            }
        }
    }
    return false;
}
bool check(std::vector<std::string> lines, size_t line, pair<size_t, size_t> coordinates){
    bool isTop = topCheck(lines, line, coordinates);  
    bool isBot = botCheck(lines, line, coordinates); 
    bool isRight = rightCheck(lines, line, coordinates); 
    bool isLeft = leftCheck(lines, line, coordinates);
    cout << "isTop: " << isTop << endl;
    cout << "isBot: " << isBot << endl;
    cout << "isRight: " << isRight << endl;
    cout << "isLeft: " << isLeft << endl;
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
    
    int res = 0;
    for(size_t i = 0; i < lines.size(); i++){
        cout << "line : " << i << endl;
        cout << lines[i] << endl;
        auto ns = getCoordinates(lines[i]);
        for(auto n : ns){
            if(check(lines, i, n)){
                //cout << i << ", " << n.first << ", " << n.second << ", "<< lines[i].substr(n.first, n.second - n.first + 1) << "\n";
                res += stoi(lines[i].substr(n.first, n.second - n.first + 1));
            }
        }
    }
    cout << res << endl;  
}
