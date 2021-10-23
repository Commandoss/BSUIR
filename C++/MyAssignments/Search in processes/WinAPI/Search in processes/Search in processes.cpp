// Search in processes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Fsystem.hpp"

#include <windows.h>
#include <tlhelp32.h>
#include <atlbase.h>
#include <iostream>

using namespace::std;

HANDLE getProcessList() {
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        cerr << "CreateToolhelp32 error" << endl;
        exit(EXIT_FAILURE);
    }
    return hSnapshot;
}

string getProcessPath(CONST DWORD &procID) {
    HANDLE proc = OpenProcess(PROCESS_QUERY_INFORMATION, TOKEN_READ, procID);
    if (proc == INVALID_HANDLE_VALUE) {
		cerr << " OpenProcess error " << endl;
        exit(EXIT_FAILURE);
    }

	CHAR path[MAX_PATH];
    DWORD dwSize = MAX_PATH;
    if (!QueryFullProcessImageNameA(proc, 0, path, &dwSize)) {
        return "";
    }


    return string(path);
}

void checking_parameters(const int &argc, const char *argv[]) {
	if (argc <= 1)
		cerr << "Command line parameters were not specified." << endl;
	else if (Fsystem::file_type(argv[1]) != Regular_File)
		cerr << "The specified file does not exist or is not a file." << endl;
}

std::string getSubsequence(const char *path) {
    Fsystem f;
    f.open_file(path, ios_base::in | ios_base::binary);

    return f.read_file_all();
}

void findInProcess(const string & subsequence) {
    Fsystem f;
    HANDLE hSnapshot = getProcessList();
    PROCESSENTRY32 peProcessEntry;
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    do {
        string path = getProcessPath(peProcessEntry.th32ProcessID);
        if (path.empty())
            continue;

        f.open_file(path, ios_base::in | ios_base::binary);
        if (f.find_in_file(subsequence)) {
            cout << "Found!" << endl;

			cout << "Name process: " << peProcessEntry.szExeFile << endl;
			cout << "Path process: " << path << endl;
			cout << "ID process: " << peProcessEntry.th32ProcessID << endl;
			break;
        }
        f.close();
    } while (Process32Next(hSnapshot, &peProcessEntry));

    CloseHandle(hSnapshot);
}

int main(int argc, const char *argv[]) {
    checking_parameters(argc, argv);
    string subsequence = getSubsequence(argv[1]);
    findInProcess(subsequence);

    return 0;
}