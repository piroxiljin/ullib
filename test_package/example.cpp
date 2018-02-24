
#include <ULApp.h>

#include <ULFrames.h>
#include <ULLib.h>

class CMainFrame :
  public ULWnds::ULFrames::CULFrameWnd
{
public:
	CMainFrame(void);
	~CMainFrame(void);
//сообщения==================================
	virtual LRESULT OnCreate(WPARAM,LPARAM);
};

CMainFrame::CMainFrame(void):ULWnds::ULFrames::CULFrameWnd()
{
}

CMainFrame::~CMainFrame(void)
{
}

LRESULT CMainFrame::OnCreate(WPARAM,LPARAM lParam)
{	
	CULFrameWnd::OnCreate(0,lParam);

	return FALSE;
};


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
        return FALSE;
	}
};
CCWApp g_app;
