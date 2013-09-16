#include "Demo.hpp"

#include <cmath>
#include <glm/glm.hpp>

using namespace glm;

Demo::Demo() {
	dotAmount = 24;
	vec3 unit(0.0, 1.0, 0.0);
	GLfloat step = 2 * M_PI / dotAmount;

	for (GLuint i = 0; i < dotAmount; i++) {
		GLfloat angle = i * step;
		mat3 rot(
				cos(angle), -sin(angle), 0,
				sin(angle),  cos(angle), 0,
				0, 0, 1
		);

		vec3 direction = rot * unit;

		dots.push_back(Dot(i, dotAmount, direction));
	}
}

void Demo::renderFunc(GLuint time, Engine engine) {
	for (GLuint i = 0; i < dots.size(); i++) {
		engine.drawObject(dots.at(i));
	}
}
