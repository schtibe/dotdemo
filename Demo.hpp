#ifndef DEMO_HPP__

#define DEMO_HPP__

#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "engine/Engine.hpp"


class Demo {
	public:
		Demo();
		void renderFunc(GLuint time, Engine engine);
	
	private:
		GLuint dotAmount;
		GLuint arms;
		GLuint shader;


		GLuint s_time;
		GLuint s_amount;
		GLuint s_arms;
		GLuint s_projection;
		GLuint s_view;
		GLuint s_mouse;
};


#endif /* end of include guard: DEMO_HPP__ */
