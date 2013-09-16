#ifndef BALL_HPP

#define BALL_HPP

#include <glm/glm.hpp>

#include "Board.hpp"
#include "engine/DrawObject.hpp"
#include "boost/container/vector.hpp"

using boost::container::vector;
using namespace glm;

class Ball : public DrawObject {
	public:
		Ball(Board *board);
		Ball(Board * board, GLfloat xPos, GLfloat yPos, GLfloat zPos);


	private:
		Board *board;
		void draw(GLuint time);
		void doPhysics(GLuint time);

		const float gravity = 9.81f;

		void initBallGeometry();
		void subdivide(float *v1, float *v2, float *v3, long depth);
		void normalize(float v[3]);
		void init();
		GLfloat xPos, yPos, zPos;
		GLfloat xSpeed, ySpeed, zSpeed;
		GLfloat xAcc, yAcc, zAcc;
		vec4 radius;

		const GLfloat scaleFactor = 0.25;

		GLuint *vertexBuffers;
		GLuint vertexCount;

		boost::container::vector<GLfloat> ballVertices;

		GLuint shader;

		GLuint s_ballPos;
		GLuint s_time;
		GLuint s_speed;
		GLuint s_scaleFactor;

		GLuint lastUpdate;
};


#endif /* end of include guard: BALL_HPP */
