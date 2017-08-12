
#include "hello/app/base/Application.hpp"
#include <mvcgame/platform/win/ApplicationBridge.hpp>

int main(int argc, char** argv) {
	std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge(argc, argv));
	Application app(std::move(bridge));
	app.run();
	return 0;
}