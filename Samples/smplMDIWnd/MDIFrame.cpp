#include ".\mdiframe.h"

#include <ULFrames.h>
#include <ULGDI.h>




CMDIFrame::CMDIFrame(void):CULMDIFrameWnd()
{
	MessageMap.AddCommand<CMDIFrame>(ID_NEW,&CMDIFrame::OnFileNew);
//	MessageMap.AddMessage<CMDIFrame>(WM_ENTERSIZEMOVE,&CMDIFrame::OnEnterSizeMove);
};

LRESULT CMDIFrame::OnEraseBkGnd(WPARAM,LPARAM)
{
	return TRUE;
}

CMDIFrame::~CMDIFrame(void)
{
};

LRESULT CMDIFrame::OnCreate(WPARAM,LPARAM lParam)
{
	CULMDIFrameWnd::OnCreate(0,lParam);

	m_pMDIClient=new CMDIClientWnd;
	m_pMDIClient->Create(*this,m_idSubMenu,m_idFirstChild,m_dwClientStyle,m_dwClientStyleEx);
	delete ReplaceMDIClient(m_pMDIClient);

	RECT rcMainWndClient;
	GetClientRect(&rcMainWndClient);
	m_StatusBarCtrl.CreateStatusBar(*this,ID_STATUSBAR,TRUE);
	m_StatusBarCtrl.GetStatusBar().AddPart(rcMainWndClient.right,_T("Просто панель типелла"));
	m_StatusBarCtrl.GetStatusBar().SetText(0,_T("Просто панель"));	
/*
	m_ToolBarCtrl.CreateToolBarCtrl(*this,ID_TOOLBAR,rcMainWndClient.left+50,rcMainWndClient.top+50,
		24,24,24,24,
		ULWnds::ULWndCtrls::CULToolBarCtrl::dsAllowDockTop,TRUE,WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|
		TBSTYLE_AUTOSIZE|CCS_NODIVIDER|TBSTYLE_FLAT,
		ULWnds::ULWndCtrls::CULToolBarCtrl::dsDrawGripperDocked|ULWnds::ULWndCtrls::CULToolBarCtrl::dsDrawGripperFloating|
		ULWnds::ULWndCtrls::CULToolBarCtrl::dsAllowDockAll);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_NEW,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("New"),NULL,STD_FILENEW,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(101,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("Open"),NULL,STD_FILEOPEN,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(102,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("Save"),NULL,STD_FILESAVE,IDB_STD_LARGE_COLOR);
*/
//	m_WndCtrlList.AddWndCtrl(&m_StatusBarCtrl);
//	m_WndCtrlList.AddWndCtrl(&m_ToolBarCtrl);

//=================
	m_RebarCtrl.CreateRebarCtrl(*this,0,0,ULWnds::ULWndCtrls::CULToolBarCtrl::dsAllowDockTop);

  m_ToolBar.Create(*this,
		ID_TOOLBAR,24, 24+15, 24, 24,ULWnds::ULBars::CULToolBar::afNon|ULWnds::ULBars::CULToolBar::afTop,
    WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|TBSTYLE_TOOLTIPS|CCS_NODIVIDER|
		TBSTYLE_FLAT,TBSTYLE_EX_DRAWDDARROWS);

  if(m_ToolBar.m_hWnd!=NULL)
		m_ToolBar.AddButton(0,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("New"),NULL,STD_FILENEW,IDB_STD_LARGE_COLOR);

  m_ToolBar2.Create(*this,
		ID_TOOLBAR,24, 24+15, 24, 24,ULWnds::ULBars::CULToolBar::afNon|ULWnds::ULBars::CULToolBar::afTop,
    WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|TBSTYLE_TOOLTIPS|CCS_NODIVIDER,TBSTYLE_EX_DRAWDDARROWS);

  if(m_ToolBar2.m_hWnd!=NULL)
		m_ToolBar2.AddButton(0,TBSTATE_ENABLED, BTNS_BUTTON ,_T("Open"),NULL,STD_FILEOPEN,IDB_STD_LARGE_COLOR);

	assert(m_RebarCtrl.GetRebar().InsertBand(0,m_ToolBar,_T("qwerty"),NULL));
	assert(m_RebarCtrl.GetRebar().InsertBand(1,m_ToolBar2,_T("qwerty2"),NULL));


	m_WndCtrlList.AddWndCtrl(&m_RebarCtrl);


	SendMessage(WM_COMMAND,ID_NEW);

	return FALSE;
}

void CMDIFrame::OnFileNew(WORD /*wID*/,HWND /*hControl*/)
{
	CMDIChild* pMDIChild=new CMDIChild;
	TCHAR szCapture[MAX_PATH];
	_itot_s((int)m_pMDIClientWnd->GetChildCount()+1,szCapture,MAX_PATH,10);
	pMDIChild->Create(szCapture,80,80,300,300,IDI_ICON_CHILD1,*m_pMDIClientWnd,COLOR_APPWORKSPACE);
	m_pMDIClientWnd->AddChild(pMDIChild);
//	EnableMenuItem((HMENU)::GetMenu(*this),wID,MF_DISABLED|MF_GRAYED);
}
