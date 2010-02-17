#pragma once
#include "..\..\ULLib\Include\ULLib.h"
#include "..\..\ULLib\Include\ULGDI.h"

class CToolBarCtrlC :
  public ULWnds::ULWndCtrls::CULToolBarCtrl
{
public:
  CToolBarCtrlC(void):ULWnds::ULWndCtrls::CULToolBarCtrl()
	{
	}
	~CToolBarCtrlC(void)
	{
	}

	virtual LRESULT OnEraseBkGnd(WPARAM wParam,LPARAM)
	{
    HDC hdc=(HDC)wParam;
    ULGDI::ULDC::CULDC dc(hdc);
		RECT rcClient;
		GetClientRect(&rcClient);

		dc.SetBkMode(ULGDI::ULDC::CULDC::bmTRANSPARENT);
		
		int nHeight=-MulDiv(22, dc.GetDeviceCaps(LOGPIXELSY), 96);
		int nOrient=((m_fDocked)&&((m_dwDockedState&dsAllowDockLeft)||(m_dwDockedState&dsAllowDockRight)))?2700:0;
		ULGDI::ULGObjs::CULFont font;
		font.CreateFont(nHeight,0,nOrient,0,FW_NORMAL,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Arial cyr"));
		font.m_hFont=(HFONT)dc.SelectObject(font);
		ULGDI::ULGObjs::CULBrush brush;
		brush.CreateSolidBrush(0xff0000);
		brush.m_hBrush=(HBRUSH)dc.SelectObject(brush);
		ULGDI::ULGObjs::CULPen pen;
		pen.CreatePen(PS_SOLID,1,0x0000ff);
		pen.m_hPen=(HPEN)dc.SelectObject(pen);
		dc.SetTextColor(0x00ffff);

		dc.Rectangle(0,0,rcClient.right,rcClient.bottom);
		TCHAR text[]=_T("Здесь может быть ваша реклама");
		if((m_fDocked)&&((m_dwDockedState&dsAllowDockLeft)||(m_dwDockedState&dsAllowDockRight)))
			dc.TextOut(35,7,text,sizeof(text)/sizeof(TCHAR)-1);
		else 
			dc.TextOut(7,0,text,sizeof(text)/sizeof(TCHAR)-1);
		DrawGripper(dc, rcClient);

		//освобождение ресурсов
		font.m_hFont=(HFONT)dc.SelectObject(font);
		brush.m_hBrush=(HBRUSH)dc.SelectObject(brush);
		pen.m_hPen=(HPEN)dc.SelectObject(pen);
		dc.Detach();
		return TRUE;
	}
};
