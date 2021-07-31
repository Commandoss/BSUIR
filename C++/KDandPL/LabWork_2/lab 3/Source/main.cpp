//
//  main.cpp
//  lab 3
//
//  Created by Belousov Ilya on 9/11/20.
//  Copyright © 2020 Belousov Ilya. All rights reserved.
//

#include "String.h"
#include <vector>

#define USER_CL_PROGRAM 1

enum Menu {
    sum = 1,
    sumAsig,
    asig,
    equa,
    inequal,
    tSequn,
    getPos,
    more,
    les
}; Menu m;



int main() {
    ios_base::sync_with_stdio();

    cString line1("Helloy ");
    cString line2("World!");
    cString line3("I study language C++ Helloy  12");
    cString line4("It is very intresting.");
    cString line5, line6, line7, line8;

    int answer = 2;
    const int MAX_NUM_ELEMENTS_CL = 4;
    int cMas[MAX_NUM_ELEMENTS_CL];
    for (int i = 0; i < MAX_NUM_ELEMENTS_CL; i++) cMas[i] = 0;

    //    while (true) {

    cout << "\tHow do you want to set string?\n";
    cout << "1. Manual imput.\n"
    "2. Auto imput.\n"
    "Answer: ";
    cin >> answer;

    if (answer == 1) {
//        
//        cout << "\tWhat types do you want to use?\n";
//        cout << "1. Class object.\n"
//        "2. Sting.\n"
//        "3. Char.\n"
//        "4. Int.\n"
//        "Answer: ";
//        cin >> answer;
//
//        cout << "How many objects to create?\n";
//        cout << "Answer: ";
//        cin >> answer;
//        vector<cString> VcPer(answer)
//
//        switch(answer) {
//            case 1:
//                for (int i = 0; i < answer; i++) {
//
//                }
//
//        }
        cout << "Enter the text for line #1: ";
        rewind(stdin);
        cin >> line1;

        cout << "Enter the text for line #2: ";
        rewind(stdin);
        cin >> line2;

        cout << "Enter the text for line #3: ";
        rewind(stdin);
        cin >> line3;

        cout << "Enter the text for line #4: ";
        rewind(stdin);
        cin >> line4;
    }
    cString line10 = line1 + line2 += line3 + "950503" + line2(3, 7);
    cout << "\n\tLine text:";
    cout << "\nline #1: " << line1 << " Size: " << line1.getsize();
    cout << "\nline #2: " << line2 << " Size: " << line2.getsize();
    cout << "\nline #3: " << line3 << " Size: " << line3.getsize();
    cout << "\nline #4: " << line4 << " Size: " << line4.getsize() << endl;
    //нужно сделать паузу

    cout << "\tWhat do you want to do with strings?\n";
    cout << "1. Summation.\n"
    "2. Summation over assignment.\n"
    "3. Assignment.\n"
    "4. Equality.\n"
    "5. Inequality.\n"
    "6. Taking a sequence.\n"
    "7. Get position[].\n"
    "8. More.\n"
    "9. Less.\n"
    "Answer: ";
    cin >> answer;

    if (answer <= 9) {
        int pos = 0, info = 1, counter = 0;
        cout << "\n\tWhat lines do you want to use for this operation?\n";
        while (counter < MAX_NUM_ELEMENTS_CL) {
            counter++;
            cout << "Enter line numbers: ";
            cin >> pos; pos--;

            if (cMas[pos] != 1)
                cMas[pos] = true;
            else {
                cout << "Sorry but this element is already in use!" << endl;;
                counter--;
            }

            if (counter != 4 || answer == 1) {
                cout << "\nDo you want to ask more?";
                cout << "\n1. YES  2. NO\nAnswer: ";
                cin >> info;
            }
            if (info == 2) break;
        }
    }

    int pos1 = 0, pos2 = 0;
    char symbol;
    switch (answer) {
        case sum:
            if ((cMas[0] && cMas[1]) == true) { //???
                line5 = line1 + line2;
            }
            if ((cMas[0] && cMas[2]) == true) {
                line5 = line1 + line3;
            }
            if ((cMas[0] && cMas[3]) == true) {
                line5 = line1 + line4;
            }
            if ((cMas[1] && cMas[2]) == true) {
                line5 = line2 + line3;
            }
            if ((cMas[1] && cMas[3]) == true) {
                line5 = line2 + line4;
            }
            if ((cMas[2] && cMas[3]) == true) {
                line5 = line3 + line4;
            }

            break;

        case sumAsig:
            if ((cMas[0] && cMas[1]) == true) {
                line1 += line2;
            }
            if ((cMas[0] && cMas[2]) == true) {
                line1 += line3;
            }
            if ((cMas[0] && cMas[3]) == true) {
                line1 += line4;
            }
            if ((cMas[1] && cMas[2]) == true) {
                line2 += line3;
            }
            if ((cMas[1] && cMas[3]) == true) {
                line2 += line4;
            }
            if ((cMas[2] && cMas[3]) == true) {
                line3 += line4;
            }

            break;

        case asig:
            if ((cMas[0] && cMas[1]) == true) {
                line1 = line2;
            }
            if ((cMas[0] && cMas[2]) == true) {
                line1 = line3;
            }
            if ((cMas[0] && cMas[3]) == true) {
                line1 = line4;
            }
            if ((cMas[1] && cMas[2]) == true) {
                line2 = line3;
            }
            if ((cMas[1] && cMas[3]) == true) {
                line2 = line4;
            }
            if ((cMas[2] && cMas[3]) == true) {
                line3 = line4;
            }

            break;

        case equa:
            if ((cMas[0] && cMas[1]) == true) {
                if ((line1 == line2) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }
            if ((cMas[0] && cMas[2]) == true) {
                if ((line1 == line3) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }
            if ((cMas[0] && cMas[3]) == true) {
                if ((line1 == line4) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }
            if ((cMas[1] && cMas[2]) == true) {
                if ((line2 == line3) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }
            if ((cMas[1] && cMas[3]) == true) {
                if ((line2 == line4) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }
            if ((cMas[2] && cMas[3]) == true) {
                if ((line3 == line4) == true) cout << "\nStrings match.\n";
                else cout << "\nStrings don't match.\n";
            }

            break;

        case inequal:
            if ((cMas[0] && cMas[1]) == true) {
                if ((line1 != line2) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }
            if ((cMas[0] && cMas[2]) == true) {
                if ((line1 != line3) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }
            if ((cMas[0] && cMas[3]) == true) {
                if ((line1 != line4) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }
            if ((cMas[1] && cMas[2]) == true) {
                if ((line2 != line3) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }
            if ((cMas[1] && cMas[3]) == true) {
                if ((line2 != line4) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }
            if ((cMas[2] && cMas[3]) == true) {
                if ((line3 != line4) == true) cout << "\nStrings don't match.\n";
                else cout << "\nStrings match.\n";
            }

            break;

        case tSequn:
            cout << "\nSet positions taking sequence: ";
            cin >> pos1 >> pos2;
            if (cMas[0] == true) {
                line5 = line1(pos1, pos2);
            }
            if (cMas[1] == true) {
                line6 = line2(pos1, pos2);
            }
            if (cMas[2] == true) {
                line7 = line3(pos1, pos2);
            }
            if (cMas[3] == true) {
                line8 = line4(pos1, pos2);
            }

            break;

        case getPos:
            cout << "\nSet symbol: ";
            cin >> symbol;
            if (cMas[0] == true) {
                cout << "\nline #1: ";
                if(line1[symbol] == true) cout << "\n\tThe specified item was found.\n";
                else cout << "\n\tThe element you are looking for is missing in the given string.\n";
            }
            if (cMas[1] == true) {
                cout << "line #2: ";
                if(line2[symbol] == true) cout << "\n\tThe specified item was found.\n";
                else cout << "\n\tThe element you are looking for is missing in the given string.\n";
            }
            if (cMas[2] == true) {
                cout << "line #3: ";
                if(line3[symbol] == true) cout << "\n\tThe specified item was found.\n";
                else cout << "\n\tThe element you are looking for is missing in the given string.\n";
            }
            if (cMas[3] == true) {
                cout << "line #4: ";
                if(line4[symbol] == true) cout << "\n\tThe specified item was found.\n";
                else cout << "\n\tThe element you are looking for is missing in the given string.\n";
            }

            break;

        case more:
            if ((cMas[0] && cMas[1]) == true) {
                if ((line1 > line2) == true) cout << "Line #1 greater than line #2";
                else cout << "Line #2 greater than line #1";
            }
            if ((cMas[0] && cMas[2]) == true) {
                if ((line1 > line3) == true) cout << "Line #1 greater than line #3";
                else cout << "Line #3 greater than line #1";
            }
            if ((cMas[0] && cMas[3]) == true) {
                if ((line1 > line4) == true) cout << "Line #1 greater than line #4";
                else cout << "Line #4 greater than line #1";
            }
            if ((cMas[1] && cMas[2]) == true) {
                if ((line2 > line3) == true) cout << "Line #2 greater than line #3";
                else cout << "Line #3 greater than line #2";
            }
            if ((cMas[1] && cMas[3]) == true) {
                if ((line2 > line4) == true) cout << "Line #2 greater than line #4";
                else cout << "Line #4 greater than line #2";
            }
            if ((cMas[2] && cMas[3]) == true) {
                if ((line3 > line4) == true) cout << "Line #3 greater than line #4";
                else cout << "Line #4 greater than line #3";
            }

            break;

        case les:
            if ((cMas[0] && cMas[1]) == true) {
                if ((line1 < line2) == true) cout << "Line #1 less line #2";
                else cout << "Line #2 less line #1";
            }
            if ((cMas[0] && cMas[2]) == true) {
                if ((line1 < line3) == true) cout << "Line #1 less line #3";
                else cout << "Line #3 less line #1";
            }
            if ((cMas[0] && cMas[3]) == true) {
                if ((line1 < line4) == true) cout << "Line #1 less line #4";
                else cout << "Line #4 less line #1";
            }
            if ((cMas[1] && cMas[2]) == true) {
                if ((line2 < line3) == true) cout << "Line #2 less line #3";
                else cout << "Line #3 less line #2";
            }
            if ((cMas[1] && cMas[3]) == true) {
                if ((line2 < line4) == true) cout << "Line #2 less line #4";
                else cout << "Line #4 less line #2";
            }
            if ((cMas[2] && cMas[3]) == true) {
                if ((line3 < line4) == true) cout << "Line #3 less line #4";
                else cout << "Line #4 less line #3";
            }

            break;

        default:
            cout << "\nClosing the program.\n";
            exit(USER_CL_PROGRAM);
    }

    cout << "\n\tText of strings after conversion:";
    cout << "\nline #1: " << line1;
    cout << "\nline #2: " << line2;
    cout << "\nline #3: " << line3;
    cout << "\nline #4: " << line4;
    cout << "\nline #5: " << line5;

    if (answer == 6) {
        cout << "\nline #6: " << line6;
        cout << "\nline #7: " << line7;
        cout << "\nline #8: " << line8;
    }
    cout << endl;

}

