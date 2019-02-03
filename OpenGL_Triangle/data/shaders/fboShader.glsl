#vertexShader
#version 330 core
layout(location = 0)in vec2 pos;
layout(location = 1)in vec2 texCoord;

out vec2 texCoord0;

void main()
{
	gl_Position = vec4(pos, 0.0, 1.0);
	texCoord0 = texCoord;
}

#fragmentShader
#version 330 core
layout(location = 0)out vec4 color;

uniform sampler2D _texture;

in vec2 texCoord0;

void main()
{
	color = texture2D(_texture, texCoord0);
}