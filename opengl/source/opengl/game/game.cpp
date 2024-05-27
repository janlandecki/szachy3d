#include <opengl/game/game.h>
#include <Windows.h>
#include <opengl/window/window.h>
#include <opengl/graphics/VertexArrayObject.h>
#include <opengl/graphics/ShaderProgram.h>
#include <opengl/graphics/UniformBuffer.h>

struct UniformData
{
	f32 movement;
};

game::game()
{
	m_graphicsEngine = std::make_unique<graphicsengine>();
	m_display = std::make_unique<window>();
	m_display->makeCurrentContext();
	m_graphicsEngine->setViewport(m_display->getInnerSize());
}
game::~game(){}
void game::onCreate()
{
	const f32 polygonVertices[] = {
		-0.5f,-0.5f,0.0f,
		1    ,0    ,0   ,

		-0.5f, 0.5f,0.0f,
		1    ,1    ,1   ,

		0.5f, -0.5f,0.0f,
		1   ,0    ,0  ,

		0.5f, 0.5f,0.0f,
		1   ,1   ,1,
		0.8f, 0.9f,0.0f,
		1   ,1   ,1
	};
	VertexAttribute attribsList[] = {
		3,//pozycja
		3 //kolor
	};
	m_polygonVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)polygonVertices,
		sizeof(f32) * (3 + 3),
		5,

		attribsList,
		2
		});

	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		});

	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"assets/shaders/testshader.vert",
			L"assets/shaders/testshader.frag"
		});

	m_shader->setUniformBufferSlot("UniformData", 0);
}

void game::onUpdate()
{
	//mierzenie czasu do animacji
	auto currentTime = std::chrono::system_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
		elapsedSeconds = currentTime - m_previousTime;
	m_previousTime = currentTime;
	auto deltaTime = (f32)elapsedSeconds.count();
	m_movement += deltaTime;
	auto currentPos = sin(m_movement);
	UniformData data = { currentPos };
	m_uniform->setData(&data);

	//kolor t³a
	m_graphicsEngine->clear(vec4(0.6, 0, 0.65, 1));

	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);
	m_graphicsEngine->setShaderProgram(m_shader);
	m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);

	m_display->present(false);
}
void game::run()
{
	onCreate();
	while (m_isRunning)
	{
		MSG msg = {};
		if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		onUpdate();
	}

	onQuit();
}
void game::onQuit(){}
void game::quit()
{
	m_isRunning = false;
}