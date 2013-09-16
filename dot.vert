#version 130

varying vec3 position;

void main() {

	gl_PointSize = 10.0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	position = gl_Vertex.xyz;
}
