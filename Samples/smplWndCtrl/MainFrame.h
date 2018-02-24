#pragma once
#include <ULFrames.h>
#include <ULWndCtrls.h>
#include "ToolBarCtrlC.h"
class CMainFrame :
  public ULWnds::ULFrames::CULFrameWnd
{
public:
	CMainFrame(void);
	~CMainFrame(void);
//���������==================================
	virtual LRESULT OnCreate(WPARAM,LPARAM);
	virtual LRESULT OnCWMClose(WPARAM,LPARAM);
//��������� �� ���������=====================
	virtual void OnMenuFileExit(WORD id,HWND hControl);
	virtual void OnMenuViewToolBar(WORD id,HWND hControl);
	virtual void OnMenuViewStatusBar(WORD id,HWND hControl);
//�����======================================
	CToolBarCtrlC m_ToolBarCtrl;
  ULWnds::ULWndCtrls::CULStatusBarCtrl m_StatusBarCtrl;
  ULWnds::ULWndCtrls::CULWndCtrlList m_WndCtrlList;
};
