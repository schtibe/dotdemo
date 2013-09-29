#version 130


const float pi = 3.1415926;
const float displacement = 1.8;

uniform uint arms;
uniform uint amount;

uniform uint he_time;
uniform mat4 he_projection;
uniform mat4 he_view;

out float pointSize;

flat out int dotNumber;


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

	dotNumber = number;

	gl_PointSize = pointSize = 20.0;
	gl_Position = he_projection * he_view * vec4(position, 1.0);

}
