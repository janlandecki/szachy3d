#include <opengl/graphics/ShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

ui32 ShaderProgram::getId()
{
	return m_programId;
}

void ShaderProgram::setUniformBufferSlot(const char* name, ui32 slot)
{
	ui32 index = glGetUniformBlockIndex(m_programId, name);
	glUniformBlockBinding(m_programId, index, slot);
}

void ShaderProgram::attach(const wchar_t* shaderFilePath, const ShaderType& type)
{
	std::string shaderCode;

	auto path = std::filesystem::path(shaderFilePath);

	std::ifstream shaderStream(path);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		OGL3D_WARNING("Shader | " << shaderFilePath << " not found");
		return;
	}

	ui32 shaderId = 0;
	if (type == VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	i32 logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("Shader | " << shaderFilePath << " compiled with errors:" << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[type] = shaderId;

	OGL3D_INFO("Shader | " << shaderFilePath << " compiled successfully");
}

void ShaderProgram::link()
{
	glLinkProgram(m_programId);

	i32 logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("Shader | " << &errorMessage[0]);
		return;
	}
}