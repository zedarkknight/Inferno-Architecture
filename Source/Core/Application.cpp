#include "stdafx.h"
#include "Application.h"
#include "RendererWindows/D3D12/Debug/D3D12DebugLayer.h"

namespace AppCore
{
	static Application* s_Application = nullptr;

	Application::Application(const AppSpecs& specs)
		: m_AppSpecs(specs)
	{
		s_Application = this;

		InitD3D12DebugLayer();
		m_DXWindow = std::make_shared<DXWindow>(specs.windowSpec);
		if (D3D12Context::Get().Init() && m_DXWindow->Init())
		{
			//TODO: Error handle. 
		}

		if (m_AppSpecs.windowSpec.Title.empty())
			m_AppSpecs.windowSpec.Title = m_AppSpecs.name;
	}

	Application::~Application()
	{
		s_Application = nullptr;
	}

	void Application::Run()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			if (m_DXWindow->ShouldClose())
			{
				Stop();
				break;
			}
				
			//Update
			m_DXWindow->Update();
			auto* cmdList = D3D12Context::Get().InitcommandList();

			//Render
			D3D12Context::Get().ExecCommandList();
		}
		m_DXWindow->Shutdown();
		D3D12Context::Get().Shutdown();
	}

	void Application::Stop()
	{
		m_IsRunning = false;
	}

	bool Application::InitD3D12DebugLayer()
	{
		return D3D12DebugLayer::Get().Init();
	}

}
