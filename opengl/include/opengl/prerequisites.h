#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class VertexArrayObject;
class UniformBuffer;
class ShaderProgram;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct VertexAttribute
{
	ui32 numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	ui32 vertexSize = 0;
	ui32 listSize = 0;

	VertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct UniformBufferDesc
{
	ui32 size = 0;
};

enum TriangleType
{
	TriangleList = 0,
	TriangleStrip
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};

#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;


#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;