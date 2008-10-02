#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLibd.lib")
#else
	#pragma comment(lib,"..\\..\\ULLib\\Lib\\uULLib.lib")
#endif

#include "..\..\ULLib\Include\ULStates.h"
#include "..\..\ULLib\Include\ULApp.h"
#include "..\..\ULLib\Include\ULDlgs.h"
/////////////////////////////////////////////////////
#include "IntroPage.h"
#include "WorkPage.h"
#include "FinishPage.h"
#include "resource.h"
////////////////////////////////////////////////////
class CPropShPgApp:public ULApps::CULApp
{
public:
	CPropShPgApp():ULApps::CULApp(){LOGFILE_ADD(_T("CPropShPgApp"))};
	~CPropShPgApp()
	{
		LOGFILE_SAVE(_T("CPropShPgApp"))
	};
	virtual BOOL InitInstance()
	{
		ULWnds::ULDlgs::CULPropSheet* m_pPropSheet=new ULWnds::ULDlgs::CULPropSheet;
		CIntroPage m_IntroPropPage;
		CWorkPage m_WorkPropPage;
		CFinishPage m_FinishPropPage;
		m_pPropSheet->AddPage(m_IntroPropPage.Create(IDD_PROPPAGE_INTRO));
		m_pPropSheet->AddPage(m_WorkPropPage.Create(IDD_PROPPAGE_WORK,
			_T("Worka"),_T("Кароче поехали")));
		m_pPropSheet->AddPage(m_FinishPropPage.Create(IDD_PROPPAGE_FINISH));
		
		m_pPropSheet->Create(NULL,_T("Бла-Бла-Бла"),
			IDB_BITMAP_BANNER,IDB_BITMAP_WATERMARK,	ULWnds::ULDlgs::CULPropSheet::wfWizard97|
			ULWnds::ULDlgs::CULPropSheet::wfWizardContextHelp);
		m_pMainWnd=m_pPropSheet;
		return (m_pMainWnd->m_hWnd!=NULL);
	}
};
CPropShPgApp g_app;
