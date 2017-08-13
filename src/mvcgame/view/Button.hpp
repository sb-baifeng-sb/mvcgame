

#ifndef mvcgame_Button_hpp
#define mvcgame_Button_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/texture/Texture.hpp>

namespace mvcgame {

    class Button : public View
    {
	public:
		typedef std::function<void(Button*)> ClickedFunc;
		typedef std::shared_ptr<const Texture> Texture;
    public:
		Button();
		Button(Texture normal, Texture light, Texture disable);
	public:
		void setClickedFunc(ClickedFunc func);
		void setTexture(Texture normal, Texture light, Texture disable);
		void setEnable(bool b);
	public:
		bool isEnable() const;
		bool isPressed() const;
	private:
		void setPressed(bool b);
		void drawView();
	private:
		bool _enable;
		bool _pressed;
		Texture _normal;
		Texture _light;
		Texture _disable;
		ClickedFunc _click;
    };

}

#endif