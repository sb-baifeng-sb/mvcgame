
#include "hello/app/controller/MainController.hpp"
#include "hello/app/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/font/FontSheet.hpp>
#include <mvcgame/view/SpineSkeletonView.hpp>
#include <mvcgame/action/TweenAction.hpp>
#include <mvcgame/view/TileMapView.hpp>
#include <mvcgame/view/PanZoomView.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
	auto bg = std::make_shared<ColorView>();
	bg->setBackgroundColor(Color(50, 255, 50));
	bg->getFrame().size = getRoot().getView().getSize();
	bg->getFrame().origin = bg->getFrame().size / 2;

	/*auto tileMap = ServiceLocator::get().getTileMaps().load("desert");
	//std::cout << *tileMap << std::endl;
	auto tileMapView = std::make_shared<TileMapView>(tileMap);
	tileMapView->getFrame().origin = tileMapView->getFrame().size / 2;
	tileMapView->setScale(0.5f);

	setView(tileMapView);
	return;*/
	
	auto guybrushAtlas = ServiceLocator::get().getTextureAtlases().load("guybrush");
	_guybrush = std::make_shared<Sprite>(*guybrushAtlas);
	_guybrush->getFrame().origin = bg->getFrame().size / 2;
	_guybrush->getFrame().origin.x -= 150;
	_guybrush->setScale(0.5);
	_guybrush->setSpriteFrameDuration(20);
	bg->addChild(_guybrush);

	/*auto colorMask = std::make_shared<ColorView>();
	colorMask->setBackgroundColor(Color(0, 0, 0, 30));
	colorMask->getFrame().size = _guybrush->getFrame().size;
	colorMask->getFrame().origin = _guybrush->getFrame().size / 2;
	_guybrush->addChild(colorMask);*/

	auto miguelAtlas = ServiceLocator::get().getTextureAtlases().load("miguel");
	auto miguel = std::make_shared<Sprite>(*miguelAtlas);
	miguel->getFrame().origin = bg->getFrame().size / 2;
	miguel->getFrame().origin.x += 150;
	miguel->setSpriteFrameDuration(20);
	bg->addChild(miguel);

	auto fontAtlas = ServiceLocator::get().getFontAtlases().load("font");
	FontSheet fontSheet(*fontAtlas);
	auto title = std::make_shared<TextView>();
	title->setSheet(fontSheet);
	title->getFrame().size = Size(50, 50);
	title->getFrame().origin = bg->getFrame().size / 2;
	title->setText("I'm your father!");
	bg->addChild(title);

	auto dragonSkel = ServiceLocator::get().getSkeletons().load("dragon");
	auto dragon = std::make_shared<SpineSkeletonView>(dragonSkel);
	dragon->getFrame().origin = bg->getFrame().size / 2;
	dragon->getFrame().origin.x -= 200;
	dragon->getFrame().origin.y /= 2;
	dragon->getFrame().origin.y += 250;
	dragon->setScale(0.5);

	dragon->setAnimation("flying", true);
	dragon->addAnimation("flying", true, 1);

	auto spineboySkel = ServiceLocator::get().getSkeletons().load("spineboy");
	auto spineboy = std::make_shared<SpineSkeletonView>(spineboySkel);
	spineboy->getFrame().origin = bg->getFrame().size / 2;
	spineboy->getFrame().origin.x += 200;
	spineboy->getFrame().origin.y /= 2;
	spineboy->setScale(0.5);

	spineboySkel->setMix("walk", "jump", 0.2f);
	spineboySkel->setMix("jump", "walk", 0.4f);
	spineboy->setAnimation("walk", true);
	spineboy->addAnimation("jump", false, 0);
	spineboy->addAnimation("walk", true, 0);
	spineboy->addAnimation("jump", false, 3);
	spineboy->addAnimation("walk", true, 0);
	spineboy->addAnimation(true, 0);
	spineboy->addAnimation("walk", true, 1);

	auto powerupSke = ServiceLocator::get().getSkeletons().load("powerup");
	auto powerup = std::make_shared<SpineSkeletonView>(powerupSke);
	powerup->getFrame().origin = bg->getFrame().size / 2;
	powerup->getFrame().origin.y -= 300;
	powerup->setScale(0.5f);

	//powerup->setAnimation("animation", true);
	powerup->addAnimation("animation", true, 1);

	bg->addChild(spineboy);
	bg->addChild(dragon);
	bg->addChild(powerup);

	setView(bg);
}

void MainController::respondOnTouchStart(const TouchEvent& event)
{
	_guybrushTouched = true;
	_guybrushTouchPoint = event.getPoints()[0];
	if (_guybrush == NULL)
	{
		return;
	}
	std::cout << "GUYBRUSH" << std::endl;
	_guybrushTouched = event.touched(*_guybrush);
	if (_guybrushTouched)
	{
		std::cout << "GUYBRUSH TOUCHED!!!" << std::endl;
		_guybrushTouchPoint = event.getPoints()[0];
	}
}

void MainController::respondOnTouchUpdate(const TouchEvent& event)
{
	if (_guybrushTouched)
	{
		std::cout << "GUYBRUSH MOVED!!!" << std::endl;
		auto point = event.getPoints()[0];
		auto vec = point - _guybrushTouchPoint;
		_guybrushTouchPoint = point;
		//_guybrush->getFrame().origin += vec;
		getView().getFrame().origin += vec;
		std::cout << point;
	}
}

void MainController::respondOnTouchEnd(const TouchEvent& event)
{
	_guybrushTouched = false;
}