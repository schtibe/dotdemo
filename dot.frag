#version 130

out float pointSize;
flat in int dotNumber;

uniform uint he_time;
uniform uint amount;

out vec4 out_color;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
	vec2 distance = gl_PointCoord.st;

	distance.s = abs(0.5 - distance.s);
	distance.t = abs(0.5 - distance.t);

	float step = 1.0 / float(amount);
	float hue = float(dotNumber) * step;

	hue -= float(he_time) * 0.0001;

	vec3 color = hsv2rgb(vec3(hue, 1, 1));
	
	float len = sqrt(pow(distance.s, 2) + pow(distance.t, 2));

	float alpha = 1.0 - (2.0 * len);
	if (alpha < 0.1) {
		discard;
	}
	out_color = vec4(color.xyz, alpha);
}
