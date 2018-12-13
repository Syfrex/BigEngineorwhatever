#include "Files/LogFile.h"
#include "Engine/Engine.h"

int main(int argc, char* argv[])
{
	
	Big::Engine engine;

	if (!engine.Create())
	{
		engine.Destroy();
		return -1;
	}
	engine.Update();
	engine.Destroy();
	
	return 0;
}
