//
//  Predicates.h
//  LLL
//
//  Created by Belousov Ilya on 16.08.21.
//

#ifndef predicates_h
#define predicates_h

#include <iostream>
#include <vector>
#include <string.h>
#include <locale.h>

using namespace::std;

void clear_iostream() {
    cin.ios_base::clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

vector<const string> set_predicates() {
    vector<const string> predicates;
    string predicat;
    
    do {
        cout << "Enter predicate: ";
        cin >> predicat;
        
        predicates.push_back(predicat);
        
        cout << "Do you want to continue?\n"
        << "1. Yes    2. No\n" << "Answer: ";
        clear_iostream();
    } while(cin.get() == '1');
    
    return predicates;
}

vector<const string> get_transformed_predicates(const vector<const string> predicates) {
    vector<const string> vPredicates;
    string buffer;
    
    for (auto word : predicates) {
        for (auto symbol : word) {
            if (islower(symbol)) {
                buffer.push_back('l');
            } else if (isupper(symbol)) {
                buffer.push_back('u');
            } else if (isdigit(symbol)) {
                buffer.push_back('n');
            } else {
                buffer.push_back('?');
            }
        }
        vPredicates.push_back(buffer);
        buffer.clear();
    }
    return vPredicates;
}

string get_transformed_predicate(const string line) {
    string buffer;
    for (auto symbol : line) {
        if (islower(symbol)) {
            buffer.push_back('l');
        }
        else if (isupper(symbol)) {
            buffer.push_back('u');
        }
        else if (isdigit(symbol)) {
            buffer.push_back('n');
        } else {
            buffer.push_back('?');
        }
    }
    return buffer;
}

bool check_predicate(const string line, const vector<const string> predicates) {
    string buffer = get_transformed_predicate(line);
    for (auto word : predicates) {
        if ((word.compare(buffer) == 0) && (word.size() == buffer.size())) {
            cout << buffer << endl;
            return true;
        }
    }
    return false;
}

#endif /* Predicates_h */
