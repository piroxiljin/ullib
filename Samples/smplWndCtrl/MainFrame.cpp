#include "resource.h"
#include ".\mainframe.h"

CMainFrame::CMainFrame(void):ULWnds::ULFrames::CULFrameWnd()
{
	MessageMap.AddMessage<CMainFrame>(CToolBarCtrlC::CWM_CLOSE,&CMainFrame::OnCWMClose);
	MessageMap.AddCommand<CMainFrame>(ID_VIEW_TOOLBAR,&CMainFrame::OnMenuViewToolBar);
	MessageMap.AddCommand<CMainFrame>(ID_VIEW_STATUSBAR,&CMainFrame::OnMenuViewStatusBar);
	MessageMap.AddCommand<CMainFrame>(ID_FILE_EXIT,&CMainFrame::OnMenuFileExit);
}

CMainFrame::~CMainFrame(void)
{
}

LRESULT CMainFrame::OnCreate(WPARAM,LPARAM lParam)
{	
	CULFrameWnd::OnCreate(0,lParam);
	//=====================Создание статусбара======================
	m_StatusBarCtrl.CreateStatusBar(*this,ID_STATUSBAR);
	//=====================добавление скций в статусбар=============
	RECT rcStatusBarCtrl;
	m_StatusBarCtrl.GetClientRect(&rcStatusBarCtrl);
	m_StatusBarCtrl.GetStatusBar().AddPart(2*rcStatusBarCtrl.right/4,_T("Типа первая панеля"));
	m_StatusBarCtrl.GetStatusBar().SetText(0,_T("Первая панеля"));
	m_StatusBarCtrl.GetStatusBar().AddPart(rcStatusBarCtrl.right/4,_T("Типа вторая панеля"));
	m_StatusBarCtrl.GetStatusBar().SetText(1,_T("Вторая панеля"));
	m_StatusBarCtrl.GetStatusBar().AddPart(rcStatusBarCtrl.right/4,_T("Типа третья панеля"));
	m_StatusBarCtrl.GetStatusBar().SetText(2,_T("Третсья панеля"));
	//=====================Создание тулбара=========================
	RECT rcMainFrm;
	GetWindowRect(&rcMainFrm);
	m_ToolBarCtrl.CreateToolBarCtrl(*this,ID_TOOLBAR,rcMainFrm.left+50,rcMainFrm.top+50,
		24,24,24,24,
    ULWnds::ULWndCtrls::CULToolBarCtrl::dsAllowDockTop,TRUE,WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|
		TBSTYLE_AUTOSIZE|CCS_NODIVIDER|TBSTYLE_FLAT,
    ULWnds::ULWndCtrls::CULToolBarCtrl::dsDrawGripperDocked|ULWnds::ULWndCtrls::CULToolBarCtrl::dsDrawGripperFloating|
		ULWnds::ULWndCtrls::CULToolBarCtrl::dsAllowDockAll|TBSTYLE_EX_DRAWDDARROWS);
	m_ToolBarCtrl.ShowWindow(SW_HIDE);
	//===============добавление стандартных кнопок на тулбар=======
	m_ToolBarCtrl.GetToolBar().AddButton(ID_FILE_NEW,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа New"),STD_FILENEW,(UINT_PTR)IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_FILE_OPEN,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа Open"),STD_FILEOPEN,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_FILE_SAVE,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа Save"),STD_FILESAVE,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(0,0,BTNS_SEP,NULL,0);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_EDIT_CUT,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа Cut"),STD_CUT,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_EDIT_COPY,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа Copy"),STD_COPY,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(ID_EDIT_PASTE,TBSTATE_ENABLED,
		BTNS_BUTTON,_T("Типа Paste"),STD_PASTE,IDB_STD_LARGE_COLOR);
	m_ToolBarCtrl.GetToolBar().AddButton(1,0,BTNS_SEP,NULL,0);
	//===============добавление кнопки из ресурсов на тулбар=======
	HBITMAP hBitmap=(HBITMAP)::LoadImage(::GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDB_BITMAP_TB_HELP),IMAGE_BITMAP,0,0,
		0);
	m_ToolBarCtrl.GetToolBar().InsertButton(7,ID_HELP_ABOUT,TBSTATE_ENABLED,
		BTNS_BUTTON|BTNS_DROPDOWN,_T("Типа About"),0,hBitmap,0,IDR_MENU_MAIN);
    
	m_ToolBarCtrl.ShowWindow(SW_SHOW);
	//=====================Создание контейнера панелек=============
	m_WndCtrlList.Create(*this);
	//=====================Добавление панелек в контейнер==========
	m_WndCtrlList.AddWndCtrl(&m_StatusBarCtrl);
	m_WndCtrlList.AddWndCtrl(&m_ToolBarCtrl);
	m_ToolBarCtrl.ResizeAllWndCtrls();
	return FALSE;
};

LRESULT CMainFrame::OnCWMClose(WPARAM wParam,LPARAM)
{
	HWND hWnd=(HWND)wParam;
	if(hWnd==m_ToolBarCtrl)
	{
		m_ToolBarCtrl.ShowWindow(SW_HIDE);
		::CheckMenuItem(::GetMenu(*this),ID_VIEW_TOOLBAR,MF_UNCHECKED);
		return FALSE;
	}
	return TRUE;
}

void CMainFrame::OnMenuViewToolBar(WORD id,HWND hControl)
{
	UINT fChecked=GetMenuState(::GetMenu(*this),id,MF_BYCOMMAND);
	fChecked=(fChecked==MF_UNCHECKED)?MF_CHECKED:MF_UNCHECKED;
	::CheckMenuItem(::GetMenu(*this),id,fChecked);
	if(!fChecked)
		m_ToolBarCtrl.ShowWindow(SW_HIDE);
	else
		m_ToolBarCtrl.ShowWindow(SW_SHOW);
};

void CMainFrame::OnMenuViewStatusBar(WORD id,HWND hControl)
{
	UINT fChecked=GetMenuState(::GetMenu(*this),id,MF_BYCOMMAND);
	fChecked=(fChecked==MF_UNCHECKED)?MF_CHECKED:MF_UNCHECKED;
	::CheckMenuItem(::GetMenu(*this),id,fChecked);
	if(!fChecked)
		m_StatusBarCtrl.ShowWindow(SW_HIDE);
	else
		m_StatusBarCtrl.ShowWindow(SW_SHOW);	
};

void CMainFrame::OnMenuFileExit(WORD id,HWND hControl)
{
	DestroyWindow();
}