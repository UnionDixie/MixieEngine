#pragma once

#include <array>
#include <functional>

namespace Engine {

	enum class EventType {
		WindowResize = 0,
		WindowClose,

		KeyPress,
		KeyRelease,

		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,

		EventsCount
	};

	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual EventType get_type() const = 0;
	};

	struct Event
	{
		size_t width, height;
	};

	class EventDispatcher {
	public:

		template<typename EventType>
		void addEventListener(std::function<void(EventType&)> callback) {
			auto baseCallback = [func = std::move(callback)](BaseEvent& event){
				if (event.get_type() == EventType::type) {
					func(static_cast<EventType&>(event));
				}
			};
			eventCallbacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
		}

		void dispatch(BaseEvent& event) {
			auto& callback = eventCallbacks[static_cast<size_t>(event.get_type())];
			if (callback)
				callback(event);
		}

	private:
		std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> eventCallbacks;
	};

	struct MouseMoveEvent : public BaseEvent
	{
		MouseMoveEvent(double x, double y) :x(x),y(y) {}

		virtual EventType get_type() const override {
			return type;
		}
		double x, y;
		static const EventType type = EventType::MouseMove;
	};

	struct WindowResize : public BaseEvent
	{
		WindowResize(size_t w, size_t h) :w(w), h(h) {}

		virtual EventType get_type() const override {
			return type;
		}
		size_t w, h;
		static const EventType type = EventType::WindowResize;
	};

	struct EventWinClose : public BaseEvent
	{
		virtual EventType get_type() const override {
			return type;
		}
		static const EventType type = EventType::WindowClose;
	};


}