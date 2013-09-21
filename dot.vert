#version 130

const float pi = 3.1415926;
const float end = 4.5;
const float arms = 3;

uniform uint amount;
uniform uint time;

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
	
	float startPos = pi / (amount / (arms * 2)) * number;
	float pos = sin(startPos + time * 0.002) * end / 2;

	position = position + (position * ((end / B) * (end / 2 + pos)));

	gl_PointSize = pointSize = 20.0;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);

	dotNumber = number;
}
