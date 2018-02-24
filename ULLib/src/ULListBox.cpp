///\file ULListBox.cpp
///\brief cpp ���� ������ ������ ��� LISTBOX ��������(08.09.2007)
#include "ULListBox.h"
#include "ULRes.h"
namespace ULWnds
{
	namespace ULControls
	{
		CULListBox::CULListBox(){};
		CULListBox::~CULListBox(){};
		BOOL CULListBox::Create(HWND hParentWnd,UINT uID,int x,int y,
			int cx,int cy,DWORD dwStyle,DWORD dwStyleEx)
		{
		#ifndef UNICODE
			char szClassName[]="LISTBOX";
		#else
			wchar_t szClassName[]=L"LISTBOX";
		#endif//UNICODE
			m_hParentWnd=hParentWnd;
			m_hWnd = CreateWindowEx(dwStyleEx,szClassName,
				NULL,
				dwStyle, 
				x, y, cx, cy, 
				hParentWnd,(HMENU)(LONG_PTR)uID,   
				ULOther::ULGetResourceHandle(),
				NULL);
			return CULSubClass::Attach(m_hWnd);
		};
	}
}