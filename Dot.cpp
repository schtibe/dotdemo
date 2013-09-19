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
	s_number = glGetUniformLocation(shader, "number");
	s_amount = glGetUniformLocation(shader, "amount");

	GLuint A;
	GLuint B = (dotAmount / 3) * 0.5;

	if (number % (B * 2) == B) {
		A = B;
	}
	else if (number % (B * 2) > B) {
		A = B - (number % B);
	}
	else {
		A = number % (B * 2);
	}

	position = (direction * start) + (direction * ((end / B) * A));
	pos = (end / B ) * A;
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
		vec3 startPoint = (direction * start);
		GLuint B = (dotAmount / 3) * 0.5;
		//float v = 0.05;
		
		GLfloat startPos = M_PI / (dotAmount / 6) * number;
		pos = glm::sin(startPos + time * 0.002) * end / 2;
	
		position = startPoint + (direction * ((end / B) * (end / 2 + pos)));

		lastUpdate = time;
}
