////
////  main.cpp
////  Coursera
////
////  Created by Belousov Ilya on 16.11.21.
////
//
//using namespace::std;
//
//#define PRINT_VALUES(out, x, y) \
//    out << (x) << endl << (y) << endl
//
//#include <iostream>
//#include <vector>
//#include <stdexcept>
//#include <iterator>
//
//template <typename T>
//class Deque {
//private:
//    std::vector<T> front_;
//    std::vector<T> back_;
//public:
//    Deque(){};
//    const bool Empty() const {
//        if (front_.size() == 0 && back_.size() == 0) {
//            return true;
//        }
//        return false;
//    }
//    const size_t Size() const {
//        return front_.size() + back_.size();
//    }
//    void PushBack(T elem) {    // Под новую реализацию сделано!
//        back_.push_back(elem);
//    }
//    void PushFront(T elem) {   // Под новую реализацию сделано!
//        front_.push_back(elem);
//    }
//    T& Back() {               // Под новую реализацию сделано!
//        if (!back_.size()) {  // Элементов в зад добавлено не было
//            return front_.front();
//        }
//        return back_.back();
//    }
//    const T& Back() const {    // Под новую реализацию сделано!
//        if (!back_.size()) {  // Элементов в зад добавлено не было
//            return front_.front();
//        }
//        return back_.back();
//    }
//    T& Front() {               // Под новую реализацию сделано!
//        if (!front_.size()) {  // Элементов в перед добавлено не было
//            return back_.front();
//        }
//        return front_.back();
//    }
//    const T& Front() const {    // Под новую реализацию сделано!
//        if (!front_.size()) {  // Элементов в перед добавлено не было
//            return back_.front();
//        }
//        return front_.back();
//    }
//    T& operator[] (size_t index) {
//        if (front_.empty()) {
//            return back_[index];
//        }
//        if (back_.empty()) {
//            return *(std::next(front_.rbegin(), index));
//        }
//        if (index >= front_.size()) {
//            return back_[index - front_.size()];
//        }
//        return *(std::next(front_.rbegin(), index));
//    }
//    const T& operator[](size_t index) const {
//        if (front_.empty()) {
//            return back_[index];
//        }
//        if (back_.empty()) {
//            return *(std::next(front_.rbegin(), index));
//        }
//        if (index >= front_.size()) {
//            return back_[index - front_.size()];
//        }
//        return *(std::next(front_.rbegin(), index));
//    }
//    T& At(size_t index) {
//        if (index >= (front_.size() + back_.size())) {
//            throw std::out_of_range("out of range");
//        }
//        if (front_.empty()) {
//            return back_[index];
//        }
//        if (back_.empty()) {
//            return *(std::next(front_.rbegin(), index));
//        }
//        if (index >= front_.size()) {
//            return back_[index - front_.size()];
//        }
//        return *(std::next(front_.rbegin(), index));
//    }
//    const T& At(size_t index) const {
//        if (index >= (front_.size() + back_.size())) {
//            throw std::out_of_range("out of range");
//        }
//        if (front_.empty()) {
//            return back_[index];
//        }
//        if (back_.empty()) {
//            return *(std::next(front_.rbegin(), index));
//        }
//        if (index >= front_.size()) {
//            return back_[index - front_.size()];
//        }
//        return *(std::next(front_.rbegin(), index));
//    }
//};
//
//#include <iostream>
//#include <cmath>
//
//using namespace::std;
//
//#define MUL(a, b) (a * b)
//
//int main() {
//    double a = 11,
//           b = 1,
//           c = 11,
//           x = 12;
//
//    double result = (MUL(a, x) + MUL(b, x) + c)
//           / (MUL(b, pow(x, 2)) - sqrt(MUL(x + MUL(a, cos(x)), c)));
//    cout << "Result: " << result << endl;
//    return result;
//}


#include <iostream>

using namespace::std;

int main() {
    // cin -> поток ввода в приложение

    //      Массивы
    // [] -> оператор разыменовывания, а так же создания массива
    //    int mas[5]; -> создание массива
    //    cin >> mas[0]; -> разименовывание

    //      Циклы
//    1. while (значение)
//    int answer1 = 0;
//
//    cout << "Close programm?" << endl;
//    cout << "1.Yes" << " " << "2.No" << endl;
//    cout << "Answer: ";
//    cin >> answer1;
//    while (answer1 == 2) {
//        cout << "Hello" << endl;
//    }

////     2. Do/while(значение)
//    int answer = 0;
//    do {
//        int a, b;
//        cout << "Input a: ";
//        cin >> a;
//
//        cout << "Input b: ";
//        cin >> b;
//
//        cout << "a + b = " << a + b << endl;
//
//        cout << "Close programm?" << endl;
//        cout << "1.Yes" << " " << "2.No" << endl;
//        cout << "Answer: ";
//        cin >> answer;
//    } while(answer == 2);

//    3. For();
    int a = 0;
    for (int i = 0; i < 10; i++) {
        a++;
    }
    cout << a;

    return 0;
}

