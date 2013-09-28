#include "Camera.hpp"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

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

	xMouseOffset = 0;
	yMouseOffset = 0;
}


Camera::Camera() :
	position(vec3(0, 0, 1)) {

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
}

mat4 Camera::projection() {
	float ratio = (float)width / (float)height;
	return perspective(45.0f, ratio, 0.1f, 100.0f);
}

mat4 Camera::view() {
	return lookAt(
			position,
			direction,
			up
	);
}

/**
 * Mouse motion event
 */
void Camera::mouseMotion(SDL_Event &event) {
	Sint32 xRel = event.motion.xrel;
	Sint32 yRel = event.motion.yrel;
	
	xMouseOffset += xRel;
	yMouseOffset += yRel;
}

vec2 Camera::mouse() {
	return vec2(xMouseOffset, yMouseOffset);
}

void Camera::stride(SDL_Event &event) {
	if (event.key.keysym.scancode == SDL_SCANCODE_D) {
		cout << "right" << endl;
		strideOffset += 0.1;
	}
	else {
		cout << "left" << endl;
		strideOffset -= 0.1;
	}
}
