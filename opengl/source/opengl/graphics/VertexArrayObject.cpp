#include <opengl/graphics/VertexArrayObject.h>
#include <glad/glad.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	if (!data.listSize) OGL3D_ERROR("VertexArrayObject | listSize is NULL");
	if (!data.vertexSize) OGL3D_ERROR("VertexArrayObject | vertexSize is NULL");
	if (!data.verticesList) OGL3D_ERROR("VertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (ui32 i = 0; i < data.attributesListSize; i++)
	{
		glVertexAttribPointer(
			i,
			data.attributesList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			data.vertexSize,
			(void*)((i == 0) ? 0 : data.attributesList[i - 1].numElements * sizeof(f32))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 VertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

ui32 VertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 VertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
