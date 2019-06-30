#shader vertex
#version 330 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 v_color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_color = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_color;
uniform float u_time;

void main()
{
	color = vec4(v_color, 0.5 + sin(u_time * 0.01) * 0.5);
};
