#include "..\..\include\core\core.h"

#include <iostream>
#include <core/utility/log.h>
#include <core/win/Window.h>

Engine::Core::Core()
{
    std::cout << "\tEngineCore\n";
}

int Engine::Core::init(ui width, ui height, std::string_view title)
{
	win1 = std::make_unique<Window>(title, width, height);
	win1->setCallback(
		[](Engine::Event& ev) {
			LOG_INFO("Event {0}x{1}", ev.width, ev.height);
		}
	);

	while (true)
	{
		win1->update();
		update();
	}

    return 0;
}

void Engine::Core::update()
{
}
