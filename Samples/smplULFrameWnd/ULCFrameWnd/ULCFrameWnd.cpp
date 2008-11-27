#include ".\ulcframewnd.h"
#include "..\..\..\ULLib\Include\ULDlgs.h"
#include "..\..\..\ULLib\Include\ULMenu.h"
#include "..\resource.h"

#include "stdio.h"
#define ID_TB 1
#define ID_CB 2

CULCFrameWnd::CULCFrameWnd(void):ULWnds::ULFrames::CULFrameWnd()
{
	MessageMap.AddMessage<CULCFrameWnd>(WM_SIZE,&CULCFrameWnd::OnSize);
	MessageMap.AddCommand<CULCFrameWnd>(ID_MENU_NEW,&CULCFrameWnd::OnMenuNew);
	MessageMap.AddCommand<CULCFrameWnd>(IDC_BUTTON,&CULCFrameWnd::OnMenuNew);
	MessageMap.AddCommand<CULCFrameWnd>(IDM_EXIT,&CULCFrameWnd::OnMenuExit);
	MessageMap.AddCommand<CULCFrameWnd>(IDM_ABOUT,&CULCFrameWnd::OnMenuAbout);		
}

CULCFrameWnd::~CULCFrameWnd(void)
{
}


LRESULT CULCFrameWnd::OnCreate(WPARAM /*wParam*/,LPARAM /*lParam*/)
{

	RECT rcMainWndClient;
	GetClientRect(&rcMainWndClient);
	m_StatusBar.Create(*this,ID_STATUSBAR);
	m_StatusBar.AddPart(3*rcMainWndClient.right/4,_T("Первая панель"));
	m_StatusBar.SetText(0,_T("Первая панель типелла"));
	m_StatusBar.AddPart(1*rcMainWndClient.right/4-(22+16),_T("Вторая панель типелла"));
	m_StatusBar.SetText(1,_T("Вторая панель "));
	m_StatusBar.AddPart(22+16,_T("Третья панель типелла"));
	m_StatusBar.SetIcon(2,IDI_ICON_SB);
//	m_StatusBar.DeleteAll();


	assert(m_ReBarTop.Create(*this,0,ULWnds::ULBars::CULRebar::afTop));

	DWORD dwBaseUnits = GetDialogBaseUnits(); 
	m_hwndCombo = CreateWindow(_T("COMBOBOX"), NULL, 
		CBS_DROPDOWN | WS_CHILD | WS_VISIBLE|WS_BORDER, 
		(6 * LOWORD(dwBaseUnits)) / 4, 
		(3 * HIWORD(dwBaseUnits)) / 8, 
		(50 * LOWORD(dwBaseUnits)) / 4, 
		(250 * HIWORD(dwBaseUnits)) / 8, 
		*this, NULL, GetModuleHandle(NULL), NULL); 
	::SendMessage(m_hwndCombo,CB_ADDSTRING,NULL,LPARAM(_T("строка 1")));
	::SendMessage(m_hwndCombo,CB_ADDSTRING,NULL,LPARAM(_T("строка 2")));




  m_ToolBar.Create(*this,
		ID_TOOLBAR,24, 24+15, 24, 24,ULWnds::ULBars::CULToolBar::afNon|ULWnds::ULBars::CULToolBar::afTop,
    WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN| TBSTYLE_LIST| TBSTYLE_TOOLTIPS|CCS_ADJUSTABLE|CCS_NODIVIDER|
		TBSTYLE_FLAT,TBSTYLE_EX_DRAWDDARROWS);

  if(m_ToolBar.m_hWnd!=NULL)
	{
		m_ToolBar.AddButton(ID_MENU_NEW,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("New"),NULL,STD_FILENEW,IDB_STD_LARGE_COLOR);
		m_ToolBar.AddButton(ID_MENU_OPEN,TBSTATE_ENABLED, BTNS_BUTTON ,_T("Open"),NULL,STD_FILEOPEN,IDB_STD_LARGE_COLOR);
		m_ToolBar.AddButton(ID_MENU_SAVE,TBSTATE_ENABLED,BTNS_BUTTON,_T("Save"),NULL,STD_FILESAVE,IDB_STD_LARGE_COLOR);
		m_ToolBar.AddButton(0,TBSTATE_ENABLED,BTNS_SEP,NULL,NULL,0);
		m_ToolBar.AddButton(ID_MENU_DELETE,TBSTATE_ENABLED,BTNS_BUTTON,_T("Delete"),NULL,STD_DELETE,IDB_STD_LARGE_COLOR);
		m_ToolBar.AddButton(0,TBSTATE_ENABLED,BTNS_SEP,NULL,NULL,0);
		HBITMAP hBitmap=::LoadBitmap(::GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDB_BITMAP_CUSTOM));
		static TCHAR szStr[]=_T("ID_MENU_OTHER");
		m_ToolBar.AddButton(ID_MENU_OTHER,TBSTATE_ENABLED,BTNS_BUTTON,
			_T("Other1"),szStr,0,hBitmap);
//		::DeleteObject(hBitmap);

//пробуем вставить
		hBitmap=::LoadBitmap(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP_CUSTOM2));
		ULWnds::ULControls::CULMenu popupMenu;
		popupMenu.LoadMenu(ULOther::ULGetResourceHandle(),MAKEINTRESOURCE(IDC_SMPLULFRAMEWND));
		m_ToolBar.InsertButton(7,ID_MENU_OTHER2,TBSTATE_ENABLED, BTNS_DROPDOWN |BTNS_BUTTON ,
			_T("insert button"),NULL,0,hBitmap,popupMenu.GetSubMenu(1));
		::DeleteObject(hBitmap);
