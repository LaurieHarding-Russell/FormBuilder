#version 130

in vec2 textureCoordinate;
out vec4 fColour;

uniform sampler2D image;

void main(){

	if(int(textureCoordinate.y * 250) %25 == 0) {
		fColour = texture(image,textureCoordinate) + vec4(1,0,0,0.5);
	} else {
		fColour= texture(image,textureCoordinate);
	}
}