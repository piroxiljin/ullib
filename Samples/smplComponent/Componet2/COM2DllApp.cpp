///\file ULCOMD2llApp.cpp
///\brief cpp файл класса динамической библиотеки COM-сервера(21.01.2007)
#include "ULLib.h"
#include "ULLibLink.h"
#include "ULClassFactory.h"
#include "..\\IFaces.h"
#include <assert.h>
#include "Component2.h"

UL_DECLARE_DLLMAIN

class CCOM2DllApp:
	public ULApps::CULCOMDllApp
{
public:
	///\brief Конструктор
	CCOM2DllApp():
		ULApps::CULCOMDllApp()
	{
	};
	virtual HRESULT OnRegisterServer()
	{
		return m_RegServ.RegisterServer(m_hInstance, 
			CLSIDComponent2,
			_T("ULCOM2, Probe"),
			_T("ULCOM2.Probe"),
			_T("ULCOM2.Probe.1"));
	}
	virtual HRESULT OnUnregisterServer()
	{
		return m_RegServ.UnregisterServer(CLSIDComponent2,
			_T("ULCOM2.Probe"),
			_T("ULCOM2.Probe.1"));
	}
	virtual HRESULT OnGetClassObject(const CLSID& clsid,
			const IID& iid,
			void** ppvObject)
	{
		return GetClassObjectFromClassFactory<ULCOMs::CULClassFactory<CComponent2,ULCOMs::ULAgregation::CULAgregateNone<CComponent2>>>
			(CLSIDComponent2,clsid,iid,ppvObject);
	};
};


CCOM2DllApp app;

