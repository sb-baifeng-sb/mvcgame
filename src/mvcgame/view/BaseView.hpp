//
//  BaseView.hpp
//  mvcgame
//
//  Created by Miguel Ibero on 29/11/12.
//
//

#ifndef mvcgame_BaseView_hpp
#define mvcgame_BaseView_hpp

#include <mvcgame/view/IView.hpp>
#include <mvcgame/Geometry.hpp>

namespace mvcgame {

    /**
     * This is a basic view class that doesn't draw anything
     * Can be used by the different platforms to inherit from.
     */
    class BaseView : public IView
    {
    protected:
        IView* _parent;
        IView::Children _children;
        Rect _frame;
        Scale _scale;        
        Anchor _anchor;
        Anchor _parentAnchor;        
        Rotation _rotation;

        IView::Children::iterator findChild(const IView& child);
    public:
        BaseView();
        BaseView(const IView& view);
        BaseView(const Rect& f, const Scale& s, const Anchor& a, const Rotation& r);
        virtual ~BaseView();

        virtual void draw();

        virtual Rect& getFrame();
        virtual const Rect& getFrame() const;
        virtual void setFrame(const Rect& rect);

        virtual Rotation& getRotation();
        virtual const Rotation& getRotation() const;
        virtual void setRotation(const Rotation& r);

        virtual Scale& getScale();        
        virtual const Scale& getScale() const;
        virtual void setScale(const Scale& s);

        virtual Anchor& getAnchor();
        virtual const Anchor& getAnchor() const;
        virtual void setAnchor(const Anchor& a);      
        
        virtual Anchor& getParentAnchor();
        virtual const Anchor& getParentAnchor() const;
        virtual void setParentAnchor(const Anchor& a);

        virtual void addChild(IViewPtr child, unsigned layer=0);
        virtual IViewPtr removeChild(const IView& child);

        virtual IView& getParent();
        virtual const IView& getParent() const;
        virtual void removeFromParent();
        virtual void setParent(IView& parent);

        virtual bool respondToTouchPoint(const Point& p, const TouchEvent& event);
        
    };
}

#endif