#include "HashMap.h"

//constructor, initialize all values in table to null
HashMap::HashMap() {
    table = new HashNode * [TABLESIZE];
    for(int i = 0; i < TABLESIZE; i++)
    {
        table[i] = nullptr;
    }
    numNodes = 0;
}

//hashing function, will use C++ std library's hashing function, modulo table size to ensure it fits within table array
int HashMap::hashFunction(std::string k) {
    return std::hash<string>{}(k) % TABLESIZE;
}

//Insert function, to create HashNode representing product and store it in array
void HashMap::insert(std::string name, std::string price, std::string rating) {
    //get hash value/table index for our key
    int hash = hashFunction(name);

    //iterate thru table to see if collision will occur
    while(table[hash] != nullptr && table[hash]->key != name)
    {
        hash += 1; //linear probing in case of collision
        if(hash > TABLESIZE)
        {
            return;
        }
    }

    if(table[hash] != nullptr)
    {
        delete table[hash];
    }

    //create HashNode and place it in the table, update size
    pair<float, float> p = make_pair(stof(price), stof(rating));
    table[hash] = new HashNode(name, p);
    numNodes++;

    //resizing the table once load factor goes over a max value
    if(this->loadFactor() > 0.9)
    {
        HashNode** table2 = new HashNode * [2 * TABLESIZE];
        for(int i = 0; i < TABLESIZE; i++)
        {
            table2[i] = table[i];
        }
        table = table2;
    }
}

//searching for exact name, use properties of hash table to search based on hash value
vector<HashMap::HashNode> HashMap::searchName(std::string name) {
    vector<HashMap::HashNode> ans;
    int hash = hashFunction(name);
    while(table[hash] != nullptr && table[hash]->key != name)
    {
        hash += 1; //to get to the hash key we used when adding it to table
        if(hash > TABLESIZE)
        {
            return ans; //empty vector since name doesn't exist
        }
    }

    if(table[hash] == nullptr)
    {
        return ans;
    }
    else
    {
        ans.push_back(*table[hash]);
        return ans;
    }
}

//Destructor to delete pointers to the hashnodes and table itself
HashMap::~HashMap() {
    for(int i = 0; i < TABLESIZE; i++)
    {
        if(table[i] != nullptr)
        {
            delete table[i];
        }
    }
    delete[] table;
}

//function to return size of table
int HashMap::size() {
    return numNodes;
}

//function for loadFactor calculation
float HashMap::loadFactor() {
    return numNodes/TABLESIZE;
}

//Function to search for a keyword; this will require iterating through entire table
vector<HashMap::HashNode> HashMap::searchKeyword(string keyword) {
    vector<HashMap::HashNode> ans;
    for(int i = 0; i < TABLESIZE; i++)
    {
        if(table[i] != nullptr)
        {
            string product = table[i]->key;
            //add any product whose name contains the keyword
            if (product.find(keyword) != string::npos) {
                ans.push_back(*(table[i]));
            }
        }
    }
    return ans;
}


//Function to search by a keyword for the 5 cheapest items under a specific price or the 5 top items over a certain rating
vector<HashMap::HashNode> HashMap::searchKeywordPriceRating(std::string keyword, float priceOrating, std::string por) {
    vector<HashMap::HashNode> ans;
    if(por == "price") //searching by keyword and price
    {
        //pq to compare by price
        priority_queue<HashNode, vector<HashNode>, ComparePrice> pq1;
        for(int i = 0; i < TABLESIZE; i++)
        {
            if(table[i] != nullptr)
            {
                string prod = table[i] -> key;
                float pr = table[i]->value.first;
                if(prod.find(keyword)!= string::npos && pr <= priceOrating)
                {
                    //add all products under the price threshold
                    pq1.push(*table[i]);
                }
            }
        }

        while(ans.size() < 5 && !pq1.empty())
        {
            //return the 5 cheapest items, or however many exist under threshold
            ans.push_back(pq1.top());
            pq1.pop();
        }
    }
    else if(por == "rating") //searching by keyword and rating
    {
        //priority queue to compare by ratings
        priority_queue<HashNode, vector<HashNode>, CompareRating> pq2;
        for(int i = 0; i < TABLESIZE; i++)
        {
            if(table[i] != nullptr)
            {
                string prod = table[i] -> key;
                float rate = table[i]->value.second;
                if(prod.find(keyword)!= string::npos && rate >= priceOrating)
                {
                    //add all products over minimum rating
                    pq2.push(*table[i]);
                }
            }
        }

        while(ans.size() < 5 && !pq2.empty())
        {
            //return only 5 top rated items, or how ever many above the minimum rating
            ans.push_back(pq2.top());
            pq2.pop();
        }
    }
    return ans;
}