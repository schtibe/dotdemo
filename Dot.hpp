#ifndef DOT_HPP__

#define DOT_HPP__

#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <glm/glm.hpp>

#include "engine/DrawObject.hpp"

using namespace glm;

class Dot : public DrawObject {
	public:
		Dot(GLuint number, GLuint dotAmount, vec3 direction);
		void draw(GLuint time);
		void doPhysics(GLuint time);

	private:
		GLuint number;
		GLuint dotAmount;
		vec3 direction;
		vec3 position;

		GLuint shader;
};


#endif /* end of include guard: DOT_HPP__ */
