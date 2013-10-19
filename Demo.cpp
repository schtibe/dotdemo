#include "Demo.hpp"

#include <glm/glm.hpp>
#include "engine/Camera.hpp"

#include "engine/Shader.hpp"
#include <string>

#include "engine/glmUtils.hpp"


#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

using namespace glm;

Demo::Demo() :
	mode(true){
	dotAmount = 42;
	arms = 3;

	Camera::inst()->init(vec3(0, 0, 20),
						 vec3(0, 0, 0),
						 vec3(0, 1, 0));

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

#ifndef XSCREENSAVER
	shader = Shader::loadShaders("dot.vert", "dot.frag");
	polyShader = Shader::loadShaders("poly.vert", "poly.frag");
#else

#include "dot_vert_string.cpp"
#include "dot_frag_string.cpp"

#include "poly_vert_string.cpp"
#include "poly_frag_string.cpp"

	string vertShader = string(dot_vert, dot_vert + dot_vert_len);
	string fragShader = string(dot_frag, dot_frag + dot_frag_len);
	string polyVert   = string(poly_vert, poly_vert + poly_vert_len);
	string polyFrag   = string(poly_frag, poly_frag + poly_frag_len);
	
	shader = Shader::generateShaders(vertShader, fragShader);
	polyShader = Shader::generateShaders(polyVert, polyFrag);
#endif

	s_time       = glGetUniformLocation(shader, "he_time");
	s_amount     = glGetUniformLocation(shader, "amount");
	s_arms       = glGetUniformLocation(shader, "arms");
	s_projection = glGetUniformLocation(shader, "he_projection");
	s_view       = glGetUniformLocation(shader, "he_view");

	GLfloat polyVertArray[] = {
		-1, 1, 0,
		1, 1, 0,
		-1, -1, 0,
		1, 1, 0,
		1, -1, 0,
		-1, -1 ,0
	};

	glGenBuffers(1, &polyBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, polyBuffer);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(polyVertArray),
		polyVertArray,
		GL_STATIC_DRAW
	);
}

void Demo::renderFunc(GLuint time, Engine engine) {
	if (mode) {
		glUseProgram(shader);

		glUniform1ui(s_time, time);
		glUniform1ui(s_amount, dotAmount);
		glUniform1ui(s_arms, arms);

		mat4 projection = Camera::inst()->projection();
		mat4 view       = Camera::inst()->view();

		glUniformMatrix4fv(s_projection , 1 , GL_FALSE , &projection[0][0]);
		glUniformMatrix4fv(s_view       , 1 , GL_FALSE , &view[0][0]);

		glDrawArrays(GL_POINTS, 0, dotAmount);
	}
	else {
		glUseProgram(polyShader);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, polyBuffer);

		glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				BUFFER_OFFSET(0)
		);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
	}

	mode = !mode;
}
