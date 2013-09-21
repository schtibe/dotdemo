#include "Dot.hpp"
#include "engine/Shader.hpp"

#include <iostream>

using namespace std;

std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec) {

	out << "{"
		<< vec.x << ", " << vec.y << ", " << vec.z
		<< "}";
	
	return out;
}

Dot::Dot(GLuint number, GLuint dotAmount, vec3 direction) :
	number(number),
	dotAmount(dotAmount),
	direction(direction) {

	shader = Shader::loadShaders("dot.vert", "dot.frag");
	s_time = glGetUniformLocation(shader, "time");
	s_amount = glGetUniformLocation(shader, "amount");
}

void Dot::draw(GLuint time) {
	glUseProgram(shader);

	glUniform1i(s_time, time);
	glUniform1i(s_number, number);
	glUniform1i(s_amount, dotAmount);

	glBegin(GL_POINTS);
		glVertex3f(position.x, position.y, position.z);
	glEnd();
}

void Dot::doPhysics(GLuint time) {
}
