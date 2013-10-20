#include "Camera.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "glmUtils.hpp"

using namespace std;

Camera *Camera::instance = NULL;

Camera *Camera::inst() {
	if (!instance) {
		instance = new Camera;
	}

	return instance;
}

void Camera::setRes(GLuint w, GLuint h) {
	width = w;
	height = h;

	glViewport(0, 0, width, height);
}

void Camera::init(vec3 pos, vec3 dir, vec3 up) {
	position = pos;
	direction = dir;
	this->up = up;
}


Camera::Camera() :
	position(vec3(0, 0, 1)) {

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
}

mat4 Camera::projection() {
	float ratio = (float)height / (float)width;
	return perspective(45.0f, 1/ratio, 0.1f, 100.0f);
}

mat4 Camera::view() {
	return lookAt(
			position,
			direction,
			up
	);
}


