#version 330 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 texCoord;
layout(location = 2)in vec3 color;

uniform mat4 _proj;
uniform mat4 _view;
uniform mat4 _model;

out vec2 texCoord0;
out vec3 color0;

void main()
{
	gl_Position = _proj * _view * _model * vec4(pos, 1);
	texCoord0 = texCoord;
	color0 = color;
}