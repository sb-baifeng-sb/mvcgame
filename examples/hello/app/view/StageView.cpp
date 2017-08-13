#include "StageView.hpp"

#define BG_SPRITE_MAX 2
#define FG_SPRITE_MAX 6

StageView::StageView() {
}

StageView::~StageView() {
}

void StageView::initView() {
	if (_bgBox != nullptr || _fgBox != nullptr) {
		return;
	}
	_bgBox = std::make_shared<Window>();
	_fgBox = std::make_shared<Window>();

	for (int i = 0; i < BG_SPRITE_MAX; i++) {
		_bgBox->addChild(SpriteView());
	}

	for (int i = 0; i < FG_SPRITE_MAX; i++) {
		_fgBox->addChild(SpriteView());
	}

	addChild(_bgBox);
	addChild(_fgBox);
}

void StageView::removeAllBgBoxChild() {
	_bgBox->removeChildren();
}

void StageView::removeAllFgBoxChild() {
	_fgBox->removeChildren();
}

StageView::SpriteView StageView::getBgByIndex(unsigned int index) {
	Children& children = _bgBox->getChildren();
	if (index < children.size()) {
		return std::dynamic_pointer_cast<mvcgame::Sprite>(children[index].first);
	}
	return std::make_shared<mvcgame::Sprite>();
}

StageView::SpriteView StageView::getFgByIndex(unsigned int index) {
	Children& children = _fgBox->getChildren();
	if (index < children.size()) {
		return std::dynamic_pointer_cast<mvcgame::Sprite>(children[index].first);
	}
	return std::make_shared<mvcgame::Sprite>();
}
