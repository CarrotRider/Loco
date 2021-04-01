#pragma once
#include "Window.h"

class GLFWwindow;

namespace Loco {
	
	class WindowsWindow :
		public Window
	{
	public: 
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned GetWidth() const override { return m_Data.Width; }
		unsigned GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVsync() const override;

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}


