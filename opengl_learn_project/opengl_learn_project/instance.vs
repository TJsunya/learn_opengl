#version 330 core
layout (location=0) in vec2 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aOffset;

out vec3 color;
void main(){
	gl_Position = vec4(aPos.x + aOffset.x, aPos.y + aOffset.y, 0.0, 1.0);
	color = aColor;
}