#include "Demo.hpp"

#include "engine/Shader.hpp"

using namespace glm;

Demo::Demo() {
	dotAmount = 42;

	glEnable(GL_PROGRAM_POINT_SIZE);

	shader = Shader::loadShaders("dot.vert", "dot.frag");
	s_time = glGetUniformLocation(shader, "time");
	s_amount = glGetUniformLocation(shader, "amount");
}

void Demo::renderFunc(GLuint time, Engine engine) {
	glUseProgram(shader);

	glUniform1ui(s_time, time);
	glUniform1ui(s_amount, dotAmount);

	glDrawArrays(GL_POINTS, 0, dotAmount);
}
