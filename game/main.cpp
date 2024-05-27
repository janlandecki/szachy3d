#include <opengl/game/game.h>
#include <iostream>

int main()
{
	try
	{
		game game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::wclog << e.what() << std::endl;
		return -1;
	}

	return 0;
}