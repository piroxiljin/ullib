#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLibd.lib")
#else
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLib.lib")
#endif


#include "..\..\ULLib\Include\ULStates.h"
#include "..\..\ULLib\Include\ULApp.h"
#include "..\..\ULLib\Include\ULWnd.h"
#include "..\..\ULLib\Include\ULMDIFrameWnd.h"
#include "..\..\ULLib\Include\ULMDIChildWnd.h"
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
		delete m_pMainWnd;
		m_pMainWnd=NULL;
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
