///\file ULEdit.cpp
///\brief cpp ���� ������ ������ ��� EDIT ��������(16.08.2007)
#include "ULEdit.h"
#include "ULRes.h"
#include <tchar.h>
namespace ULWnds
{
	namespace ULControls
	{
		CULEdit::CULEdit():ULWnds::CULSubClass()
		{
			MessageMap.AddMessage<CULEdit>(WM_DROPFILES,&CULEdit::OnDropFiles);
		};
		CULEdit::~CULEdit()
		{
		};

		BOOL CULEdit::Create(HWND hParentWnd,LPCTSTR pszText,UINT uID,int x,int y,
			int cx,int cy,DWORD dwStyle,DWORD dwStyleEx)
		{
			m_hParentWnd=hParentWnd;
			m_hWnd = CreateWindowEx(dwStyleEx,_T("EDIT"),
				NULL,
				dwStyle, 
				x, y, cx, cy, 
				hParentWnd,(HMENU)(LONG_PTR)uID,   
				ULOther::ULGetResourceHandle(), 
				NULL);
			SetWindowText(pszText);
			return CULSubClass::Attach(m_hWnd);
		};

		LRESULT CULEdit::OnDropFiles(WPARAM wParam,LPARAM)
		{
			HDROP hDrop=(HDROP)wParam;
			TCHAR szFilePath[MAX_PATH];
			DragQueryFile(hDrop,0,szFilePath,MAX_PATH);
			DragFinish(hDrop);
			SetWindowText(szFilePath);
			return FALSE;
		};
	}
}