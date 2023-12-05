
#include <vector>
#include <string>
#include <iostream>
using namespace std;


std::vector<std::string> getLines(std::string& str){
   std::vector<std::string> lines {};
   size_t pos {0};
   std::string token;
   while((pos = str.find("\n")) != std::string::npos){
      token = str.substr(0, pos);
      lines.push_back(token);
      str.erase(0, pos + 1);
   }
   lines.push_back(str);
   return lines;
}

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
    if(coordinates.first < lines[0].size()){
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
    return  topCheck(lines, line, coordinates)   || 
            botCheck(lines, line, coordinates)   || 
            rightCheck(lines, line, coordinates) || 
            leftCheck(lines, line, coordinates); 
}


int main(){
    std::string str {"467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598.."};
    auto lines = getLines(str);
    int res = 0;
    for(size_t i = 0; i < lines.size(); i++){
        auto ns = getCoordinates(lines[i]);
        for(auto n : ns){
            if(check(lines, i, n)){
                //cout << i << ", " << n.first << ", " << n.second << ", "<< lines[i].substr(n.first, n.second - n.first + 1) << "\n";
                res += stoi(lines[i].substr(n.first, n.second - n.first + 1));
            }
        }
    }
    cout << res;  
}
