#include "ULComponent.h"
#include "ULCOMDllApp.h"

CULComponent::CULComponent(void):
	CUnknown(NULL),
	m_nRef(1)
{
	static_cast<ULApps::CULCOMDllApp*>(ULApps::CULCOMDllApp::GetULDllApp())->ComponentLock();
}

CULComponent::~CULComponent(void)
{
	static_cast<ULApps::CULCOMDllApp*>(ULApps::CULCOMDllApp::GetULDllApp())->ComponentUnlock();
}
/*
HRESULT __stdcall CULComponent::QueryInterface(const IID& iid, void** ppvObject)
{
	if (iid == IID_IUnknown) 
		*ppvObject = static_cast<IX*>(this); 
	else
		if (iid == IID_IX) 
			*ppvObject = static_cast<IX*>(this); 
		else 
			if (iid == IID_IY) 
				*ppvObject = static_cast<IY*>(this); 
			else 
			{ 
				*ppvObject = NULL; 
				return E_NOINTERFACE; 
			} 
	reinterpret_cast<IUnknown*>(*ppvObject)->AddRef(); 
	return S_OK; 
};

ULONG __stdcall CULComponent::AddRef()
{
	return InterlockedIncrement(&m_nRef);
}; 
ULONG __stdcall CULComponent::Release()
{
	return InterlockedDecrement(&m_nRef);
}; 
*/