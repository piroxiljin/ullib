#include ".\workpage.h"

CWorkPage::CWorkPage(void):ULWnds::ULDlgs::CULPropPage(),
	m_bNext(FALSE)
{
	MessageMap.AddCommand<CWorkPage>(IDC_BUTTON_PUSHME,&CWorkPage::OnBtnPushMe);
}

CWorkPage::~CWorkPage(void)
{
}

void CWorkPage::OnBtnPushMe(WORD,HWND)
{
	ULWnds::ULDlgs::CULPropSheet PropSheet;
	PropSheet.AddPage(m_Page1.Create(IDD_PROPPAGE_PAGE1,_T("Page1"),NULL,
		::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON_MAIN))));
	PropSheet.AddPage(m_Page2.Create(IDD_PROPPAGE_PAGE2,_T("Page2"),NULL,
		::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON_MAIN))));
	assert(PropSheet.Create(*this,_T("Не визардмоде"),0)==IDOK);	
	m_bNext=TRUE;
}

LRESULT CWorkPage::OnWizNext(short Result)
{
	if(!m_bNext)
		return CULPropPage::OnWizNext(-1);
	else 
		return CULPropPage::OnWizNext(Result);
};

