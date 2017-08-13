
#ifndef __STAGE_VIEW_H__
#define __STAGE_VIEW_H__

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/Sprite.hpp>

class StageView : public mvcgame::View
{
public:
	typedef mvcgame::NodeView Window;
	typedef std::shared_ptr<mvcgame::Sprite> SpriteView;
public:
	StageView();
	~StageView();
public:
	void initView();
public:
	void removeAllBgBoxChild();
	void removeAllFgBoxChild();
private:
	SpriteView getBgByIndex(unsigned int index);
	SpriteView getFgByIndex(unsigned int index);
private:
	std::shared_ptr<Window> _bgBox;
	std::shared_ptr<Window> _fgBox;
};

#endif