#include "Application.h"
#include <iostream>

int main()
{
#if !DEBUG
	FreeConsole();
	std::cout.setstate(std::ios_base::failbit);
#endif
	Application& app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	return 0;
}