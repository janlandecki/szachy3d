#pragma once

#include <opengl/prerequisites.h>
#include <opengl/math/vec4.h>
#include <opengl/math/rect.h>

class graphicsengine
{
public:
    graphicsengine();
    ~graphicsengine();
    VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& data);
    UniformBufferPtr createUniformBuffer(const UniformBufferDesc& desc);
    ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);
    void clear(const vec4& color);
    void setViewport(const rect& size);
    void setVertexArrayObject(const VertexArrayObjectPtr& vao);
    void setUniformBuffer(const UniformBufferPtr& buffer, ui32 slot);
    void setShaderProgram(const ShaderProgramPtr& program);
    void drawTriangles(const TriangleType& triangleType, ui32 vertexCount, ui32 offset);
};

