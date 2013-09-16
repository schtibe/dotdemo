#include "Dot.hpp"
#include "engine/Shader.hpp"

Dot::Dot(GLuint number, GLuint dotAmount, vec3 direction) :
	number(number),
	dotAmount(dotAmount),
	direction(direction) {

	position = direction;

	shader = Shader::loadShaders("dot.vert", "dot.frag");
}

void Dot::draw(GLuint time) {
	glUseProgram(shader);

	glBegin(GL_POINTS);
		glVertex3f(position.x, position.y, position.z);
	glEnd();
}

void Dot::doPhysics(GLuint time) {

}
