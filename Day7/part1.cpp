#include <vector>
#include <string.h>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

enum HandType{FiveOfAKind = 6, FourOfAKind = 5, FullHouse = 4, ThreeOfAKind = 3, TwoPair = 2, OnePair = 1, HighCard = 0};
map<char, int> cardValue{
        {'A', 13},
        {'K', 12},
        {'Q', 11},
        {'J', 1},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
};


typedef struct cardHand{
    char cards[5];
    HandType type;
    int bid;
} cardHand;

HandType getHandType(const char cards[]){
    map<char, int> cardCount{
        {'A', 0},
        {'K', 0},
        {'Q', 0},
        {'J', 0},
        {'T', 0},
        {'9', 0},
        {'8', 0},
        {'7', 0},
        {'6', 0},
        {'5', 0},
        {'4', 0},
        {'3', 0},
        {'2', 0},
    };
    for(int i = 0; i < 5; i++){
        cardCount[cards[i]] += 1;
    }
    vector<pair<char,int>> value;
    for(auto x : cardCount){
        value.push_back(x);
    }
    sort(value.begin(), value.end(), [](pair<char, int> a, pair<char, int> b){return a.second < b.second;});
    if(value[12].first != 'J')
        value[12].second += cardCount['J'];
    else{
        value[12].second += value[11].second;
    }
    if(value[12].second == 5){
        return FiveOfAKind;
    } else if(value[12].second == 4){
        return FourOfAKind;
    } else if(value[12].second == 3 && value[11].second == 2){
        return FullHouse;
    } else if(value[12].second == 3){
        return ThreeOfAKind;
    } else if(value[12].second == 2 && value[11].second == 2){
        return TwoPair;
    } else if(value[12].second == 2){
        return OnePair;
    } else {
        return HighCard;
    }
}

cardHand constructHand(const char cards[], const int bid){
    cardHand hand;
    strcpy(hand.cards, cards);
    hand.bid = bid;
    hand.type = getHandType(cards);
    return hand;
}

bool cardsCmp(const cardHand& first, const cardHand& second){
    if(first.type < second.type)
        return true;
    if(first.type > second.type)
        return false;
    for(int i = 0; i < 5; i++)
        if(cardValue[first.cards[i]] < cardValue[second.cards[i]])
            return true;
        else if(cardValue[first.cards[i]] > cardValue[second.cards[i]])
            return false;
    return false;
}


int main(){
    vector<cardHand> hands;

    std::ifstream infile("input2.txt");
    if (!infile.is_open()) {
        return 0;
    }

    string cards;
    string bid;
    while (getline(infile, cards, ' ')) {
        getline(infile, bid);
        hands.push_back(constructHand(cards.c_str(), stoi(bid)));
    }
    sort(hands.begin(), hands.end(), cardsCmp);
    long long sum = 0;
    for (int i = 0; i < hands.size(); ++i) {
        cout << hands[i].bid << " " << hands[i].cards << " " << hands[i].type<<endl;
        sum += hands[i].bid * (i + 1);
    }
    cout << sum << endl;
    return 0;
}