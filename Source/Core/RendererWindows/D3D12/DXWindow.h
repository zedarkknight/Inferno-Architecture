#ifndef DXWINDOW_H
#define DXWINDOW_H
#include <string>
#include "Includes/WinIncludes.h"

namespace AppCore
{
	struct WindowSpecData
	{
		std::string Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizable = true;
		bool VSync = true;
	};

	class DXWindow
	{
	public:
		DXWindow(const WindowSpecData& specData = WindowSpecData());
		~DXWindow();

		bool Init();
		void Shutdown();
		void Update();

		inline bool ShouldClose() const
		{
			return m_bShouldClose;
		}

	private:

		// When something happens in the window it tells us which window it occurred by giving us:
		// A window handle ( wnd ) where the message occurred on
		// A code on what happened ( msg ) 
		// Params depending on what code was sent. 
		static LRESULT CALLBACK OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

		ATOM m_wndClass = 0;
		HINSTANCE   m_hInstance;
		HWND		m_window = nullptr;
		bool		m_bShouldClose = false;

	////singleton 
	//public:
	//	DXWindow(const DXWindow&) = delete;
	//	DXWindow& operator=(const DXWindow&) = delete;

	//	inline static DXWindow& Get()
	//	{
	//		static DXWindow instance;
	//		return instance;
	//	}
	//private:
	//	DXWindow() = default;
	};
}
#endif // !DXWINDOW_H



