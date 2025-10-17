
#ifndef D3D12WINDOW_H
#define D3D12WINDOW_H

#include "Includes/WinIncludes.h"
#include "Includes/ComPointer.h"
#include <string>

namespace AppCore
{

	class D3D12Context
	{
	public:
		bool Init();
		void Shutdown();

		void SignalAndWait();

		inline ComPointer<ID3D12Device10>& GetDevice()
		{
			return m_device;
		}

		inline ComPointer<ID3D12CommandQueue>& GetCmdQueue()
		{
			return m_cmdQueue;
		}

		ID3D12GraphicsCommandList10* InitcommandList();

		void ExecCommandList();
	private:
		ComPointer<ID3D12Device10>		m_device;
		ComPointer<ID3D12CommandQueue>	m_cmdQueue;

		ComPointer<ID3D12CommandAllocator> m_cmdAllocator;
		ComPointer<ID3D12GraphicsCommandList10> m_cmdList;

		ComPointer<ID3D12Fence1>		m_fence; 
		UINT64							m_fenceValue = 0;
		HANDLE							m_fenceEvent = nullptr;

	//Singleton Implementation 
	public:
		D3D12Context(const D3D12Context&) = delete;
		D3D12Context& operator=(const D3D12Context&) = delete;

		inline static D3D12Context& Get()
		{
			static D3D12Context instance;
			return instance;
		}
	private:
		D3D12Context() = default;

	};
}

#endif // !D3D12WINDOW_H