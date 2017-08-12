//
//  Event.hpp
//  lite2d
//
//  Created by baifeng on 2017/6/26.
//  Copyright © 2017年 baifeng. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <cstdlib>

namespace PureMVC {
    class IObserverRestricted;
}

namespace BF {
    class Event {
    public:
        void sendNotification   ( int notificationName, void* body, int notificationType);
        void sendNotification   ( int notificationName, int notificationType );
        void sendNotification   ( int notificationName, void* body );
        void sendNotification   ( int notificationName );
    public:
        void registerObserver ( int notificationName, PureMVC::IObserverRestricted* observer );
        void removeObserver( int notificationName, intptr_t contextAddress );
    };
}

#endif /* Event_hpp */
