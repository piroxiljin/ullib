#include ".\intropage.h"

CIntroPage::CIntroPage(void):ULWnds::ULDlgs::CULPropPage()
{
	MessageMap.AddMessage<CIntroPage>(WM_INITDIALOG,&CIntroPage::OnInitDialog);
}

CIntroPage::~CIntroPage(void)
{
}

LRESULT CIntroPage::OnInitDialog(WPARAM,LPARAM)
{
	ULGDI::ULDC::CULClientDC dc(*this);
	int nHeight = -MulDiv(20, dc.GetDeviceCaps(LOGPIXELSY), 96);
	ULGDI::ULGObjs::CULFont font;
	font.CreateFont(nHeight,0,0,0,FW_BOLD,FALSE,
		FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Vernanda"));
	::SendMessage(GetDlgItem(IDC_STATIC_HEADER),WM_SETFONT,WPARAM((HFONT)font),TRUE);
	font.Detach();
	return FALSE;
}

LRESULT CIntroPage::OnSetActive(DWORD dwFlags)
{
	return CULPropPage::OnSetActive(PSWIZB_NEXT);
};

