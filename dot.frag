#version 130


varying vec3 position;

uniform int move;

void main() {

	vec2 distance = gl_PointCoord.xy - position.xy;

	if (move == 1) {
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else {
		gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
}
