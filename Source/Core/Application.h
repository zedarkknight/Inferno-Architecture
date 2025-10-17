#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <memory>
#include <string> 
#include "RendererWindows/D3D12/D3D12Context.h"
#include "RendererWindows/D3D12/DXWindow.h"
namespace AppCore
{
	struct AppSpecs
	{
		std::string name = "Application";
		WindowSpecData windowSpec;
	};

	class Application
	{
	public:
		Application(const AppSpecs& specs = AppSpecs());
		~Application();

		void Run();
		void Stop();

		static Application& Get();
		static float GetTime();
	private:
		AppSpecs m_AppSpecs;
		bool m_IsRunning = false;
		bool InitD3D12DebugLayer();

		std::shared_ptr<DXWindow> m_DXWindow; 
	};
}
#endif