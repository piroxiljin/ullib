///\file ULProgressBar.cpp
///\brief фаил реализации класса обёртки для ProgressBar
#pragma message("ULProgressBar.cpp поменять пути при переносе в библиотеку")
#include "ULProgressBar.h"
//#include "..\Include\ULProgressBar.h"
#include "ULStates.h"
//#include "..\Include\ULStates.h"
#include <commctrl.h>
namespace ULWnds
{
	namespace ULControls
	{
		CULProgressBar::CULProgressBar():
			ULWnds::CULSubClass()
		{
		}

		BOOL CULProgressBar::Create(HWND hParentWnd,UINT uID,int x,int y,int cx,int cy,DWORD dwStyle,DWORD dwStyleEx)
		{
			m_hParentWnd=hParentWnd;
			m_hWnd = CreateWindowEx(dwStyleEx,PROGRESS_CLASS,
				NULL,
				dwStyle, 
				x, y, cx, cy, 
				hParentWnd,(HMENU)(LONG_PTR)uID,   
				ULOther::ULGetResourceHandle(), 
				NULL);
			return CULSubClass::Attach(m_hWnd);
		}

		int CULProgressBar::SetPos(int nPos)
		{
			return (int)SendMessage(PBM_SETPOS,(LPARAM)nPos,0);
		}

		void CULProgressBar::SetRange(short nLower,short nUpper)
		{
			SendMessage(PBM_SETRANGE,0,MAKELPARAM(nLower,nUpper));
		}

	}
}
