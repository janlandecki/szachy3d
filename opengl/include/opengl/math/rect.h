#pragma once
#include <opengl/prerequisites.h>

class rect
{
public:
	rect() {}
	rect(i32 width, i32 height) :width(width), height(height) {}
	rect(i32 left, i32 top, i32 width, i32 height) :left(left), top(top), width(width), height(height) {}
	rect(const rect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height) {}
public:
	i32 width = 0, height = 0, left = 0, top = 0;
};