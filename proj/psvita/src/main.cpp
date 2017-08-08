
#include <base/Application.hpp>
#include <mvcgame/platform/vita/ApplicationBridge.hpp>

int main(int argc, char *argv[]) {
	std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge(argc, argv));
	mvcgame::Application app(std::move(bridge));
	app.run();
	return 0;
}
