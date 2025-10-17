#include "stdafx.h"
#include "D3D12Context.h"

bool AppCore::D3D12Context::Init()
{
	if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_device))))
	{
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	if (FAILED(m_device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_cmdQueue))))
	{
		return false;
	}

	if (FAILED(m_device->CreateFence(m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
	{
		return false;
	}

	m_fenceEvent = CreateEvent(nullptr, false, false, nullptr);
	if (!m_fenceEvent)
	{
		return false;
	}

	if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator))))
	{
		return false;
	}

	if (FAILED(m_device->CreateCommandList1(0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_cmdList))))
	{
		return false;
	}
	return true;
}

void AppCore::D3D12Context::Shutdown()
{
	m_cmdList.Release();
	m_cmdAllocator.Release();

	if (m_fenceEvent)
		CloseHandle(m_fenceEvent);

	m_fence.Release();
	m_cmdQueue.Release();
	m_device.Release();
}

void AppCore::D3D12Context::SignalAndWait()
{
	m_cmdQueue->Signal(m_fence, ++m_fenceValue);
	if (SUCCEEDED(m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent)))
	{
		// TODO: find way to not rely on waiting for an object. We are currently making this a synchronous program when it could be async. 
		if (WaitForSingleObject(m_fenceEvent, 20000) != WAIT_OBJECT_0)
		{
			std::exit(-1);
		}
	}
	else
	{
		// TODO: error out smoothly
		std::exit(-1);
	}
}

ID3D12GraphicsCommandList10* AppCore::D3D12Context::InitcommandList()
{
	m_cmdAllocator->Reset();
	m_cmdList->Reset(m_cmdAllocator, nullptr);
	return m_cmdList;
}

void AppCore::D3D12Context::ExecCommandList()
{
	if (SUCCEEDED(m_cmdList->Close()))
	{
		ID3D12CommandList* cmdList[] = { m_cmdList };
		m_cmdQueue->ExecuteCommandLists(1, cmdList);
		SignalAndWait();
	}
}
