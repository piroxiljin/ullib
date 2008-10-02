#pragma once
#include "..\..\ULLib\Include\ULDlgs.h"
#include "resource.h"

class CFinishPage :
	public ULWnds::ULDlgs::CULPropPage
{
public:
	CFinishPage(void);
	~CFinishPage(void);
	virtual LRESULT OnInitDialog(WPARAM,LPARAM);
	virtual LRESULT OnSetActive(DWORD dwFlags);
	virtual LRESULT OnWizFinish(BOOL bFinish);
};
