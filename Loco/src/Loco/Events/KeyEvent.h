#pragma once

#include "Event.h"

namespace Loco {

	class LOCO_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
	protected:
		int m_KeyCode;
	};

	class LOCO_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " :: " << m_RepeatCount << " repeats";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED)
	private:
		int m_RepeatCount;
	};

	class LOCO_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

	class LOCO_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_TYPED)
	};
}