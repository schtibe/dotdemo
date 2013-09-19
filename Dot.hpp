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
		const GLuint number;
		const GLuint dotAmount;
		const vec3 direction;
		vec3 position;

		GLuint shader;
		GLuint s_time;
		GLuint s_number;
		GLuint s_amount;

		GLuint arms = 3;
		GLfloat start = 1;
		GLfloat end = 6;
		GLfloat pos;

		// the direction to move
		// 1 = outwards
		// 0 = inwards
		GLfloat v = 0.0;
		GLfloat acc = 0.0000005;

		GLuint lastUpdate;
		GLuint zeroTime = 0;
};


#endif /* end of include guard: DOT_HPP__ */
