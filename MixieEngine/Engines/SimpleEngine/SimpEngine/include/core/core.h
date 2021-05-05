#pragma once

#include <string_view>

namespace Engine {

	class Core
	{
	private:
		using ui = unsigned int;
	public:
		Core();
		virtual ~Core() = default;

		Core(const Core&) = delete;
		Core& operator=(const Core&) = delete;
		Core(Core&&) = delete;
		Core& operator=(Core&&) = delete;

		virtual int init(ui width, ui height, std::string_view title);
		virtual void update();

	private:

	};

}