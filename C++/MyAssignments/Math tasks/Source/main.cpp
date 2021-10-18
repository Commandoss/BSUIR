//
//  main.cpp
//  LabWork
//
//  Created by Belousov Ilya

#include <iostream>
// Сумма натуральных чисел кратных 3 и 5
int main(int argc, const char * argv[]) {
    unsigned int limit = 0;
    std::cout << "Upper limit: ";
    std::cin >> limit;
    
    unsigned long long sum = 0;
    for (unsigned int i = 3; i < limit; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            sum += i;
        }
    }
    
    std::cout << "sum = " << sum << std::endl;
}


// Наибольший общий делитель
unsigned int gcd1(unsigned int const a, unsigned int const b) {
    return b == 0 ? a : gcd1(b, a % b);
}

unsigned int gcd2(unsigned int a, unsigned int b) {
    while(b != 0) {
        unsigned int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    std::cout << gcd1(15, 35);
    std::cout << gcd2(12, 24);
}

// Наименьшее общее кратное
int lcm(int const a, int const b) {
    int h = gcd1(a, b);
    return h ? (a * (b / h)) : 0;
}

// Наибольшее число меньше заданного
bool is_prime(int const num) {
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

int main() {
    unsigned int limit = 0;
    std::cout << "Upper limit: ";
    std::cin >> limit;
    
    for (int i = limit; i > 1; i--) {
        if (is_prime(i)) {
            std::cout << "Largest prime: " << i << std::endl;
            return 0;
        }
    }
}

// Простые числа отличающиеся на шесть
int main() {
    unsigned int limit = 0;
    std::cout << "Upper limit: ";
    std::cin >> limit;
    
    for (int n = 2; n <= limit; n++) {
        if (is_prime(n) && is_prime(n + 6)) {
            std::cout << n << "," << n + 6 << std::endl;
        }
    }
}

#include <cmath>
// Избыточные числа
int sum_proper_divisors(int const number) {
    int result = 1;
    for (int i = 2; i < std::sqrt(number); i++) {
        if (number % i == 0) {
            result += (i == (number / i)) ? i : (i + number / i);
        }
    }
    return result;
}

void print_abundant(int const limit) {
    for (int number = 10; number <= limit; ++number) {
        auto sum = sum_proper_divisors(number);
        if (sum > number) {
            std::cout << number << ", abundance = " << sum - number << std::endl;
        }
    }
}

int main() {
    int limit = 0;
    std::cout << "Upper limit: ";
    std::cin >> limit;
    
    print_abundant(limit);
}

// Избыточные числа
void print_amicables(int const limit) {
    for (int number = 3; number < limit; ++number) {
        auto sum1 = sum_proper_divisors(number);
        if (sum1 < limit) {
            auto sum2 = sum_proper_divisors(sum1);
            if (sum2 == number && number != sum1) {
                std::cout << number << "," << sum1 << std::endl;
            }
        }
    }
}

int main() {
    int limit = 0;
    std::cout << "Upper limit: ";
    std::cin >> limit;
    
    print_amicables(limit);
}

// Числа Амстронга
void print_narcissistics() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                auto abc = a * 100 + b * 10 + c;
                auto arm = a * a * a + b * b * b + c * c * c;
                if (abc == arm) {
                    std::cout << arm << std::endl;
                }
                
            }
        }
    }
}

int main() {
    print_narcissistics();
}


#include <vector>
// Простые множители
std::vector<unsigned long long> prime_factors(unsigned long long n) {
    std::vector<unsigned long long> factors;
    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }
    for (unsigned long long i = 3; i <= std::sqrt(n); i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }
    if (n > 2) {
        factors.push_back(n);
    }
    return factors;
}

int main() {
    unsigned long long number = 0;
    std::cout << "Number: ";
    std::cin >> number;
    
    auto factors = prime_factors(number);
    std::copy(std::begin(factors), std::end(factors),
              std::ostream_iterator<unsigned long long>(std::cout << " "));
}


#include <string.h>
// Код грея
unsigned int gray_encode(unsigned int const num) {
    return num ^ (num >> 1);
}

unsigned int gray_decode(unsigned int gray) {
    for (unsigned int bit = 1U << 31; bit > 1; bit >>= 1) {
        if (gray & bit ) gray ^= bit >> 1;
    }
    return gray;
}

std::string to_binary(unsigned int value, int const digits) {
    return std::bitset<32>(value).to_string().substr(32 - digits, digits);
}

int main() {
    std::cout << "Number\tBinary\tGray\tDecoded\n";
    std::cout << "------\t------\t----\t-------\n";
    
    for (unsigned int n = 0; n < 32; ++n) {
        auto encg = gray_encode(n);
        auto decg = gray_decode(encg);
        
        std::cout << n << "\t" << to_binary(n, 5) << "\t"
        << to_binary(encg, 5) << "\t" << decg << "\n";
    }
}

// Преобразование десятичных чисел в римские
std::string to_roman(unsigned int value) {
    std::vector<std::pair<unsigned int, char const *>> roman {
        {1000, ""}, {900, ""},  {500, ""},  {400, ""},
        {100, ""},  {90, ""},   {50, ""},   {40, ""},
        {10, ""},   {9, ""},    {5, ""},    {4, ""},    {1, ""}};
    
    std::string result;
    for (auto const & kvp : roman) {
        while (value >= kvp.first) {
            result += kvp.second;
            value -= kvp.first;
        }
    }
    return result;
}

int main() {
    for (int i = 1; i <= 100; ++i) {
        std::cout << i << "\t" << to_roman(i) << std::endl;
    }
}


// наибольшая последовательность Коллатца

std::pair<unsigned long long, long> longest_collatz(unsigned long long const limit) {
    long length = 0;
    unsigned long long number = 0;
    std::vector<int> cache(limit + 1, 0);
    
    for (unsigned long long i = 2; i <= limit; i++) {
        auto n = i;
        long steps = 0;
        while (n != 1 && n >= i) {
            if ((n % 2) == 0) n = n / 2;
            else n = n * 3 + 1;
            steps++;
        }
        
        if (cache[i] > length) {
            length = cache[i];
            number = i;
        }
    }
    return std::make_pair(number, length);
}

#include <random>
// Вычисление значенния числа ПИ
template <typename E = std::mt19937,
          typename D = std::uniform_real_distribution<>>

double compute_pi(E& engine, D& dist, int const samples = 1000000) {
    auto hit = 0;
    for (auto i = 0; i < samples; i++) {
        auto x = dist(engine);
        auto y = dist(engine);
        if (y <= std::sqrt(1 - std::pow(x, 2))) hit += 1;
    }
    return 4.0 * hit / samples;
}

int main() {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data),
                  std::ref(rd));
    
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    auto eng = std::mt19937 {seq};
    auto dist = std::uniform_int_distribution<>{0, 1};
    
    for (auto j = 0; j < 10; j++) {
        std::cout << compute_pi(eng, dist) << std::endl;
    }
    return 1;
}

// Проверка действительности номеров ISBN
bool validate_isbn_10(std::string_view isbn) {
    auto valid = false;
    if (isbn.size() == 10
        && std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10) {
        auto w = 10;
        auto sum = std::accumulate(std::begin(isbn), std::end(isbn), 0, [&w](int const total, char const c) {
            return total + w-- * (c - '0');
        });
        
        valid =!(sum % 11);
    }
    return valid;
}
                                
