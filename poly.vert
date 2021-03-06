#version 130

uniform mat4 he_projection;
uniform mat4 he_view;

in vec3 position;

void main() {
	float scale = 10;

	mat4 scaler = mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1
	);

	gl_Position = he_projection * he_view * scaler * vec4(position, 1);
}
