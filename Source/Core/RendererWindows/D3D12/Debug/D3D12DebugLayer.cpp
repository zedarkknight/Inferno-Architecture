#include "stdafx.h"
#include "D3D12DebugLayer.h"

bool D3D12DebugLayer::Init()
{
#ifdef _DEBUG
	// Init D3D12 Debug Layer
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&m_d3d12Debug))))
	{
		m_d3d12Debug->EnableDebugLayer();

		//Init DXGI Debug
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&m_dxdiDebug))))
		{
			m_dxdiDebug->EnableLeakTrackingForThread();
			return true;
		}
	}
#endif // !_DEBUG
	return false;
}

void D3D12DebugLayer::Shutdown()
{
#ifdef _DEBUG
	if (m_dxdiDebug)
	{
		OutputDebugString(L"DXGI Reports living device objects \n");
		m_dxdiDebug->ReportLiveObjects(
			DXGI_DEBUG_ALL,
			DXGI_DEBUG_RLO_FLAGS( DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)
		);
	}
	m_dxdiDebug.Release();
	m_d3d12Debug.Release();
#endif // !_DEBUG

}
