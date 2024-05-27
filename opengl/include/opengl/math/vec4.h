#pragma once
#include <opengl/prerequisites.h>

class vec4{
public:
	vec4(){}
	vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w){}
	~vec4(){}
	f32 x = 0, y = 0, z = 0, w = 0;
};