//		m_ToolBar.AutoSize();

//пробуем удалить
//		m_ToolBar.DeleteButton(2);
	}



	HBITMAP hBmp=::LoadBitmap(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP_BG));

	RECT rcTBWidth;
	m_ToolBar.GetItemRect(m_ToolBar.GetButtonCount()-1,&rcTBWidth);
	SIZE szToolBar={rcTBWidth.right,rcTBWidth.bottom};

//  BOOL fRet;

	RECT rect;
	::GetWindowRect(m_hwndCombo,&rect);

//	SIZE szCombo={rect.right-rect.left,rcTBWidth.bottom};

	assert(m_ReBarTop.InsertBand(0,m_hwndCombo,NULL,NULL));

	assert(m_ReBarTop.InsertBand(0,m_ToolBar,NULL,NULL));
/*
  m_ToolBar2.Create(*this,
		ID_TOOLBAR,24, 24+15, 24, 24,ULWnds::ULBars::CULToolBar::afNon|ULWnds::ULBars::CULToolBar::afTop,
    WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|TBSTYLE_TOOLTIPS|CCS_NODIVIDER,TBSTYLE_EX_DRAWDDARROWS);

  if(m_ToolBar2.m_hWnd!=NULL)
	{
		m_ToolBar2.AddButton(ID_MENU_NEW,TBSTATE_ENABLED,  BTNS_BUTTON ,_T("New"),NULL,STD_FILENEW,IDB_STD_LARGE_COLOR);
		m_ToolBar2.AddButton(ID_MENU_OPEN,TBSTATE_ENABLED, BTNS_BUTTON ,_T("Open"),NULL,STD_FILEOPEN,IDB_STD_LARGE_COLOR);
		m_ToolBar2.AddButton(ID_MENU_SAVE,TBSTATE_ENABLED,BTNS_BUTTON,_T("Save"),NULL,STD_FILESAVE,IDB_STD_LARGE_COLOR);
		m_ToolBar2.AddButton(0,TBSTATE_ENABLED,BTNS_SEP,NULL,NULL,0);
		m_ToolBar2.AddButton(ID_MENU_DELETE,TBSTATE_ENABLED,BTNS_BUTTON,_T("Delete"),NULL,STD_DELETE,IDB_STD_LARGE_COLOR);
		m_ToolBar2.AddButton(0,TBSTATE_ENABLED,BTNS_SEP,NULL,NULL,0);
		HBITMAP hBitmap=::LoadBitmap(::GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDB_BITMAP_CUSTOM));
		m_ToolBar2.AddButton(ID_MENU_OTHER,TBSTATE_ENABLED,BTNS_BUTTON,
			_T("Other"),NULL,0,hBitmap);
//		::DeleteObject(hBitmap);

//пробуем вставить
		hBitmap=::LoadBitmap(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP_CUSTOM2));
		ULWnds::ULControls::CULMenu popupMenu;
		popupMenu.LoadMenu(ULOther::ULGetResourceHandle(),MAKEINTRESOURCE(IDC_SMPLULFRAMEWND));
		m_ToolBar2.InsertButton(7,ID_MENU_OTHER2,TBSTATE_ENABLED, BTNS_DROPDOWN |BTNS_BUTTON ,
			_T("insert button"),NULL,0,hBitmap,popupMenu.GetSubMenu(0));
		popupMenu.Detach();
		::DeleteObject(hBitmap);
//		m_ToolBar2.AutoSize();

//пробуем удалить
//		m_ToolBar.DeleteButton(2);
	}

	fRet=m_ReBarTop.InsertBand(0,m_ToolBar2,_T("Тулбар2"),NULL,(WORD)ID_TB,&szToolBar);
	*/

	//====================================================================

	m_ToolBar.SendMessage(TB_MARKBUTTON,ID_MENU_NEW,1);
//	m_ToolBar.SendMessage(TB_CHECKBUTTON,ID_MENU_NEW,0);

	return FALSE;
} 

LRESULT CULCFrameWnd::OnSize(WPARAM wParam,LPARAM lParam)
{
	m_ReBarTop.AutoSize();
	m_StatusBar.AutoSize();
	return FALSE;
}
void CULCFrameWnd::OnMenuNew(WORD id,HWND hControl)
{
	MessageBox(_T("New(Типа мессага)"),_T("Menu"),0);
//	::MessageBox(m_hWnd,"New(Удаляем 0 Band)","Menu",0);
//	m_ReBar.DeleteBand(0);
}

void CULCFrameWnd::OnMenuExit(WORD id,HWND hControl)
{
	DestroyWindow();
}

void CULCFrameWnd::OnMenuAbout(WORD id,HWND hControl)
{
	ULWnds::ULDlgs::CULDlg dlgAbout;
	dlgAbout.CreateModal(IDD_ABOUTBOX,m_hWnd);	
}
