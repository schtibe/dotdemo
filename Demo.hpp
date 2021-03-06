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
		GLuint polyShader;
		GLuint polyBuffer;

		bool mode;

		GLuint s_time;
		GLuint s_amount;
		GLuint s_arms;
		GLuint s_projection;
		GLuint s_view;
		GLuint sp_projection;
		GLuint sp_view;

		GLuint lastUpdate;
};


#endif /* end of include guard: DEMO_HPP__ */
