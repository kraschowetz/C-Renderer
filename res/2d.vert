#version 410 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 color;

uniform float time;
uniform mat4 u_model_mat;
uniform mat4 u_perspective;

out vec3 vertex_color;

void main() {
	
	vec4 _position = u_perspective * u_model_mat * vec4(pos, 1.0f);

	gl_Position = vec4(
		_position.x,
		_position.y,
		_position.z,
		_position.w
	);

	vertex_color = color;
}

