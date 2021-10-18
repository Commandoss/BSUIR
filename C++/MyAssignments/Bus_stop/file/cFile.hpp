//
//  cFile.hpp
//  Bus_Stop
//
//  Created by Belousov Ilya on 19.06.21.
//

#ifndef cFile_hpp
#define cFile_hpp

#include <vector>
#include <fstream>
#include "cBusCompany.hpp"
#include "Bus.hpp"


class cFile {
public:
    cFile();
    vector<bus> readFileToBC(string path, string nameComp);
    bool writeBCToFile(string path, string nameComp, vector<bus> busList);
};



#endif /* cFile_hpp */
