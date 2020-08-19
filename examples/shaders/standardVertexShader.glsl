#version 130

in vec2 vTextureCoordinate;
in vec2 vertexPosition;
out vec2 textureCoordinate;

void main() {
    textureCoordinate= vTextureCoordinate;
	gl_Position = vec4(vertexPosition.xy,0,1);

}