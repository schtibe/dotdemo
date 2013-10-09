
#include <boost/bind.hpp>

#include "engine/Engine.hpp"
#include "Demo.hpp"

#include <screenhack.h>

Engine *engine;


static char **dotdemo_defaults;

static XrmOptionDescRec dotdemo_options[0];

static void dotdemo_reshape(Display *, Window, void *closure,
		unsigned int width, unsigned int heigth) {

}

static Bool dotdemo_event(Display *, Window, void *closure,
		XEvent *event) {

}

void dotdemo_free(Display *, Window, void *closure)  {

}


static void *dotdemo_init (Display *disp, Window win) {

	cout << "INIT" << endl;
	engine = new Engine("dotdemo", 1024, 1024, SHOW_FPS | PRINT_VERSION);

	Demo *demo =  new Demo();

	
	engine->registerRenderFunc(
			boost::bind(&Demo::renderFunc, demo, _1, _2)
	);


	//engine.toggleDebugCamera();
	//engine.run();
}

static unsigned long dotdemo_draw(Display*, Window, void *closure) {
	cout << "Draw" << endl;
	engine->render();
	return 1;
}

int main() {
	cout << "Main?" << endl;
}

XSCREENSAVER_MODULE("DotDemo", dotdemo)

