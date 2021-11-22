//
//  StationMonitor.hpp
//  main
//
//  Created by Belousov Ilya on 16.11.21.
//

#ifndef StationMonitor_hpp
#define StationMonitor_hpp

#include <list>
#include <sstream>

#include "ThreadControl.hpp"
#include "Pseudoterminal.hpp"
#include "Error.hpp"

class StationMonitor : public Pseudoterminal {
public:
    StationMonitor();
   ~StationMonitor();

    bool start(const std::string &adress);
    void stop();

private:
    void create_marker();

    void checkRing();
};

#endif /* StationMonitor_hpp */
