#pragma once

#include "..\..\..\ULLib\Include\ULFrames.h"
#include "..\..\..\ULLib\Include\ULBars.h"



class CULCFrameWnd :
  public ULWnds::ULFrames::CULFrameWnd
{
public:
//========================================
	ULWnds::ULBars::CULToolBar m_ToolBar;
	ULWnds::ULBars::CULRebar m_ReBarTop;
	ULWnds::ULBars::CULStatusBar m_StatusBar;
	HWND m_hwndCombo;

	CULCFrameWnd(void);
	~CULCFrameWnd(void);
///////////////WM_...///////////////////////////
	virtual LRESULT OnCreate(WPARAM /*wParam*/,LPARAM /*lParam*/);
	virtual LRESULT OnSize(WPARAM wParam,LPARAM lParam);
///////////////WM_COMMAND///////////////////////////
	virtual void OnMenuNew(WORD id,HWND hControl);
	virtual void OnMenuExit(WORD id,HWND hControl);
	virtual void OnMenuAbout(WORD id,HWND hControl);
};
