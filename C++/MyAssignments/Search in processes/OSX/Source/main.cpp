//
//  main.cpp
//  Search in processes
//
//  Created by Belousov Ilya on 18.10.21.
//

#include <iostream>
#include "Fsystem.hpp"
#include "PIDS.hpp"

using namespace::std;

void checking_parameters(const int &argc, const char *argv[]) {
    if (argc <= 1)
        throw "Command line parameters were not specified.";
    else if (Fsystem::file_type(argv[1]) != Regular_File)
        throw "The specified file does not exist or is not a file.";
}

std::string get_subsequence(const char *path) {
    Fsystem f;
    f.open_file(path, ios_base::in | ios_base::binary);

    return f.read_file_all();
}

void find_in_process(const string &subsequence) {
    Fsystem f;
    PIDS P;

    std::list<pid_t> pids = P.get_list_pids();
    for (auto pid : pids) {
        f.open_file(P.get_pid_path(pid), ios_base::in | ios_base::binary);

        if (f.find_in_file(subsequence)) {
            cout << "Sequence found in process: " << P.get_pid_name(pid) << endl;
            cout << "Path to Mach-o file: " << P.get_pid_path(pid) << endl;
            return;
        }
        f.close();
    }
    cout << "Sequence not found" << endl;
}

void write_subsequence(const pid_t &pid, const string &path) {
    Fsystem f;
    f.open_file(path, ios_base::out | ios_base::trunc | ios_base::binary);

    PIDS P;
    Fsystem R;
    R.open_file(P.get_pid_path(pid), ios_base::in | ios_base::binary);
    std::string subsequence = R.read_file_line();

    f.write_file(subsequence);
}

int main(int argc, const char * argv[]) {
    try {
        checking_parameters(argc, argv);
//        write_subsequence(36029, argv[1]);
        std::string subsequence = get_subsequence(argv[1]);
        find_in_process(subsequence);

    } catch (const std::string &msg) {
        cout << "\t--- Error ---\n";
        cout << "Error info: " << msg << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

// When using a sequence taken from a file
// The result of the program will be:
// Sequence found in process: GitHub Desktop Helper (Renderer
// Path to Mach-o file: /Applications/GitHub Desktop.app/Contents/Frameworks/GitHub Desktop Helper (Renderer).app/Contents/MacOS/GitHub Desktop Helper (Renderer)
// Program ended with exit code: 0
