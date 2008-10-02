#pragma once
#ifndef __UL_UDLG_H__
#define __UL_UDLG_H__

#include "..\\resource.h"
#include "..\\..\\..\\ULLib\\Include\\ULLib.h"

using namespace ULWnds;
using namespace ULControls;
using namespace ULControls::ULButtons;
using namespace ULDlgs;

class CAboutDlg:public CULDlg
{
public:
	CAboutDlg(short idIcon):
	  CULDlg(idIcon)
	{
		MessageMap.AddCommand<CAboutDlg>(IDC_BUTTON_COLOR,&CAboutDlg::OnBtnColor);
		MessageMap.AddCommand<CAboutDlg>(IDC_BUTTON_FILE,&CAboutDlg::OnBtnFile);		
		ULApps::CULApp::GetULApp()->MessageMap.InitializePreTranslateMessage<CAboutDlg>(this,&CAboutDlg::PreTranslateMessage);
	};
	~CAboutDlg()
	{
		ULApps::CULApp::GetULApp()->MessageMap.UnInitializePreTranslateMessage<CAboutDlg>(this,&CAboutDlg::PreTranslateMessage);
	};

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CULDlg::PreTranslateMessage(pMsg);
	}

	virtual LRESULT OnInitDialog(WPARAM,LPARAM)
	{
		m_StyleButtonOK.Attach(::GetDlgItem(*this,IDOK));
		m_StyleButtonCancel.Attach(::GetDlgItem(*this,IDCANCEL));
		return FALSE;
	};
	void OnBtnColor(WORD,HWND)
	{
		ULDlgs::ULCommDlgs::CULColorDlg dlg;
		dlg.CreateModal(0,*this);		
	}
	void OnBtnFile(WORD,HWND)
	{
		ULDlgs::ULCommDlgs::CULFileDlg dlg(TRUE,_T("exe"),_T("qwerty"),4|2/*|32*/,_T("All\0*.*\0Executable\0*.exe\0"),1);
		if(dlg.CreateModal(0,*this))		
			MessageBox(dlg.GetFileName(),0,0);
	}
	

	CULStyleButton m_StyleButtonOK,m_StyleButtonCancel;
};



#define IDC_BUTTON_OWNERDRAW	100
#define IDC_BUTTON_BITMAP		101


class CULCDlg:public CULDlg
{
protected:
public:
	//=============================================
	//конструктор
	CULCDlg();
	//деструктор
	~CULCDlg(void);
	virtual LRESULT OnInitDialog(WPARAM,LPARAM);
	virtual void OnButtonAbout(WORD id,HWND hControl);
	virtual void OnCancel(WORD id,HWND hControl);
	virtual void OnButtonOwnerDraw(WORD id,HWND hControl);
	virtual void OnButtonBitmap(WORD id,HWND hControl);
	//==============================================
	CAboutDlg* m_pAboutDlg;
	CULToolTip m_ULToolTip;
	CULStyleButton m_StyleButton,m_StyleButtonOK,m_StyleButtonCancel,m_StyleButtonAbout;
	CULBitmapButton m_BitmapButton;

	CULHyperLink m_HyperLink,m_HyperLink2;
};
#endif//__UL_UDLG_H__