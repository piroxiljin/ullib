
#include <ULApp.h>
#include <ULStates.h>

#include "smplWndCtrl.h"
#include "mainframe.h"

class CCWApp:public ULApps::CULApp
{
public:
	CCWApp():CULApp()
	{
		LOGFILE_ADD(_T("CCWApp"));
	}
	~CCWApp()
	{
#ifdef _DEBUG
		delete m_pMainWnd;m_pMainWnd=NULL;
#endif
		LOGFILE_SAVE(_T("CCWApp"));
	}
	virtual BOOL InitInstance()
	{
		CMainFrame* m_pMainFrame=new CMainFrame;
		m_pMainFrame->Create(_T("Пример CtrlWnd"),IDR_MENU_MAIN,
			0,0,COLOR_WINDOWFRAME);
		m_pMainFrame->ShowWindow(m_nCmdShow);
		m_pMainFrame->UpdateWindow();
		m_pMainWnd=m_pMainFrame;
		return (*m_pMainFrame!=NULL);
	}
};
CCWApp g_app;
