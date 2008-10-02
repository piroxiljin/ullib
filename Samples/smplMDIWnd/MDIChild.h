#pragma once
#include "..\..\ULLib\Include\ULFrames.h"

class CMDIChild :
	public ULWnds::ULFrames::CULMDIChildWnd
{
public:
	CMDIChild(void);
	~CMDIChild(void);

	LRESULT OnPaint(WPARAM,LPARAM);
};
