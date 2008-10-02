///\file ULDllApp.cpp
///\brief cpp файл класса динамической библиотеки(03.01.2007)
#include "..\..\ULLib\Include\ULDllApp.h"
namespace ULApps
{
	HINSTANCE CULDllApp::m_hInstance=NULL;

	CULDllApp::CULDllApp(void)
	{
		
		m_pULDllApp=this;
	}

	CULDllApp::~CULDllApp(void)
	{
	};

	BOOL CULDllApp::ProcessAttach(HINSTANCE hInstance)
	{
		m_hInstance=hInstance;
		return TRUE;
	};

	BOOL CULDllApp::ProcessDetach()
	{
		return TRUE;
	};

	BOOL CULDllApp::ThreadAttach()
	{
		return TRUE;
	};

	BOOL CULDllApp::ThreadDetach()
	{
		return TRUE;
	};

	CULDllApp *CULDllApp::m_pULDllApp=NULL;

	CULDllApp* CULDllApp::GetULDllApp(void)
	{
		return m_pULDllApp;
	};

	BOOL CULDllApp::DllMain(HINSTANCE hinstDLL,
						DWORD fdwReason)
	{
		switch(fdwReason)
		{
		case DLL_PROCESS_ATTACH:
			return ProcessAttach(hinstDLL);
		case DLL_THREAD_ATTACH:
			return ThreadAttach();
		case DLL_THREAD_DETACH:
			return ThreadDetach();
		case DLL_PROCESS_DETACH:
			return ProcessDetach();
		default:
			return TRUE;
		}
	};
}
