#pragma once
#include <memory>
#include <opengl/graphics/graphicsengine.h>
#include <chrono>

class window;

class game
{
public:
	game();
	~game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();


	void run();
	void quit();
protected:
	bool m_isRunning = true;

	std::unique_ptr<graphicsengine> m_graphicsEngine;
	std::unique_ptr<window> m_display;


	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;

	std::chrono::system_clock::time_point m_previousTime;
	f32 m_movement = 0;
};

