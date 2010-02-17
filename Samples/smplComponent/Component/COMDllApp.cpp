///\file ULCOMDllApp.cpp
///\brief cpp файл класса динамической библиотеки COM-сервера(05.01.2007)
#include "..\..\..\ULLib\Include\ULLib.h"
#include "..\..\..\ULLib\Include\ULClassFactory.h"
#include "..\\IFaces.h"
#include <assert.h>
#include "ULComponent.h"

#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\..\\ULLib\\Lib\\uULLibd.lib")
#else
	#pragma comment(lib,"..\\..\\..\\ULLib\\Lib\\uULLib.lib")
#endif

UL_DECLARE_DLLMAIN();

class CCOMDllApp:
	public ULApps::CULCOMDllApp
{
public:
	///\brief Конструктор
	CCOMDllApp():
		ULApps::CULCOMDllApp()
	{
	};
	virtual HRESULT OnRegisterServer()
	{
		return m_RegServ.RegisterServer(m_hInstance, 
			CLSIDComponent0,
			_T("ULCOM, Probe"),
			_T("ULCOM.Probe"),
			_T("ULCOM.Probe.1"));
	}
	virtual HRESULT OnUnregisterServer()
	{
		return m_RegServ.UnregisterServer(CLSIDComponent0,
			_T("ULCOM.Probe"),
			_T("ULCOM.Probe.1"));
	}
	virtual HRESULT OnGetClassObject(const CLSID& clsid,
			const IID& iid,
			void** ppvObject)
	{
		return GetClassObjectFromClassFactory<ULCOMs::CULClassFactory<CULComponent>>
			(CLSIDComponent0,clsid,iid,ppvObject);
	};
};


CCOMDllApp app;

