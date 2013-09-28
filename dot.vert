#version 130


const float pi = 3.1415926;
const float displacement = 1.8;

uniform uint arms;
uniform uint amount;

uniform uint he_time;
uniform mat4 he_projection;
uniform mat4 he_view;
uniform vec2 he_mouse;

out float pointSize;

flat out int dotNumber;

mat4 view() {
	float xAngle = -he_mouse.y * 0.002;
	float yAngle = he_mouse.x * 0.002;
	mat4 rotX = mat4(
			1, 0, 0, 0,
			0, cos(xAngle), -sin(xAngle),  0,
			0, sin(xAngle), cos(xAngle),  0,
			0, 0, 0, 1
	);

	mat4 rotY = mat4(
		cos(yAngle), sin(yAngle), 0, 0,
		0, 1, 0, 0,
		sin(yAngle), 0, cos(yAngle), 0,
		0, 0, 0, 1
	);

	return rotX * rotY * he_view;
}


void main() {
	int number = gl_VertexID;

	float angle = ((2 * pi) / amount) * number;

	vec3 unit = vec3(1.0);
	mat3 rot = mat3(
			cos(angle), -sin(angle), 0,
			sin(angle),  cos(angle), 0,
			0, 0, 1
	);

	vec3 position = rot * unit;

	float a = amount / arms;
	float B = a * 0.5;
	
	float startPos = pi / B * number;
	float he_timed = float(he_time) * 0.002;
	float pos = sin(startPos + he_timed) * displacement / 2;

	position = position + (position * (displacement * (displacement / 2 + pos)));

	gl_PointSize = pointSize = 20.0;
	gl_Position = he_projection * view() * vec4(position, 1.0);
	gl_Position = vec4(0, 0, 0, 1);

	dotNumber = number;
}
