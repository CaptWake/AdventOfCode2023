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
typedef long long ll;

struct seed{
    ll start;
    ll range;
};

struct seedMap{
    ll dest;
    ll source;
    ll length;
};

vector<seed> getSeeds(string str){
    ll i = 0;
    stringstream ss{str};
    string s;
    vector<seed> res{};
    while(getline(ss, s, ' ')){
        seed seed_;
        seed_.start = stoll(s);
        getline(ss, s, ' ');
        seed_.range = stoll(s);
        res.push_back(seed_);
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

vector<seed> applyMap(vector<seedMap>& maps, seed seed_, int i=0){
    if(maps.size() == i)
        return {seed_};

    vector<seed> res; 
    auto map = maps[i];
    auto min_seed_val = seed_.start;
    auto max_seed_val = seed_.start + seed_.range - 1;
    auto upper_bound = map.source + map.length - 1;
    auto lower_bound = map.source;   
    
    if(lower_bound <= min_seed_val && min_seed_val <= upper_bound) {
        if (max_seed_val <= upper_bound) {
            res.push_back(seed{map.dest + min_seed_val - lower_bound, seed_.range});
            return res;
        } else {
            res.push_back(seed{map.dest + min_seed_val - lower_bound, upper_bound - min_seed_val+1});
            auto right = applyMap(maps, seed{upper_bound+1, max_seed_val-upper_bound}, ++i);
            res.insert(res.end(), right.begin(), right.end());
            return res;
        }
    } else if(min_seed_val < lower_bound && lower_bound <= max_seed_val) {
        if (max_seed_val <= upper_bound) {
            res.push_back(seed{map.dest, max_seed_val - lower_bound+1});
            auto left = applyMap(maps, seed{min_seed_val, lower_bound-min_seed_val}, ++i);
            res.insert(res.end(), left.begin(), left.end());
            return res;
        } else { 
            res.push_back(seed{map.dest, map.length});
            auto left = applyMap(maps, seed{min_seed_val, lower_bound-min_seed_val}, ++i);
            auto right = applyMap(maps, seed{upper_bound+1, max_seed_val-upper_bound}, ++i);
            res.insert(res.end(), left.begin(), left.end());
            res.insert(res.end(), right.begin(), right.end());
            return res;
        }
    } else {
        return applyMap(maps, seed_, ++i);
    }
}

int main(){
    std::ifstream infile("input.txt");
    if (!infile.is_open()) {
        return 0;
    }

    // vector<ll> copies;
    // ll res = 0;
    string line1;
    string line2;
    getline(infile, line1, '#');
    getline(infile, line2);

    auto seeds{getSeeds(line1)};
    auto maps{getMaps(line2)};
    
    ll min_el = __LONG_LONG_MAX__;

    for (auto& s: seeds) {
        vector<seed> res{s};
        for(auto& map: maps) {
            vector<seed> temp{};
            for(auto& r: res) {
                auto t = applyMap(map, r);
                temp.insert(temp.end(), t.begin(), t.end());
            }
            res = temp;
        }

        for(auto& r: res) {
            if (r.start < min_el)
                min_el = r.start;
        }
    }

    cout << min_el << endl;
    
#ifdef DEBUG
    cout << "======= SEEDS ========" << endl;
    for_each(seeds.begin(), seeds.end(), [](auto x){
            cout << x.start << " " << x.range << endl;
    });

    cout << "======= MAPS ========" << endl;
    for_each(maps.begin(), maps.end(), [](auto x){
        for_each(x.begin(), x.end(), [](auto y){
            cout << y.dest << " " << y.source << " " << y.length << endl;
        });
    });
#endif



}
