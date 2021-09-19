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
	
	eventDispatcher.addEventListener<Engine::MouseMoveEvent>(
		[](Engine::MouseMoveEvent& mouse) {
			LOG_INFO("Event pos:{0},{1}", mouse.x, mouse.y);
		});

	eventDispatcher.addEventListener<Engine::WindowResize>(
		[](Engine::WindowResize& win) {
			LOG_INFO("Event size:{0}x{1}", win.w, win.h);
		});

	eventDispatcher.addEventListener<Engine::EventWinClose>(
		[&](Engine::EventWinClose& win) {
			LOG_INFO("[Win Closed]");
			closeWin = true;
		});



	win1->setCallback(
		[&](BaseEvent& event) {
			eventDispatcher.dispatch(event);
		});




	while (!closeWin)
	{
		win1->update();
		update();
	}

    return 0;
}

void Engine::Core::update()
{
}
