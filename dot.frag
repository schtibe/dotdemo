#version 130


varying vec3 position;
varying float pointSize;

uniform int move;
uniform int number;
uniform int time;
uniform int amount;

/*
 * GLSL HSV to RGB+A conversion. Useful for many effects and shader debugging.
 *
 * Copyright (c) 2012 Corey Tabaka
 *
 * Hue is in the range [0.0, 1.0] instead of degrees or radians.
 * Alpha is simply passed through for convenience.
 */
vec4 hsv_to_rgb(float h, float s, float v, float a) {
	float c = v * s;
	h = mod((h * 6.0), 6.0);
	float x = c * (1.0 - abs(mod(h, 2.0) - 1.0));
	vec4 color;
 
	if (0.0 <= h && h < 1.0) {
		color = vec4(c, x, 0.0, a);
	} else if (1.0 <= h && h < 2.0) {
		color = vec4(x, c, 0.0, a);
	} else if (2.0 <= h && h < 3.0) {
		color = vec4(0.0, c, x, a);
	} else if (3.0 <= h && h < 4.0) {
		color = vec4(0.0, x, c, a);
	} else if (4.0 <= h && h < 5.0) {
		color = vec4(x, 0.0, c, a);
	} else if (5.0 <= h && h < 6.0) {
		color = vec4(c, 0.0, x, a);
	} else {
		color = vec4(0.0, 0.0, 0.0, a);
	}
 
	color.rgb += v - c;
 
	return color;
}

void main() {
	vec2 distance = gl_PointCoord.st;

	distance.s = abs(0.5 - distance.s);
	distance.t = abs(0.5 - distance.t);

	float step = 1.0 / amount;
	float hue = number * step;

	hue -= time * 0.0001;

	vec4 color = hsv_to_rgb(hue, 1, 1, 1);
	
	float alpha = 1 - (2 * length(distance));
	if (alpha < 0.1) {
		discard;
	}
	gl_FragColor = vec4(color.xyz, alpha);
}
