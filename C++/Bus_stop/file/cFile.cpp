//
//  cFile.cpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#include "cFile.hpp"

cFile::cFile() {
}

vector<bus> cFile::readFileToBC(string path, string nameComp) {
    vector<bus> busList;
    string line, buffer;
    bus b;
    
    ifstream inf(path);
    if (inf.is_open()) {
        while (getline(inf, line)) {
            if (line.find(nameComp) != string::npos) {
                line.replace(0, line.find(' ') + 1, "");
                b.setDeparture(line.substr(0, line.find(' ')));
                line.replace(0, line.find(' ') + 1, "");
                b.setArrival(line.substr(0, line.find(' ')));
                busList.push_back(b);
            }
        }
    } else {
        cout << "Unable to open file!" << endl;
    }
    
    return busList;
}

bool cFile::writeBCToFile(string path, string nameComp, vector<bus> busList) {
    ofstream of;
    of.open(path, std::ios::app);
    if (of.is_open()) {
        for (auto bus : busList) {
            of << nameComp << " ";
            of << bus.getDeparture().getHour() << ":" << bus.getDeparture().getMin() << " ";
            of << bus.getArrival().getHour() << ":" << bus.getArrival().getMin() << "\n";
        }
        return true;
    }
    
    return false;
}
