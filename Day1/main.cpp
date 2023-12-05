#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool isDigitString(string line, int index, string num){
   return line.substr(index, num.length()) == num;
    
}

char myIsDigit(string line, int index){
    if(isdigit(line[index])){
        return line[index];
    } else if(isDigitString(line, index, "one") ){
        return '1';
    } else if(isDigitString(line, index, "two") ){
        return '2';
    } else if(isDigitString(line, index, "three") ){
        return '3';
    } else if(isDigitString(line, index, "four") ){
        return '4';
    } else if(isDigitString(line, index, "five") ){
        return '5';
    } else if(isDigitString(line, index, "six") ){
        return '6';
    } else if(isDigitString(line, index, "seven") ){
        return '7';
    } else if(isDigitString(line, index, "eight") ){
        return '8';
    } else if(isDigitString(line, index, "nine") ){
        return '9';
    }
    return 0;
}

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
        char first{}, last{};
        for (int i = 0; first == 0 || last == 0 ; ++i) {
            if (first == 0)
                first = myIsDigit(line, i);
            if (last == 0)
                last = myIsDigit(line, N - i);
        }
        string number = string() + first + last;
        res += stoi(number);
    }
    
    cout << res << endl;
    return 0;
}
