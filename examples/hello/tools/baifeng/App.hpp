//
//  App.hpp
//  lite2d
//
//  Created by baifeng on 2017/6/26.
//  Copyright © 2017年 baifeng. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include <stdio.h>
#include <string>
#include "../puremvc/pmvcpp.h"
#include "Event.hpp"

namespace BF {
    class App {
    public:
        static void Fire();
    public:
        static void registerProxy ( PureMVC::IProxy* proxy );
        static PureMVC::IProxy& removeProxy ( std::string proxyName );
        static PureMVC::IProxy& getProxy ( std::string proxyName );
    public:
        static void registerMediator( PureMVC::IMediator* mediator );
        static PureMVC::IMediator& removeMediator( std::string mediatorName );
        static PureMVC::IMediator& getMediator( std::string mediatorName );
    public:
        static Event& event();
    };
}

#endif /* App_hpp */
