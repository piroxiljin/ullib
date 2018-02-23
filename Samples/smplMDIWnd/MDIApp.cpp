#include <ULStates.h>
#include <ULApp.h>
#include <ULWnd.h>
#include <ULMDIFrameWnd.h>
#include <ULMDIChildWnd.h>
/////////////////////////////////////////////////////
#include ".\mdichild.h"
#include ".\mdiframe.h"


/////////////////////////////////////////////////////
class CMDIApp:public ULApps::CULApp
{
public:
	CMDIApp():CULApp(){LOGFILE_ADD(_T("CMDIApp"))};
	~CMDIApp()
	{
#ifdef _DEBUG
		delete m_pMainWnd;m_pMainWnd=NULL;
#endif 
		LOGFILE_SAVE(_T("CMDIApp"))
	};
	
	virtual BOOL InitInstance()
	{
		CMDIFrame*m_ULMDIFrameWnd=new CMDIFrame;
		m_pMainWnd=m_ULMDIFrameWnd;
		m_ULMDIFrameWnd->Create(_T("MDI exampla"),IDR_MENU_MAIN,IDI_ICON_MAIN,IDI_ICON_MAIN,
			COLOR_WINDOW-1,1);
		m_ULMDIFrameWnd->ShowWindow(m_nCmdShow);
		m_ULMDIFrameWnd->UpdateWindow();
		return (*m_ULMDIFrameWnd!=NULL);
	}
};
CMDIApp g_app;
