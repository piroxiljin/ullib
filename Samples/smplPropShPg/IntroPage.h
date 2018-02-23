#pragma once
#include <ULDlgs.h>
#include "resource.h"
class CIntroPage :
	public ULWnds::ULDlgs::CULPropPage
{
public:
	CIntroPage(void);
	~CIntroPage(void);
	virtual LRESULT OnInitDialog(WPARAM,LPARAM);
	virtual LRESULT OnSetActive(DWORD dwFlags);
};
