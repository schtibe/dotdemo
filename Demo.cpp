#include "Demo.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "engine/Shader.hpp"
#include <string>

using namespace glm;

Demo::Demo() {
	dotAmount = 42;
	arms = 3;

	glEnable(GL_PROGRAM_POINT_SIZE);

	shader = Shader::loadShaders("dot.vert", "dot.frag");
	
	/*
#include "dot_vert_string.cpp"
#include "dot_frag_string.cpp"

	string vertShader = string(dot_vert, dot_vert + dot_vert_len);
	string fragShader = string(dot_frag, dot_frag + dot_frag_len);
	
	shader = Shader::generateShaders(vertShader, fragShader);
	*/

	s_time = glGetUniformLocation(shader, "time");
	s_amount = glGetUniformLocation(shader, "amount");
	s_arms = glGetUniformLocation(shader, "arms");
	s_mvp = glGetUniformLocation(shader, "MVP");
}

void Demo::renderFunc(GLuint time, Engine engine) {
	glUseProgram(shader);

	mat4 projection = perspective(45.0f, 1.0f, 0.1f, 100.0f);

	mat4 view = lookAt(
			vec3(0, 0, 20),
			vec3(0, 0, 0),
			vec3(0, 1, 0)
	);
	mat4 model = mat4(1.0);

	mat4 MVP = projection * view * model;

	glUniform1ui(s_time, time);
	glUniform1ui(s_amount, dotAmount);
	glUniform1ui(s_arms, arms);
	glUniformMatrix4fv(s_mvp, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_POINTS, 0, dotAmount);
}
