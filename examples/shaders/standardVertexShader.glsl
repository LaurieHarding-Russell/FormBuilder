#version 130

in vec3 vTextureCoordinate;
in vec3 vertexPosition;
out vec2 textureCoordinate;

void main() {
    textureCoordinate= vTextureCoordinate.xy;
	gl_Position = vec4(vertexPosition.xy,0,1);
    gl_PointSize = 10.0;

}