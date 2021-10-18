//Написать консольное приложение с использованием STL. +
//Программа принимает на вход в качестве аргументов имя текстового файла. +
//В программе реализована (исполняется) функция, принимающая в качестве аргументов Предикат. +
//По условию этого предиката в открытом текстовом файле удаляются все слова, ему удовлетворяющие.+
//После этого отредактированный файл сохраняется.+
//Требуется реализовать по меньшей мере два предиката, допустим, если слово полностью состоит только из цифр и если слово указано полностью в верхнем регистре.+

//Звездочка 1: Покрыть основные ключевые моменты unit тестами,
//  фрэймворк на ваше усмотрение.
//
//Звездочка 2: Сделать передачу в основную функцию (вместе с предикатом) объекта Callback'а, который будет дергаться при удовлетворении предиката. В обработчике этого Callback'а добавлять удаляемое слово (соотвутствущее условию предиката) в новый файл. Результатом выполнения приложения будет два сгенерирированных файла - содержимое одного будет исходный текст без слов, сооветствующим условию предиката, а содержимое второго будет состоять из удаленных слов.

#include <iostream>
#include <vector>
#include <string.h>

#include "predicates.h"
#include "filesys.h"

using namespace::std;

const string backupfile = "SYSTEMFILE.txt";
const string fileDeleteWord = "files/WordDelete.txt";

vector<const string> get_parameter(const int argc, char *argv[]) {
    vector<const string> param;
    for (auto i = 1; i < argc; i++) {
        param.push_back(static_cast<const string>(argv[i]));
    }
    return param;
}

void check_parameter(vector<const string> param) {
    for (auto path : param) {
        if (!check_path(path)) {
            cout << "File path: " << path << " specified incorrectly!" << endl;
            return;
        }
    }
}

vector<const string> input_parameter() {
    vector<const string> param;
    string path;
    
    cout << "Enter paths to files / file\n";
    do {
        cout << "Enter path: ";
        cin >> path;
        
        param.push_back(path);
        
        cout << "Do you want to continue?\n"
        << "1. Yes    2. No\n" << "Answer: ";
        clear_iostream();
    } while(cin.get() == '1');
    return param;
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<const string> param;
    if (argc >= 2) {
        param = get_parameter(argc, argv);
    } else {
        param = input_parameter();
    }
    
    auto userPredicates = set_predicates();
    auto predicates = get_transformed_predicates(userPredicates);
    
    string buffer;
    fstream fRead, fWrite, fWriteDeleted;
    
    remove_file(fileDeleteWord);

    
    for (auto path: param) {
        fWrite = create_file(backupfile);
        fRead = open_file(path);
        fWriteDeleted = create_file(fileDeleteWord);
        
        while (!fRead.eof()) {
            buffer = read_file(fRead);
            if (check_predicate(buffer, predicates)) {
                write_file(fWriteDeleted, buffer + " ");
                continue;
            }
            write_file(fWrite, buffer + " ");
            buffer.clear();
        }
        close_file(fRead);
        close_file(fWrite);
        close_file(fWriteDeleted);
        
        remove_file(path);
        rename_file(backupfile, path);
    }
    cout << endl;
    
    return 0;
}
