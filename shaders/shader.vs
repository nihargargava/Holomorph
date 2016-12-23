#version 330 core
#define T_THRES 0.00001


layout (location = 0) in vec2 position;

uniform float t;

void function(in vec2 z, out vec2 w)
{

	w= vec2( z.x ,z.x*z.x + z.y);
}

void homotopy(in vec2 z, in float s, out vec2 w)
{
	// To be written
	w=t*z;
}

void main()
{
	vec2 h;
	homotopy(position, t, h);
    gl_Position = vec4(h.x , h.y, 1.0f, 1.0f);
}