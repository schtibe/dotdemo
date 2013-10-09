
#include <boost/bind.hpp>

#include "engine/Engine.hpp"
#include "Demo.hpp"

#include<X11/X.h>
#include<X11/Xlib.h>



int main(int argc, char**argv) {

	Engine engine("dotdemo", 1024, 1024, NONE);

	Demo *demo =  new Demo();

	
	engine.registerRenderFunc(
			boost::bind(&Demo::renderFunc, demo, _1, _2)
	);


	//engine.toggleDebugCamera();
	engine.run();


}
