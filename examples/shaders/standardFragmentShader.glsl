#version 130

in vec2 textureCoordinate;
out vec4 fColour;

uniform sampler2D image;

void main() {
	// fColour= texture(image,textureCoordinate);
	fColour= vec4(texture(image,textureCoordinate).xyz, 1.0);
}