//
//  App.cpp
//  lite2d
//
//  Created by baifeng on 2017/6/26.
//  Copyright © 2017年 baifeng. All rights reserved.
//

#include "App.hpp"
#include "Event.hpp"

using namespace PureMVC;

namespace BF {
    
    static std::string const AppName = "BFApp";
    static Event* event = nullptr;
    
    void App::Fire() {
        Facade::getInstance(AppName);
    }
    
    IProxy& App::getProxy(std::string proxyName) {
        return *Facade::getInstance(AppName)->retrieveProxy(proxyName);
    }
    
    IProxy& App::removeProxy(std::string proxyName) {
        return *Facade::getInstance(AppName)->removeProxy(proxyName);
    }
    
    void App::registerProxy(IProxy *proxy) {
        Facade::getInstance(AppName)->registerProxy(proxy);
    }
    
    void App::registerMediator( PureMVC::IMediator* mediator ) {
        Facade::getInstance(AppName)->registerMediator(mediator);
    }
    
    IMediator& App::removeMediator( std::string mediatorName ) {
        return *Facade::getInstance(AppName)->removeMediator(mediatorName);
    }
    
    IMediator& App::getMediator( std::string mediatorName ) {
        return *Facade::getInstance(AppName)->retrieveMediator(mediatorName);
    }
    
    Event& App::Event() {
        if (event == nullptr) {
            event = new class Event();
        }
        return *event;
    }
}
