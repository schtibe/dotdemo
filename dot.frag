#version 130


varying vec3 position;

varying float pointSize;

uniform int move;

void main() {
	vec2 distance = gl_PointCoord.st;

	distance.s = abs(0.5 - distance.s);
	distance.t = abs(0.5 - distance.t);
	
	float alpha = 1 - (2 * length(distance));
	if (alpha < 0.1) {
		discard;
	}
	gl_FragColor = vec4(1.0, 0.0, 0.0, alpha);

	/*
	if (length(distance) > 0.2) {
		gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else if (move == 1) {
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else {
		gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
	*/
}
