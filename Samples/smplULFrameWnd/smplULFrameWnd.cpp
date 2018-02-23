// smplULFrameWnd.cpp : Defines the entry point for the application.
//

#include <ULStates.h>
#include <ULApp.h>
#include <ULOther.h>

#include "smplULFrameWnd.h"
#include ".\ulcframewnd\ulcframewnd.h"

class CULCApp:public ULApps::CULApp
{
public:
	HACCEL m_hAccelTable;

	CULCApp()
	{
		LOGFILE_ADD(_T("CULCApp"));
	}
	~CULCApp()
	{
#ifdef _DEBUG
		delete m_pMainWnd;m_pMainWnd=NULL;
#endif
		LOGFILE_SAVE(_T("CULCApp"));
	}
	virtual int InitInstance()
	{
		CULCFrameWnd* m_pFrameWnd=new CULCFrameWnd;
		this->m_pMainWnd=m_pFrameWnd;
		m_pFrameWnd->Create(_T("MyFrameWnd"),IDC_SMPLULFRAMEWND,IDI_ICON_LOGO,IDI_ICON_LOGO,COLOR_GRAYTEXT);
        if(*m_pFrameWnd==NULL)
			return FALSE;
		m_hAccelTable = LoadAccelerators(m_hInstance, (LPCTSTR)IDR_ACCELERATOR1);
        m_pFrameWnd->ShowWindow(m_nCmdShow);
		m_pFrameWnd->UpdateWindow();
		return TRUE;		
	}

	virtual int Run(MSG* msg)
	{
		return !TranslateAccelerator(msg->hwnd, m_hAccelTable, msg);
	}
};
CULCApp app;
