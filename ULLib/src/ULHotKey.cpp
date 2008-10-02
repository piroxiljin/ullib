///\file ULHotKey.cpp
///\brief cpp файл класса обёртки лдя HOTKEY контрола(09.09.2007)
#include "..\..\ULLib\Include\ULHotKey.h"
namespace ULWnds
{
	namespace ULControls
	{
		CULHotKey::CULHotKey():CULSubClass()
		{
		};
		CULHotKey::~CULHotKey()
		{
		};

		BOOL CULHotKey::Create(HWND hParentWnd,UINT uID,int x,int y,
				int cx,int cy,DWORD dwStyle,DWORD dwStyleEx)
		{
			m_hWnd = CreateWindowEx(dwStyleEx,HOTKEY_CLASS,
				NULL,
				dwStyle, 
				x, y, cx, cy, 
				hParentWnd,(HMENU)(LONG_PTR)uID,   
				GetModuleHandle(NULL), 
				NULL);
			return CULSubClass::Attach(m_hWnd);
		};
	}
}