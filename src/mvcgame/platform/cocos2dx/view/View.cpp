//
//  View.cpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#include <mvcgame/platform/cocos2dx/view/View.hpp>
#include <mvcgame/Geometry.hpp>
#include <cocos2dx/base_nodes/CCNode.h>

namespace mvcgame {

	View::View(cocos2d::CCNode* node) : _node(node)
	{
		setNode(node);
	}

    View::View()
    {
    	_node = new cocos2d::CCNode();
    	setNode(_node);
    }

    View::~View()
    {
    	CC_SAFE_RELEASE(_node);
    }

    void  View::setNode(cocos2d::CCNode* node)
    {
    	_node = node;
    	const cocos2d::CCSize& size = node->getContentSize();
        BaseView::setFrame(Rect(node->getPositionX(), node->getPositionY(), size.width, size.height));
        BaseView::setScale(Scale(node->getScaleX(), node->getScaleY()));
        BaseView::setRotation(Rotation(node->getRotation(), 0));
        const cocos2d::CCPoint& a = node->getAnchorPoint();
        BaseView::setAnchor(Anchor(a.x, a.y));
    }

    void View::setFrame(const Rect& rect)
    {
    	BaseView::setFrame(rect);
    	_node->setPosition(cocos2d::CCPointMake(rect.origin.x, rect.origin.y));
    	_node->setContentSize(cocos2d::CCSizeMake(rect.size.width, rect.size.height));
    }

    void View::setRotation(const Rotation& r)
    {
    	BaseView::setRotation(r);
    	_node->setRotation(r.x);    	
    }

    void View::setScale(const Scale& s)
    {
    	BaseView::setScale(s);
    	_node->setScaleX(s.x);
    	_node->setScaleY(s.y);
    }

    void View::setAnchor(const Anchor& a)
    {
        BaseView::setAnchor(a);
        _node->setAnchorPoint(cocos2d::CCPointMake(a.x, a.y));
    }

    void View::addChild(IViewPtr child, unsigned layer)
    {
        // Can only add cocos2dx implemented views
        assert(false);
    }

    void View::removeChild(const IView& child)
    {
        // Can only add cocos2dx implemented views
        assert(false);
    }

    void View::setParent(IView& parent)
    {
        // Can only add cocos2dx implemented views
        assert(false);
    }    
    
    void View::addChild(ViewPtr child, unsigned layer)
    {
    	_node->addChild(child->_node, layer);
        BaseView::addChild(IViewPtr(child.release()), layer);
    }

    void View::removeChild(const View& child)
    {
    	BaseView::removeChild(child);
        _node->removeChild(child._node, true);
    }

    void View::setParent(View& parent)
    {
        BaseView::setParent(parent);
        _node->setParent(parent._node);
    }

}