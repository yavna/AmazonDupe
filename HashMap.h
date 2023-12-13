#pragma once
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//value of initial map size/capacity
const int TABLESIZE = 150000;

//Citation: https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables
class HashMap{

private:
    int hashFunction(string k);
    int numNodes;

public:
    //struct to hold values within hash table; will store key (product name), and values (pair of price and rating)
    struct HashNode{
        string key;
        pair<float, float> value;
        HashNode(string k, pair<float, float> v){
            key = k;
            value = v;
        }
    };
    HashNode** table; //pointer to pointer; pointer to array of hashnode pointers

    //public functions
    HashMap();
    void insert(string name, string price, string rating);
    vector<HashNode> searchName(string name);
    vector<HashNode> searchKeyword(string keyword);
    vector<HashNode> searchKeywordPriceRating(string keyword, float priceOrating, string por);
    ~HashMap();
    int size();
    float loadFactor();

    //comparator to sort prices of objects
    struct ComparePrice{
        bool operator()(HashNode const& h1, HashNode const& h2)
        {
            return h1.value.first > h2.value.first;
        }
    };

    //comparator to sort ratings of objects
    struct CompareRating{
        bool operator()(HashNode const& h1, HashNode const& h2)
        {
            return h1.value.second < h2.value.second;
        }
    };
};
