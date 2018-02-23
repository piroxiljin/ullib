// smplULFrameWnd.cpp : Defines the entry point for the application.
//
#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLibd.lib")
#else
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLib.lib")
#endif

#include "..\..\ULLib\Include\ULLib.h"

#include "MainFrame.h"
//#include "resource.h"
class CApp:public ULApps::CULApp
{
public:
	HACCEL m_hAccelTable;

	CApp()
	{
		LOGFILE_ADD(_T("CApp"));
	}
	~CApp()
	{
#ifdef _DEBUG
		delete m_pMainWnd;
		m_pMainWnd=NULL;
#endif
		LOGFILE_SAVE(_T("CApp"));
	}
	virtual int InitInstance()
	{		
		CMainFrame* m_pMainFrame=new CMainFrame;
		m_pMainWnd=m_pMainFrame;
		m_pMainFrame->Create(_T("MyFrameWnd"),/*IDC_SMPLULFRAMEWND*/0,/*IDI_ICON_LOGO*/0,/*IDI_ICON_LOGO*/0,COLOR_GRAYTEXT);
        if(*m_pMainFrame==NULL)
			return FALSE;
//		m_hAccelTable = LoadAccelerators(m_hInstance, (LPCTSTR)IDR_ACCELERATOR1);
        ShowWindow(*m_pMainFrame, m_nCmdShow);
		UpdateWindow(*m_pMainFrame);
		return TRUE;		
	}

/*	virtual int Run(MSG* msg)
	{
		return !TranslateAccelerator(msg->hwnd, m_hAccelTable, msg);
	}
	*/
};
CApp app;
