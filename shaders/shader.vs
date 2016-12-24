#version 330 core
#define T_THRES 0.00001
#define PI 3.14159268
#define SCALE 3

layout (location = 0) in vec2 position;

out float flag;

uniform float t;
uniform vec2 mouse;
uniform int animate;
uniform int winder;
uniform int mouse_flag;


vec2 nlog(in vec2 z)
{	vec2 w;
	float r = sqrt(z.x*z.x + z.y*z.y);
	if (z.y>=0 )w.y = acos(z.x/r);
	else w.y = -acos(z.x/r);
	w.x = log(r);
	return w;
}

vec2 nexp( in vec2 z)
{	vec2 w;
	float ex = exp(z.x);
	w.x = ex*cos(z.y);
	w.y = ex*sin(z.y);
	return w;
}

vec2 function(in vec2 z)
{

	mat2 w= mat2(z.x, z.y , -z.y , z.x);
	mat2 J= mat2(0, -1 , 1, 0);
	mat2 K=mat2(-1,0,0,-1);
	//w=w*J;
	w=w*K;
	return vec2(w[0]);
}

vec2 function2(in vec2 z)
{

	mat2 w= mat2(z.x, z.y , -z.y , z.x);
	mat2 J= mat2(0, -1 , 1, 0);
	mat2 K=mat2(-1,0,0,-1);
	//w=w*J;
	w=w*J;
	return vec2(w[0]);
}

vec2 itimes(in vec2 z)
{

	return function2(function(z));
}

vec2 cos(in vec2 z)
{
	vec2 w;
	w = 0.5*(nexp(itimes(z)));
	w+=0.5*nexp(function2(z));
	//
	return w;
}
vec2 inverse(in vec2 z)
{
	vec2 w=vec2(z.x,-z.y);
	w/=z.x*z.x + z.y*z.y;
	return w;
}





vec2 modify(in vec2 z)
{
	vec2 w;
	w=nexp(z);
	return w;
}
vec2 unmodify(in vec2 z)
{
	vec2 w;
	w =nlog(z);
	return w;
}

vec2 homotopy(in vec2 z, in float s)
{
	vec2 w;
	if (s> T_THRES)
		w = function(modify(s*z))/s;
	else
		w= modify(z);

	return unmodify(w);
	
}

void main()
{

	vec2 h,m,o;
	o=SCALE*position;
	m=o + SCALE*mouse*mouse_flag;

	if(animate==1) //h = nexp((1+t)*nlog(m));
		h=nlog(m);
	else h=m;

	h=h/SCALE;	


    gl_Position = vec4(h.x , h.y, 1.0f, 1.0f);

    flag = animate;
}