#include ".\ulcdlg.h"
#include <ULStates.h>
#include <tchar.h>
/////////////////////////////////////////////////////////////////////////////
CULCDlg::CULCDlg():
	m_pAboutDlg(NULL)
{
	MessageMap.AddCommand<CULCDlg>(IDC_BUTTON_ABOUT,&CULCDlg::OnButtonAbout);
	MessageMap.AddCommand<CULCDlg>(IDC_BUTTON_OWNERDRAW,&CULCDlg::OnButtonOwnerDraw);
	MessageMap.AddCommand<CULCDlg>(IDC_BUTTON_BITMAP,&CULCDlg::OnButtonBitmap);
}

CULCDlg::~CULCDlg(void)
{
	if(m_pAboutDlg!=NULL) 
		delete m_pAboutDlg;
}

//==============================================================================
LRESULT CULCDlg::OnInitDialog(WPARAM,LPARAM)
{
	LOGFILE_ADD(_T("OnInitDialog"));
	CULDlg::OnInitDialog(0,0);
	ThemeClient.Create(*this);
//	ThemeClient.SetRadius(20);
//	ThemeClient.SetColors(0x666666,0xffffff);
//========================================================
	m_StyleButton.CreateStyleButton(*this,_T("Create"),IDC_BUTTON_OWNERDRAW,
		10,100,100,40);
	CULStyleButton::tagButtonColors bc;
	m_StyleButton.GetButtonColors(&bc);
	bc.bcFocused=0x00ff00;
	bc.bcHiLiteText=0x00ffff;
	bc.bcDefaultText=0xffffff;
	bc.bcDisable=0x0000ff;
	bc.bcGradientColors.gcDownFirst=0xff0000;
	bc.bcGradientColors.gcDownSecond=0x0000ff;
	bc.bcGradientColors.gcUpSecond=0xff0000;
	bc.bcGradientColors.gcUpFirst=0x0000ff;
	bc.bcGradientDest=CULStyleButton::tagButtonColors::gdLeftRight;
	m_StyleButton.SetRadius(5);
	m_StyleButton.SetButtonColors(bc);

	m_StyleButtonOK.Attach(GetDlgItem(IDOK));
	m_StyleButtonCancel.Attach(GetDlgItem(IDCANCEL));
	m_StyleButtonAbout.Attach(GetDlgItem(IDC_BUTTON_ABOUT));

//==============================================================
	m_BitmapButton.CreateBitmapButton(*this,150,100,IDC_BUTTON_BITMAP,IDB_BITMAP_UP,IDB_BITMAP_DOWN,
		IDB_BITMAP_FOCUSED,IDB_BITMAP_HILITE,IDB_BITMAP_DISABLE,IDB_BITMAP_MASK);
//==============================================================
	m_HyperLink.CreateHyperLink(*this,20,55,_T("с:\\"),_T("c:\\"),IDC_HYPERLINK);
	m_HyperLink.SetStyles(CULHyperLink::tDefault,CULHyperLink::sUnderLine,0x00ff00);
	m_HyperLink2.Attach(GetDlgItem(IDC_HYPERLINK2),_T("http://forum.sources.ru"));
//==============================================================
	m_ULToolTip.Create(NULL);
	m_ULToolTip.AddTool(*this,_T("Это диалог"));
	m_ULToolTip.AddTool(GetDlgItem(IDC_BUTTON_ABOUT),_T("Вызов диалога \"О программе\""));
	m_ULToolTip.AddTool(GetDlgItem(IDOK),_T("Ну типа ОК"));
	m_ULToolTip.AddTool(GetDlgItem(IDCANCEL),_T("Кароче Кансель"));
	m_ULToolTip.AddTool(GetDlgItem(IDC_BUTTON_OWNERDRAW),_T("Стильная кнопка"));
	m_ULToolTip.AddTool(GetDlgItem(IDC_BUTTON_BITMAP),_T("Bitmap кнопка"));
	m_ULToolTip.AddTool(GetDlgItem(IDC_HYPERLINK),_T("Переход на диск С"));
	m_ULToolTip.AddTool(GetDlgItem(IDC_HYPERLINK2),_T("Переход на http://forum.sources.ru"));

	m_ULToolTip.SetTipBkColor(0xfff5f5);
	m_ULToolTip.SetTipTextColor(0xff0000);
	m_ULToolTip.SetTitle(ULControls::CULToolTip::itInfo,_T("Типа информация"));
	m_ULToolTip.SetDelayTime(100);

//==============================================================
	LOGFILE_SAVE(_T("OnInitDialog"));
	return FALSE;
};

void CULCDlg::OnButtonAbout(WORD /*id*/,HWND /*hControl*/)
{
	m_pAboutDlg=new CAboutDlg(m_idIcon);
	m_pAboutDlg->Create(IDD_ABOUTBOX,*this);
	m_pAboutDlg->ShowWindow(SW_SHOW);
	m_pAboutDlg->UpdateWindow();
}
void CULCDlg::OnCancel(WORD id,HWND /*hControl*/)
{

	CULDlg::OnCancel(id,0);
}

void CULCDlg::OnButtonOwnerDraw(WORD /*id*/,HWND /*hControl*/)
{
//	MessageBox("OnButtonOwnerDraw",0,0);
//	::EnableWindow(hControl,FALSE);
}

void CULCDlg::OnButtonBitmap(WORD /*id*/,HWND /*hControl*/)
{
//	::EnableWindow(hControl,FALSE);
}

