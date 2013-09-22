#include "Demo.hpp"

#include "engine/Shader.hpp"

using namespace glm;

Demo::Demo() {
	dotAmount = 42;
	arms = 3;

	glEnable(GL_PROGRAM_POINT_SIZE);

	shader = Shader::loadShaders("dot.vert", "dot.frag");
	s_time = glGetUniformLocation(shader, "time");
	s_amount = glGetUniformLocation(shader, "amount");
	s_arms = glGetUniformLocation(shader, "arms");
}

void Demo::renderFunc(GLuint time, Engine engine) {
	glUseProgram(shader);

	glUniform1ui(s_time, time);
	glUniform1ui(s_amount, dotAmount);
	glUniform1ui(s_arms, arms);

	glDrawArrays(GL_POINTS, 0, dotAmount);
}
