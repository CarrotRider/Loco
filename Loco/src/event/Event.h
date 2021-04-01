#pragma once
#include "stdafx.h"

#define BIT(x) (1 << x)

namespace Loco {

	enum class EventType
	{
		NONE,
		WINDOW_CLOSE, WINDOW_RESIZE,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};

	enum EventCategoty
	{
		None = 0,
		EVENT_CATEGORY_APP			= BIT(0),
		EVENT_CATEGORY_INPUT		= BIT(1),
		EVENT_CATEGORY_KEYBOARD		= BIT(2),
		EVENT_CATEGORY_MOUSE		= BIT(3),
		EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								EventType GetEventType() const override { return GetStaticType(); }\
								const char* GetName() const override { return #type; }

#define  EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategoty category)
		{
			return GetCategoryFlags() & static_cast<int>(category);
		}
	};

	std::ostream& operator<<(std::ostream& os, const Event& e);
}