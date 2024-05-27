#pragma once
#include <opengl/math/rect.h>

class window
{
public:
	window();
	~window();

	rect getInnerSize();
	void makeCurrentContext();
	void present(bool vsync);
private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};

