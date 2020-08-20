#version 130

in vec2 textureCoordinate;
out vec4 fColour;

uniform sampler2D image;

void main(){

	if(int(textureCoordinate.y * 100) %5 == 0) {
		fColour = vec4(1,0,0,1);
	} else {
		fColour= texture2D(image,textureCoordinate);
	}
}