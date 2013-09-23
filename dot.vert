#version 130


const float pi = 3.1415926;
const float displacement = 1.8;

uniform uint arms;
uniform uint amount;
uniform uint time;
uniform mat4 MVP;

varying float pointSize;

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

	float B = (amount / arms) * 0.5;
	
	float startPos = pi / B * number;
	float pos = sin(startPos + time * 0.002) * displacement / 2;

	position = position + (position * (displacement * (displacement / 2 + pos)));

	gl_PointSize = pointSize = 20.0;
	gl_Position = MVP * vec4(position, 1.0);

	dotNumber = number;
}
