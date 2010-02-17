#pragma once
#include "..\..\ULLib\Include\ULDlgs.h"
#include "..\..\ULLib\Include\ULLib.h"
#include "resource.h"
#include <assert.h>

class CPage1:public ULWnds::ULDlgs::CULPropPage
{
public:
	CPage1():ULWnds::ULDlgs::CULPropPage()
	{
		MessageMap.AddCommand<CPage1>(IDC_BUTTON1,&CPage1::OnBtn1);		
	};
	virtual ~CPage1(){};
	virtual LRESULT OnInitDialog(WPARAM w,LPARAM l)
	{
		HWND hBtnOK=::GetDlgItem(GetParent(),IDOK);
		HWND hBtnCancel=::GetDlgItem(GetParent(),IDCANCEL);
		assert(hBtnOK!=NULL);
		assert(hBtnCancel!=NULL);
		ULWnds::ULControls::ULButtons::CULButton btnOk;
		ULWnds::ULControls::ULButtons::CULButton btnCancel;
		btnCancel.Attach(hBtnCancel);
		btnCancel.ModifyStyle(BS_DEFPUSHBUTTON,0);
		btnCancel.Detach();

		btnOk.Attach(hBtnOK);
		btnOk.ModifyStyle(0,BS_DEFPUSHBUTTON);
		btnOk.SetActiveWindow();
		btnOk.SetFocus();
		btnOk.Detach();

		::SendMessage(GetParent(),WM_NEXTDLGCTL, (WPARAM)hBtnOK, TRUE);
		return ULWnds::ULDlgs::CULPropPage::OnInitDialog(w,l);
	}
	void OnBtn1(WORD,HWND)
	{
		MessageBox(_T("Page1"),_T("Окно"),0);
	}
};

class CPage2:public ULWnds::ULDlgs::CULPropPage
{
public:
	CPage2():ULWnds::ULDlgs::CULPropPage()
	{
		MessageMap.AddCommand<CPage2>(IDC_BUTTON1,&CPage2::OnBtn1);
	};
	~CPage2(){};
	virtual LRESULT OnInitDialog(WPARAM w,LPARAM l)
	{
	/*	HWND hBtnOK=::GetDlgItem(GetParent(),IDOK);
		HWND hBtnCancel=::GetDlgItem(GetParent(),IDCANCEL);
		assert(hBtnOK!=NULL);
		assert(hBtnCancel!=NULL);
		ULWnds::ULControls::ULButtons::CULButton btnOk;
		ULWnds::ULControls::ULButtons::CULButton btnCancel;
		btnCancel.Attach(hBtnCancel);
		btnCancel.ModifySyle(BS_DEFPUSHBUTTON,0);
		btnCancel.Detach();

		btnOk.Attach(hBtnOK);
		btnOk.ModifySyle(0,BS_DEFPUSHBUTTON);
		btnOk.SetActiveWindow();
		btnOk.SetFocus();
		btnOk.Detach();

		::SendMessage(GetParent(),WM_NEXTDLGCTL, (WPARAM)hBtnOK, TRUE);
	*/	return ULWnds::ULDlgs::CULPropPage::OnInitDialog(w,l);;
	}
	void OnBtn1(WORD,HWND)
	{
		MessageBox(_T("Page2"),_T("Окно"),0);
	}
};



class CWorkPage :
	public ULWnds::ULDlgs::CULPropPage
{
public:
	CPage1 m_Page1;
	CPage2 m_Page2;
	BOOL m_bNext;
	CWorkPage(void);
	~CWorkPage(void);
	void OnBtnPushMe(WORD,HWND);
	virtual LRESULT OnWizNext(short Result);
};
