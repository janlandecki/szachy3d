#include "opengl/graphics/graphicsengine.h"
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <assert.h>
#include <opengl/graphics/VertexArrayObject.h>
#include <opengl/graphics/ShaderProgram.h>
#include <opengl/graphics/UniformBuffer.h>

VertexArrayObjectPtr graphicsengine::createVertexArrayObject(const VertexBufferDesc& data)
{
    return std::make_shared<VertexArrayObject>(data);
}

UniformBufferPtr graphicsengine::createUniformBuffer(const UniformBufferDesc& desc)
{
    return std::make_shared<UniformBuffer>(desc);
}

ShaderProgramPtr graphicsengine::createShaderProgram(const ShaderProgramDesc& desc)
{
    return std::make_shared<ShaderProgram>(desc);
}

void graphicsengine::clear(const vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void graphicsengine::setViewport(const rect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

void graphicsengine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

void graphicsengine::setUniformBuffer(const UniformBufferPtr& buffer, ui32 slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void graphicsengine::setShaderProgram(const ShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void graphicsengine::drawTriangles(const TriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
    case TriangleList: { glTriType = GL_TRIANGLES; break; }
    case TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }

    glDrawArrays(glTriType, offset, vertexCount);
}
graphicsengine::graphicsengine()
{
    WNDCLASSEX windowClass = {};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = DefWindowProcA;
    windowClass.lpszClassName = L"dummy";
    windowClass.cbSize = sizeof(WNDCLASSEX);

    auto classId = RegisterClassEx(&windowClass);

    HWND dummyWindow = CreateWindowEx(
        0,
        MAKEINTATOM(classId),
        L"dummy",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        windowClass.hInstance,
        0);

    assert(dummyWindow);

    HDC dummyDC = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
    SetPixelFormat(dummyDC, pixelFormat, &pfd);



    HGLRC dummyContext = wglCreateContext(dummyDC);
    assert(dummyContext);

    bool res = wglMakeCurrent(dummyDC, dummyContext);
    assert(res);


    if (!gladLoadWGL(dummyDC))
        OGL3D_ERROR("graphicsengine - gladLoadWGL failed");

    if (!gladLoadGL())
        OGL3D_ERROR("graphicsengine - gladLoadGL failed");


    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);
}


graphicsengine::~graphicsengine()
{
}