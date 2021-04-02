#pragma once

#include "Event.h"

namespace Loco {

	class LOCO_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WINDOW_CLOSE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APP)
	};

	class LOCO_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned width, unsigned height)
			: m_Width(width), m_Height(height) {}

		unsigned GetWidth() const { return m_Width; }
		unsigned GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APP)

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

}
