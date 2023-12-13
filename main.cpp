#include "HashMap.h"
#include "n-ary.h"
using namespace std;


int main() {
    // testing the actual method
    // main menu
    cout << "+-----------------------------------------------+" << endl;
    cout << "|    Welcome to Amazon Dupe! Choose the data    |" << endl;
    cout << "|          structure you want to store          |" << endl;
    cout << "|                    items in.                  |" << endl;
    cout << "+-----------------------------------------------+" << endl;
    cout << "|   1. Tree                                     |" << endl;
    cout << "|   2. Hashmap                                  |" << endl;
    cout << "+-----------------------------------------------+" << endl;

    int data_type;
    cin >> data_type;

    //tree to sort by price and sort by rating
    Tree price_tree, stars_tree;
    //hashmap to store all data
    HashMap hashmap;

    // parsing logic
    const std::string filename = "amazon_products.csv";
    std::ifstream userFile;
    userFile.open(filename);
    if (!userFile.is_open()) {
        std::cerr << "Couldn't read file: " << filename << std::endl;
        return 1;
    }

    // initializing no. of data points to read
    int rowsToParse = 100000;
    while (rowsToParse > 0) {
        std::string line;
        if (!std::getline(userFile, line)) {
            break;
        }

        std::istringstream ss(line);
        std::string asin,title,imgUrl,productURL,stars,reviews,price,listPrice,category_id,isBestSeller,boughtInLastMonth;

        // parsing and inserting into data structures
        //making sure requirements are met, comma delimiting
        if (getline(ss, asin, ',') && getline(ss, title, ',') && getline(ss, imgUrl, ',') &&
            getline(ss, productURL, ',') && getline(ss, stars, ',') && getline(ss, reviews, ',') &&
            getline(ss, price, ',') && getline(ss, listPrice, ','), getline(ss, category_id, ','),
                getline(ss, isBestSeller, ','),getline(ss, boughtInLastMonth, ',') && rowsToParse != 100000) {
            // insert into Tree
            price_tree.insert(title, std::stod(price), std::stod(stars));
            stars_tree.insert(title, std::stod(stars), std::stod(price));

            // insert into HashMap
            hashmap.insert(title, price, stars);


        }
        rowsToParse--;
    }

    userFile.close();

    while(true) {
        //Choose search type
        std::cout
                << "Choose whether you want to search for the exact title, or for a keyword.\n"
                   "1. Exact title\n"
                   "2. Keyword"
                << std::endl;
        int string_type;
        cin >> string_type;
        //Get search term
        std::cout << "Enter search term: " << std::endl;
        string s;
        getline(cin, s);
        getline(cin, s);

        int sort_by;
        //If not exact term, and searching by keyword, give option of sorting by price or rating
        if (string_type != 1) {
            std::cout
                    << "Choose whether you want the best items by price or rating.\n"
                       "1. Price\n"
                       "2. Rating"
                    << std::endl;
            cin >> sort_by;
        }

        //calling search functions from data structures to get vector of answers to print/return
        vector<Node *> vtree;
        vector<HashMap::HashNode> vmap;
        //tree functions
        if (data_type == 1) { //using tree calls
            if (string_type == 1) { //searching by exact term
                if (sort_by == 1) {
                    vtree = price_tree.find(s, true);
                    //printing out the value of the vectors, with price first
                    for (int i = 0; i < vtree.size(); i++) {
                        cout << vtree[i]->name << " | Price: $" << vtree[i]->value << " | Rating: " << vtree[i]->value2
                             << endl;
                    }
                } else {
                    vtree = stars_tree.find(s, false);
                    //printing out the value of the vectors, this time rating is first
                    for (int i = 0; i < vtree.size(); i++) {
                        cout << vtree[i]->name << " | Price: $" << vtree[i]->value2 << " | Rating: " << vtree[i]->value
                             << endl;
                    }
                }
            } else { //search by keyword
                if (sort_by == 1) {
                    vtree = price_tree.findKey(s, true);
                    for (int i = 0; i < vtree.size(); i++) {
                        cout << vtree[i]->name << " | Price: $" << vtree[i]->value << " | Rating: " << vtree[i]->value2
                             << endl;
                    }
                } else {
                    vtree = stars_tree.findKey(s, false);
                    for (int i = 0; i < vtree.size(); i++) {
                        cout << vtree[i]->name << " | Price: $" << vtree[i]->value2 << " | Rating: " << vtree[i]->value
                             << endl;
                    }
                }
            }

            //if sort_by = 1 -> node -> name, node -> value = price, node -> value2 = rating
            //if sort_by - 2 -> node -> name, node -> value2 = price, node -> value = rating
        } else { //Hashmap functions
            if (string_type == 1) {
                if (sort_by == 1) {
                    vmap = hashmap.searchName(s);
                } else {
                    vmap = hashmap.searchKeyword(s);
                }
            } else {
                if (sort_by == 1) { //Searching by right sort type
                    vmap = hashmap.searchKeywordPriceRating(s, 10000, "price");
                } else {
                    vmap = hashmap.searchKeywordPriceRating(s, 0, "rating");
                }
            }
            //Printing out vector of answers
            for (int i = 0; i < vmap.size(); ++i) {
                HashMap::HashNode hn = vmap[i];
                cout << hn.key << " | Price: $" << hn.value.first << " | Rating: " << hn.value.second << endl;
            }
        }
    }
    return 0;
}