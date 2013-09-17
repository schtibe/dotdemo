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
	s_move = glGetUniformLocation(shader, "move");
	s_time = glGetUniformLocation(shader, "time");
	s_number = glGetUniformLocation(shader, "number");
	s_amount = glGetUniformLocation(shader, "amount");

	GLuint A;
	GLuint B = (dotAmount / 3) * 0.5;

	if (number % (B * 2) == B) {
		A = B;
		move = 0;
	}
	else if (number % (B * 2) > B) {
		A = B - (number % B);
		move = 0;
	}
	else {
		A = number % (B * 2);
		move = 1;
	}

	position = (direction * start) + (direction * ((end / B) * A));
	pos = (end / B ) * A;
}

void Dot::draw(GLuint time) {
	glUseProgram(shader);

	glUniform1i(s_move, move);
	glUniform1i(s_time, time);
	glUniform1i(s_number, number);
	glUniform1i(s_amount, dotAmount);

	glBegin(GL_POINTS);
		glVertex3f(position.x, position.y, position.z);
	glEnd();
}

void Dot::doPhysics(GLuint time) {

	if (time - lastUpdate > 0.00001) {
		vec3 startPoint = (direction * start);
		GLuint B = (dotAmount / 3) * 0.5;
		float v = 0.05;

		if (move) {
			pos = pos + v;
		}
		else {
			pos = pos - v;
		}

		// Swap direction
		if (pos >= end) {
			pos  = end;
			move = 0;
		}
		if (pos <= 0) {
			pos  = 0;
			move = 1;
		}

		position = startPoint + (direction * ((end / B) * pos));
	}

	lastUpdate = time;
}
