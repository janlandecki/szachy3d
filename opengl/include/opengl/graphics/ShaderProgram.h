#pragma once

#include <opengl/prerequisites.h>

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	ui32 getId();
	void setUniformBufferSlot(const char* name, ui32 slot);
private:
	void attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void link();
	ui32 m_programId = 0;
	ui32 m_attachedShaders[2] = {};
};