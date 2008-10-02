#include "Component2.h"
#include "..\..\..\ULLib\Include\ULCOMDllApp.h"

CComponent2::CComponent2(void):m_nRef(1)
{
	static_cast<ULApps::CULCOMDllApp*>(ULApps::CULCOMDllApp::GetULDllApp())->ComponentLock();
}

CComponent2::~CComponent2(void)
{
	static_cast<ULApps::CULCOMDllApp*>(ULApps::CULCOMDllApp::GetULDllApp())->ComponentUnlock();
}

HRESULT __stdcall CComponent2::QueryInterface(const IID& iid, void** ppvObject)
{
	if (iid == IID_IUnknown) 
		*ppvObject = static_cast<IZ*>(this); 
	else
		if (iid == IID_IX) 
			*ppvObject = static_cast<IZ*>(this); 
		else 
		{ 
			*ppvObject = NULL; 
			return E_NOINTERFACE; 
		} 
	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef(); 
	return S_OK; 
};

ULONG __stdcall CComponent2::AddRef()
{
	return InterlockedIncrement(&m_nRef);
}; 
ULONG __stdcall CComponent2::Release()
{
	return InterlockedDecrement(&m_nRef);
}; 
