
#include <boost/bind.hpp>

#include "engine/Engine.hpp"
#include "Demo.hpp"


int main(int argc, char**argv) {

	Engine engine("dotdemo", 1024, 1024, NONE);

	Demo *demo =  new Demo();

	
	engine.registerRenderFunc(
			boost::bind(&Demo::renderFunc, demo, _1, _2)
	);


	//engine.toggleDebugCamera();
	engine.run();

}
