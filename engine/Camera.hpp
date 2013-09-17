#ifndef _CAMERA_H
#define _CAMERA_H

// This was created to allow you to use this camera code in your projects
// without having to cut and paste code.  This file and camera.cpp should be
// added to your project.
#include <cmath>
#include <SDL/SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

using namespace glm;

// This is our camera class
class Camera {
	public:
		Camera();
		Camera(GLint screenWidth, GLint screenHeight);

		vec3 getPosition();
		vec3 getView();
		vec3 getUpVector();
		vec3 getStrafe();

		void positionCamera(
				GLfloat positionX,
				GLfloat positionY,
				GLfloat positionZ,
				GLfloat viewX,
				GLfloat viewY,
				GLfloat viewZ,
				GLfloat upVectorX,
				GLfloat upVectorY,
				GLfloat upVectorZ
		);

		void positionCamera(
				vec3 position,
				vec3 view,
				vec3 upVector
		);

		void rotateView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
		void setViewByMouse(GLint mouseX, GLint mouseY);

		void strafeCamera(GLfloat speed);
		void moveCamera(GLfloat speed);
		void update(GLint mouseX, GLint mouseY);
		void look();

		void windowResize(GLint screenWidth, GLint screenHeight);

	private:
		GLint screenWidth, screenHeight;

		/**
		 * The camera's position
		 */
		vec3 position;

		/**
		 * The camera's view
		 */
		vec3 view;

		/**
		 * The camera's up vector
		 */
		vec3 upVector;

		/**
		 * The camera's strafe vector
		 */
		vec3 strafe;
};


#endif

