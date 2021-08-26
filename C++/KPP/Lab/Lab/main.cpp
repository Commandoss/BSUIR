//
//  main.cpp
//  Lab
//
//  Created by Belousov Ilya on 5.08.21.
//

#include <iostream>
#include <vector>

using namespace::std;

////int solution(const vector<int> &A) {
//    int number = 1;
//    for (int counter = 0; counter != A.size(); counter++) {
//    for (auto i = A.begin(); i != A.end(); i++) {
//        if (*i < 1) continue;
//        if (*i == number) {
//            number++;
//            break;
//
//        }
//    }
//    }
//    return number;
//}

int solution(const vector<int> &A) {
    int sum = 0;
    int idx = -1;
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] == 0)
        {
             idx = i;
        }
        else
        {
             sum += A[i];
        }
    }
    int total;
    std::cout << (A.size() + 1) * A.size() / 2;
    return total;
}


// the total sum of numbers between 1 and arr.length.

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> B;
    B.push_back(1);
    B.push_back(2);
    B.push_back(3);
//    B.push_back();
    std::cout << solution(B);
    return 0;
}
