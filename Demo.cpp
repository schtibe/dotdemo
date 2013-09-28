#include "Demo.hpp"

#include <glm/glm.hpp>
#include "engine/Camera.hpp"

#include "engine/Shader.hpp"
#include <string>

using namespace glm;

Demo::Demo() {
	dotAmount = 42;
	arms = 3;

	Camera::inst()->init(vec3(0, 0, 20),
						 vec3(0, 0, 0),
						 vec3(0, 1, 0));

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	shader = Shader::loadShaders("dot.vert", "dot.frag");
	
	/*
#include "dot_vert_string.cpp"
#include "dot_frag_string.cpp"

	string vertShader = string(dot_vert, dot_vert + dot_vert_len);
	string fragShader = string(dot_frag, dot_frag + dot_frag_len);
	
	shader = Shader::generateShaders(vertShader, fragShader);
	*/

	s_time       = glGetUniformLocation(shader, "he_time");
	s_amount     = glGetUniformLocation(shader, "amount");
	s_arms       = glGetUniformLocation(shader, "arms");
	s_projection = glGetUniformLocation(shader, "he_projection");
	s_view       = glGetUniformLocation(shader, "he_view");
	s_mouse      = glGetUniformLocation(shader, "he_mouse");
}

void Demo::renderFunc(GLuint time, Engine engine) {
	glUseProgram(shader);

	glUniform1ui(s_time, time);
	glUniform1ui(s_amount, dotAmount);
	glUniform1ui(s_arms, arms);


	mat4 projection = Camera::inst()->projection();
	mat4 view       = Camera::inst()->view();
	vec2 mouse      = Camera::inst()->mouse();

	glUniformMatrix4fv(s_projection , 1 , GL_FALSE , &projection[0][0]);
	glUniformMatrix4fv(s_view       , 1 , GL_FALSE , &view[0][0]);
	glUniform2f(s_mouse      , mouse.x, mouse.y);

	glDrawArrays(GL_POINTS, 0, dotAmount);
}
