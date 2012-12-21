//
//  ViewController.cpp
//  hydra
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgraphics/ViewController.hpp>
#include <mvcgraphics/IView.hpp>

#include <algorithm>

namespace mvcgraphics {

    ViewController::ViewController() : _view(NULL)
    {

    }

    ViewController::~ViewController()
    {
    	clearChildren();
        clearActions();
        if(_view)
        {
            delete _view;
        }
    }

    void ViewController::clearChildren()
    {
        ChildrenList::const_iterator itr;
        for(itr=_children.begin(); itr!=_children.end(); ++itr)
        {
            delete *itr;
        }
        _children.clear();
    }

    void ViewController::clearActions()
    {
        _actions.clear();
    }

    void ViewController::setView(IView* view)
    {
        if(_view)
        {
            delete _view;
        }
        _view = view;
    }
        
    const IView& ViewController::getView() const
    {
    	return *_view;
    }
    
    IView& ViewController::getView()
    {
    	return *_view;
    }
 
    void ViewController::addChild(ViewController* child)
    {
    	_children.push_back(child);
    }

    const ViewController::ChildrenList& ViewController::getChildren() const
    {
        return _children;
    }

    ViewController::ChildrenList& ViewController::getChildren()
    {
        return _children;
    }
    
    void ViewController::runAction(IAction* action)
    {
        _actions.add(action);
    }
    
    void ViewController::runAction(IAction* action, const Duration& duration)
    {
        _actions.add(action, duration);
    }

    void ViewController::updateActions(UpdateEvent& event)
    {
        _actions.update(getView(), event);
    }

}