#version 330 core
layout(location = 0)out vec4 color;

uniform sampler2D _texture;

in vec2 texCoord0;
in vec3 color0;

void main()
{
	color = texture2D(_texture, texCoord0) * vec4(color0, 1);
}