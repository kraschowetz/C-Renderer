#version 410 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 color;

uniform float time;
uniform mat4 u_model;
uniform mat4 u_perspective;
uniform mat4 u_view;

out vec3 vertex_color;

void main() {
	
	const float time_cut_point = 0.75;
	const float time_multiplier = 1.65;
	const float time_damp = 0.1;
	float offset = sin(time * time_multiplier);
	if(offset > time_cut_point) {
		offset = time_cut_point;
	}
	offset *= time_damp;

	vec4 _position = u_perspective * u_view * u_model * vec4(pos, 1.0f);

	gl_Position = vec4(
		_position.x,
		_position.y + offset,
		_position.z,
		_position.w
	);

	vertex_color = color;
}
