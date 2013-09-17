#version 130

varying vec3 position;

varying float pointSize;

void main() {

	gl_PointSize = pointSize = 20.0;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	position = gl_Vertex.xyz;
}
