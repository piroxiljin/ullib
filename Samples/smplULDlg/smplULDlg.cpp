// smplULDlg.cpp : Defines the entry point for the application.
//

#include <ULLib.h>

#include "smplULDlg.h"
#include ".\ULCDlg\ulCdlg.h"



class CULCApp:public ULApps::CULApp
{
public:
	CULCDlg* m_pMainDlg;
	CULCApp()
	{
		LOGFILE_ADD(_T("CULCApp"));
//		MEM_CHECK;
	};
	~CULCApp()
	{
#ifdef _DEBUG
		delete m_pMainWnd;m_pMainWnd=NULL;
#endif
//		MEM_VERIFY;
		LOGFILE_SAVE(_T("CULCApp"));
	};
	virtual int InitInstance()
	{
		m_pMainDlg=new CULCDlg;
		m_pMainDlg->CreateModal(IDD_DIALOG_MAIN,NULL);
/*		m_pMainDlg->Create(IDD_DIALOG_MAIN,NULL);
		m_pMainDlg->ShowWindow(SW_SHOW);
		m_pMainDlg->UpdateWindow();
		m_pMainWnd=m_pMainDlg;
		return TRUE;		*/
		return FALSE;		
	}
	virtual BOOL Run(MSG* /*pMsg*/)
	{
		return TRUE;
	}
};
CULCApp app;
