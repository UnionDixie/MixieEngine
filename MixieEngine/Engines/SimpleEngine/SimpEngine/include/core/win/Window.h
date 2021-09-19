#pragma once

#include <core/utility/Event.h>

#include <string_view>
#include <functional>

struct GLFWwindow;

namespace Engine {

	class Window
	{
	public:
		using EventCallBack = std::function<void(BaseEvent&)>;
	public:
		Window(std::string_view title, int width, int height);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

		void update();
		std::pair<size_t, size_t> getSize() const;

		void setCallback(const EventCallBack& callbackFun);

	private:
		int init();
		void destroy();
	private:
		struct WinData
		{
			WinData(std::string_view title, int w, int h) :
				title(title),sizeWindow(w,h)
			{
			}
			std::string_view title;
			std::pair<size_t, size_t> sizeWindow;
			EventCallBack callbackEvent;
		} data;

		GLFWwindow* window = nullptr;

	};
	static bool glfwIsInit = false;
}