#include ".\mdichild.h"
#include "..\..\ULLib\Include\ULApp.h"
#include "..\..\ULLib\Include\ULGDI.h"

CMDIChild::CMDIChild(void):ULWnds::ULFrames::CULMDIChildWnd()
{
	MessageMap.AddMessage<CMDIChild>(WM_PAINT,&CMDIChild::OnPaint);
}


CMDIChild::~CMDIChild(void)
{
}

LRESULT CMDIChild::OnPaint(WPARAM,LPARAM)
{
	ULGDI::ULDC::CULPaintDC dc(*this);
	
	TCHAR szText[]=_T("Ресую на чайлде");
	dc.TextOut(10,10,szText,(int)_tcslen(szText));
	dc.Rectangle(50,50,100,100);
	return FALSE;
};


