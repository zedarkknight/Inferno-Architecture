#include "stdafx.h"
#include "DXWindow.h"

namespace AppCore
{

	DXWindow::DXWindow(const WindowSpecData& specData /*= WindowSpecData()*/)
	{

	}

	DXWindow::~DXWindow()
	{
		Shutdown();
	}

	bool DXWindow::Init()
	{
		WNDCLASSEXW wcex{};
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_OWNDC;
		wcex.lpfnWndProc = &DXWindow::OnWindowMessage;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(DXWindow*);
		wcex.hInstance = GetModuleHandle(nullptr);
		wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
		wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = L"D3D12ExWndCls";
		wcex.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

		m_wndClass = RegisterClassExW(&wcex);

		if (!m_wndClass)
			return false;

		m_hInstance = wcex.hInstance;

		// Window 
		m_window = CreateWindowExW(
			WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW,
			(LPCWSTR)m_wndClass,
			L"D3D12 Window",
			WS_EX_OVERLAPPEDWINDOW | WS_VISIBLE,
			100,
			100,
			1920,
			1080,
			nullptr,
			nullptr,
			m_hInstance,
			static_cast<LPVOID>(this)
		);
		return m_window != nullptr;
	}

	void DXWindow::Shutdown()
	{
		if (m_window)
		{
			DestroyWindow(m_window);
		}
		if (m_wndClass)
		{
			UnregisterClassW((LPCWSTR)m_wndClass, GetModuleHandleW(nullptr));
		}
	}

	void DXWindow::Update()
	{
		MSG msg;
		while (PeekMessageW(&msg, m_window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	LRESULT CALLBACK DXWindow::OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_NCCREATE:
		{
			CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
			LPVOID pThis = pCS->lpCreateParams;
			SetWindowLongPtrW(wnd, 0, reinterpret_cast<LONG_PTR>(pThis));
			break;
		}
		case WM_CLOSE:
		{
			DXWindow* pWnd = reinterpret_cast<DXWindow*>(GetWindowLongPtrW(wnd, 0));
			pWnd->m_bShouldClose = true;
			return 0;
		}
		default:
			break;
		}
		// Default behavior for windows. 
		return DefWindowProc(wnd, msg, wParam, lParam);
	}
}

