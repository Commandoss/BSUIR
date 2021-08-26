//
//  main.cpp
//  Project
//
//  Created by Belousov Ilya on 17.08.21.
//

#include <iostream>
using namespace::std;

#include <sstream>
std::string highAndLow(const std::string& numbers){
    stringstream ss(numbers);
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    int temp;
    while (ss >> temp) {
        min = (min > temp) ? temp : min;
        max = (max < temp) ? temp : max;
    }
    
    return to_string(max) + " " + to_string(min);
}

#include <cmath>
long int findNextSquare(long int sq) {
    return (sqrt(sq) == static_cast<int>(sqrt(sq))) ? pow(sqrt(sq) + 1, 2) : -1;
}

#include <utility>
#include <vector>

unsigned int number(const std::vector<std::pair<int, int>>& busStops){
    int passengers = 0;
    for_each(busStops.begin(), busStops.end(), [&passengers](std::pair<int, int> par) {
        passengers += par.first;
        passengers -= par.second;
    });
    return passengers;
}

std::string get_middle(std::string input) {
    size_t pos = input.size();
    return (pos % 2 == 0) ? input.substr(pos / 2 - 1, 2) : input.substr(pos / 2, 1);
}

#include <string>
bool solution(std::string const &str, std::string const &ending) {
    return str.size() >= ending.size() && str.compare(str.size() - ending.size(), std::string::npos, ending) == 0;

}

class Accumul
{
public:
    static std::string accum(const std::string &s) {
        stringstream result;
        for (int i = 0; i < s.length(); i++)
          result << "-" << string(1, toupper(s[i])) << string(i, tolower(s[i]));
        return result.str().substr(1);
    }
    
    std::vector<std::string> towerBuilder(const int nFloors)
    {
        vector<string> tower;
        for (int i = 0, n = 1, k = nFloors - 1; i < nFloors; i++, n += 2, k--) {
            stringstream ss;
            ss << string(k, ' ') << string(n, '*') << string(k, ' ');
            tower.push_back(ss.str());
        }
        return tower;
    }
};

#include <istream>
std::string highestScoringWord(const std::string &str)
{
    stringstream ss(str);
    string answer;
    vector<string> words(std::istream_iterator<std::string>{ss}, std::istream_iterator<string>());
    int counter = 0, max = 0;
    for (auto word : words) {
        int score = 0;
        for (auto symbol : word)
            score += (int)symbol - 96;
        if (score > max) {
            max = score;
            answer = word;
        }
        
    }
  return answer;
}

#include <iomanip>
static std::string rgb(int r, int g, int b) {
    std::stringstream ss;
    ss.setf(std::ios_base::hex, std::ios_base::basefield);
    ss.setf(std::ios_base::uppercase);
    ss << std::setfill('0') << std::setw(2) << (r < 0 ? 0 : r > 255 ? 255 : r)
       << std::setw(2) << (g < 0 ? 0 : g > 255 ? 255 : g)
       << std::setw(2) << (b < 0 ? 0 : b > 255 ? 255 : b);
    return ss.str();
}

int solution(int number) {
    int sum = 0;
    for (int i = 0; i < number && number > 0; i++)
        sum += (i % 3 == 0 || i % 5 == 0) ? i : 0;
    return sum;
}

bool isPrime(int num) {
    if (num <= 3) {
        return num > 1;
    } else if (num % 2 == 0 || num % 3 == 0) {
        return false;
    } else {
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

//bool isPrime(int num) {
//  for(int i = 2; i <= sqrt(num); i++) if(num % i == 0) return false;
//  return num <= 1? false : true;
//}

#include <numeric>
std::string tickets(const std::vector<int>& peopleInLine) {
    int64_t sum = 0;
    for_each(peopleInLine.begin(), peopleInLine.end(), [&sum](int num) {
        sum < 0 || num < 25 ? sum = -1 : num > 25 ? sum -= (num - 25) : sum += num;
    });
    return sum >= 0 ? "YES" : "NO";
}

bool valid_braces(std::string braces) {
    std::stringstream ss(braces);
    std::string buffer;
    char symbol;
    while (ss >> symbol) {
        if (symbol == ')' || symbol == '}' || symbol == ']') {
            if (symbol == ')' && buffer.back() == '(') buffer.pop_back();
            else if (symbol == ']' && buffer.back() == '[') buffer.pop_back();
            else if (symbol == '}' && buffer.back() == '{') buffer.pop_back();
            else return false;
            continue;
        }
        buffer.push_back(symbol);
    }
    return true;
}

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int>& numbers, int target) {
    vector<int> num(numbers);
    for (auto end = num.end(); end > num.begin(); end--) {
        for (int i = 0, current = num.back(); i < num.size() - 1; i++) {
            if (num[i] + current == target) {
                return {i, num.size() - 1};
            }
        }
        num.pop_back();
    }
    return {0, 0};
}

bool solution1(const std::string& str, const std::string& ending) {
  return str.size() >= ending.size() && str.compare(str.size() - ending.size(), std::string::npos, ending) == 0;
}

int most_profit(const std::vector<int>& quotes)
{
    for_each(quotes.begin(), quotes.end(),[] {
        
    });
    return -1;
}

int main() {
    cout << solution1("abcde", "cde") << endl;
    cout << solution1("abcde", "abc") << endl;
    cout << solution1("abc", "") << endl;

}
