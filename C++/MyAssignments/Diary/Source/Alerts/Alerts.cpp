//
//  Alerts.cpp
//  Diary
//
//  Created by Belousov Ilya on 13.12.20.
//

#include "Alerts.hpp"

cAlerts::cAlerts() {
    Current_Data.getSisTime();
}

cAlerts::~cAlerts() {
}

bool cAlerts::checkEvents(cImportWork &value) {
    if ((Current_Data.getDay() >= value.getData(1)) &&
        (Current_Data.getMonth() >= value.getData(2)) &&
        (Current_Data.getYear() >= value.getData(3)))
    {
        cout << "\nThe event has come" << endl;
        value.printEvent();
        return true;
    }
    return false;
}

bool cAlerts::checkEvents(cImportEveryday &value) {
    if ((Current_Data.getDay() >= value.getData(1)) &&
        (Current_Data.getMonth() >= value.getData(2)) &&
        (Current_Data.getYear() >= value.getData(3)))
    {
        if (value.emptyTime()) {
            cout << "\nThe event has come" << endl;
            value.printEvent();
            return true;
        }
        else if ((Current_Data.getHour() >= value.getTime(4)) &&
                 (Current_Data.getMinutes() >= value.getTime(5)))
        {
            cout << "\nThe event has come" << endl;
            value.printEvent();
            return true;
        }
    }
    return false;
}
