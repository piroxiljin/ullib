#pragma once
#include "..\..\ULLib\Include\ULFrames.h"
#include ".\mdichild.h"
#include "resource.h"
#include "..\..\ULLib\Include\ULControls.h"
#include "..\..\ULLib\Include\ULWndCtrls.h"

#include "..\..\ULLib\Include\ULRebarCtrl.h"



class CMDIClientWnd: public ULWnds::ULFrames::CULMDIClientWnd
{
public:
	CMDIClientWnd():CULMDIClientWnd()
	{
		MessageMap.AddMessage<CMDIClientWnd>(WM_PAINT,&CMDIClientWnd::OnPaint);
	};
	~CMDIClientWnd(){};
	virtual LRESULT OnPaint(WPARAM,LPARAM)
	{
		ULGDI::ULDC::CULPaintDC dc(*this);
			
		TCHAR szText[]=_T("–есую на клиенте");
		dc.TextOut(10,10,szText,(int)_tcslen(szText));
		dc.Rectangle(50,50,100,100);
		return FALSE;
	}
};

class CMDIFrame :
	public ULWnds::ULFrames::CULMDIFrameWnd
{
protected:
	ULWnds::ULWndCtrls::CULStatusBarCtrl m_StatusBarCtrl;
	ULWnds::ULWndCtrls::CULToolBarCtrl m_ToolBarCtrl;

	CMDIClientWnd* m_pMDIClient;



	ULWnds::ULWndCtrls::CULRebarCtrl m_RebarCtrl;
	ULWnds::ULBars::CULToolBar m_ToolBar;
	ULWnds::ULBars::CULToolBar m_ToolBar2;

public:
	CMDIFrame(void);
	~CMDIFrame(void);
//сообщени€==================================
	virtual LRESULT OnCreate(WPARAM,LPARAM);
	virtual LRESULT OnEraseBkGnd(WPARAM,LPARAM);
//сообщени€ от контролов=====================
	virtual void OnFileNew(WORD wID,HWND hControl);
};