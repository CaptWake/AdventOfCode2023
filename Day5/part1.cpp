#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <functional>
#include <numeric>
#include <ranges>

using namespace std;

struct seedMap{
    long long dest;
    long long source;
    long long length;
};

vector<long long> getSeeds(string str){
    long long i = 0;
    stringstream ss{str};
    string s;
    vector<long long> res{};
    while(getline(ss, s, ' ')){
        res.push_back(stoll(s));
    }
    return res;
}

vector<vector<seedMap>> getMaps(string str){
    stringstream ss1{str};
    string s1;
    vector<vector<seedMap>> res {};
    while(getline(ss1, s1, '#')){
        stringstream ss2 {s1};
        string s2;
        vector<seedMap> maps{};
        seedMap map {};
        while(getline(ss2, s2, ' ')){
            map.dest = stoll(s2);
            getline(ss2, s2, ' ');
            map.source = stoll(s2);
            getline(ss2, s2, ' ');
            map.length = stoll(s2);
            maps.push_back(map);
        }
        res.push_back(maps);
    }
    return res;
}

long long applyMap(vector<seedMap> maps, long long seed){
    vector<seedMap> filteredMaps{};
    copy_if(maps.cbegin(), maps.cend(), back_inserter(filteredMaps), [seed](auto map){
        return map.source <= seed && seed <= map.source + map.length;
    });
    return filteredMaps.size() > 0 ? seed + filteredMaps[0].dest - filteredMaps[0].source : seed;
}

int main(){
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }

    vector<long long> copies;
    long long res = 0;
    string line1;
    string line2;
    getline(infile, line1, '#');
    getline(infile, line2);

    auto seeds{getSeeds(line1)};
    auto maps{getMaps(line2)};
    for_each(maps.begin(), maps.end(), [](auto x){
        for_each(x.begin(), x.end(), [](auto y){
            cout << y.dest << " " << y.source << " " << y.length << endl;
        });
    });
    using namespace std::placeholders;
    vector<function<long long(long long)>> f {};
    auto fs = accumulate(maps.begin(), maps.end(), f, [](auto fs, auto map){
        fs.push_back(bind(applyMap, map, _1));
        return fs;
    });
    transform(seeds.cbegin(), seeds.cend(), seeds.begin(), [fs](long long seed){
        return accumulate(fs.begin(), fs.end(), seed, [](auto s, auto f1){
            return f1(s);
        });
    });
    cout << min_element(seeds.begin(), seeds.end())[0] << endl;
    
}
