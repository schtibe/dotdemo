
#include <boost/bind.hpp>

#include "engine/Engine.hpp"
#include "Demo.hpp"


int main(int argc, char**argv) {
	setenv("SDL_VIDEO_X11_NODIRECTCOLOR", "1", 1);

	Engine engine("dotdemo", 1024, 1024, SHOW_FPS | PRINT_VERSION);

	Demo *demo =  new Demo();

	
	engine.registerRenderFunc(
			boost::bind(&Demo::renderFunc, demo, _1, _2)
	);


	//engine.toggleDebugCamera();
	engine.run();
}
