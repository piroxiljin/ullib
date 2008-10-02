#include ".\finishpage.h"
#include "..\..\ULLib\Include\ULGDI.h"

CFinishPage::CFinishPage(void):ULWnds::ULDlgs::CULPropPage()
{
	MessageMap.AddMessage<CFinishPage>(WM_INITDIALOG,&CFinishPage::OnInitDialog);
}

CFinishPage::~CFinishPage(void)
{
}

LRESULT CFinishPage::OnInitDialog(WPARAM,LPARAM)
{
	ULGDI::ULDC::CULClientDC dc(*this);
	int nHeight = -MulDiv(20, dc.GetDeviceCaps(LOGPIXELSY), 96);
	ULGDI::ULGObjs::CULFont font;
	font.CreateFont(nHeight,0,0,0,FW_BOLD,FALSE,
		FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Vernanda"));
	::SendMessage(GetDlgItem(IDC_STATIC_END),WM_SETFONT,WPARAM((HFONT)font),TRUE);
	font.Detach();
	return FALSE;
}

LRESULT CFinishPage::OnSetActive(DWORD dwFlags)
{
	return CULPropPage::OnSetActive(PSWIZB_FINISH);
};

LRESULT CFinishPage::OnWizFinish(BOOL bFinish)
{
	return CULPropPage::OnWizFinish(0);
}
