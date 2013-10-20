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
		void stride(SDL_Event &ev);

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


};

#endif

