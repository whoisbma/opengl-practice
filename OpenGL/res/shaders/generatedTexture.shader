#shader vertex
#version 330 core 

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec3 a_color;

out vec2 v_texCoord;
out vec3 v_color;

uniform mat4 u_MVP;
uniform float u_scale;

void main()
{
	gl_Position = u_MVP * a_position;
	v_texCoord = a_texCoord * u_scale;
	v_color = a_color;
};

//---------------------------------------

#shader fragment
#version 330 core

in vec2 v_texCoord;
in vec3 v_color;

layout(location = 0) out vec4 gl_FragColor;

uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoord);
	gl_FragColor = texColor * vec4(v_color, 1.0);
};
