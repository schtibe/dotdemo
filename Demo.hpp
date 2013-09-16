#ifndef DEMO_HPP__

#define DEMO_HPP__

#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <boost/container/vector.hpp>

#include "engine/Engine.hpp"
#include "Dot.hpp"


class Demo {
	public:
		Demo();
		void renderFunc(GLuint time, Engine engine);
	
	private:
		boost::container::vector<Dot> dots;
		GLuint dotAmount;
};


#endif /* end of include guard: DEMO_HPP__ */
