

#include "hello/app/controller/MainController.hpp"
#include "hello/app/base/Application.hpp"
#include "ServiceLocator.hpp"
#include <mvcgame/asset/FileStreamLoader.hpp>

Application::Application(std::unique_ptr<mvcgame::IApplicationBridge> bridge) :
mvcgame::Application(std::move(bridge)) {
}

void Application::run()
{
	std::unique_ptr<mvcgame::FileStreamLoader> fs(new mvcgame::FileStreamLoader(getBridge().getFilesystem()));
	fs->addPath("../../../examples/hello/resources");
	fs->addPath("resources");
	fs->addPath("app0:resources");
	ServiceLocator::get().getAssetStreams().addLoader(std::move(fs));

	getRoot().getView().setSize(mvcgame::Size(960, 544));
	getRoot().addChild(std::unique_ptr<mvcgame::ViewController>(new MainController()));
	mvcgame::Application::run();
}