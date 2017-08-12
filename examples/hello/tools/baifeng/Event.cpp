//
//  Event.cpp
//  lite2d
//
//  Created by baifeng on 2017/6/26.
//  Copyright © 2017年 baifeng. All rights reserved.
//

#include "Event.hpp"
#include "../puremvc/pmvcpp.h"

using namespace PureMVC;

namespace BF {
    
    static std::string const AppName = "BFApp";
    
    void Event::sendNotification   ( int notificationName, void* body, int notificationType) {
        Facade::getInstance(AppName)->sendNotification(notificationName, body, notificationType);
    }
    
    void Event::sendNotification   ( int notificationName, int notificationType ) {
        Facade::getInstance(AppName)->sendNotification(notificationName, notificationType);
    }
    
    void Event::sendNotification   ( int notificationName, void* body ) {
        Facade::getInstance(AppName)->sendNotification(notificationName, body);
    }
    
    void Event::sendNotification   ( int notificationName ) {
        Facade::getInstance(AppName)->sendNotification(notificationName);
    }
    
    void Event::registerObserver ( int notificationName, IObserverRestricted* observer ) {
        View::getInstance(AppName)->registerObserver(notificationName, observer);
    }
    
    void removeObserver( int notificationName, intptr_t contextAddress ) {
        View::getInstance(AppName)->removeObserver(notificationName, contextAddress);
    }
}
