#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

using namespace glm;

class Camera {
	public:
		static Camera *inst();

		mat4 projection();
		mat4 view();

		void setRes(GLuint w, GLuint h);
		void init(vec3, vec3, vec3);

		void mouseMotion(SDL_Event &ev);
		void strideRight(SDL_Event &ev);
		vec2 mouse();
		vec2 stride();

	private:
		static Camera *instance;
		Camera();
		Camera(Camera &);
		Camera & operator=(Camera const&);
		~Camera() {}

		GLuint width;
		GLuint height;

		vec3 position;
		vec3 direction;
		vec3 up;

		GLint xMouseOffset;
		GLint yMouseOffset;

		GLint strideOffset;

};

#endif

