#pragma once

#include <opengl/prerequisites.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& data);
	~VertexArrayObject();

	ui32 getId();
	ui32 getVertexBufferSize();
	ui32 getVertexSize();
private:
	ui32 m_vertexBufferId = 0;
	ui32 m_vertexArrayObjectId = 0;
	VertexBufferDesc m_vertexBufferData;
};