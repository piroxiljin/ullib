#pragma once

#include <ULLib.h>

class CMainFrame:
	public ULWnds::ULFrames::CULFrameWnd
{
public:
	CMainFrame(void);
	virtual ~CMainFrame(void);
protected:
///////////////WM_...///////////////////////////
	virtual LRESULT OnCreate(WPARAM /*wParam*/,LPARAM /*lParam*/);
};
