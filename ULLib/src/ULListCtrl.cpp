///\file ULListCtrl.cpp
///\brief фаил реализации класса лист контрола
#include "..\..\ULLib\Include\ULListCtrl.h"
#include "..\..\ULLib\Include\ULRes.h"
namespace ULWnds
{
	namespace ULControls
	{

		CULListCtrl::CULListCtrl():
			ULWnds::CULSubClass()
		{

		}

		BOOL CULListCtrl::Create(HWND hParentWnd,UINT uID,int x,int y,
			int cx,int cy,DWORD dwStyle,DWORD dwStyleEx)
		{
			m_hParentWnd=hParentWnd;
			m_hWnd = CreateWindowEx(dwStyleEx,WC_LISTVIEW,
				NULL,
				dwStyle, 
				x, y, cx, cy, 
				hParentWnd,(HMENU)(LONG_PTR)uID,   
				ULOther::ULGetResourceHandle(), 
				NULL);
			return CULSubClass::Attach(m_hWnd);
		}

		int CULListCtrl::InsertColumn(int nCol,LPCTSTR lpszColumnHeading,int nFormat,int nWidth,int nSubItem)
		{
			LVCOLUMN lvc;
			lvc.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVCF_FMT;
			lvc.pszText=(LPTSTR)lpszColumnHeading;
			lvc.cchTextMax=static_cast<int>(_tcslen(lpszColumnHeading)+1);
			lvc.fmt=nFormat;
			lvc.cx=nWidth;
			lvc.iSubItem=nSubItem;
			return (int)SendMessage(LVM_INSERTCOLUMN,(WPARAM)nCol,(LPARAM)&lvc);
		}

		BOOL CULListCtrl::SetColumnWidth(int nCol,int cx)
		{
			return (BOOL)SendMessage(LVM_SETCOLUMNWIDTH,(WPARAM)nCol,(LPARAM)cx);
		}

		int CULListCtrl::GetColumnWidth(int nCol)
		{
			return (int)SendMessage(LVM_GETCOLUMNWIDTH,(WPARAM)nCol);
		}

		int CULListCtrl::InsertItem(int nItem,LPCTSTR lpszItem)
		{
			LVITEM lvi;
			lvi.mask=LVIF_TEXT;
			lvi.iItem=nItem;
			lvi.iSubItem=0;
			lvi.pszText=(LPTSTR)lpszItem;
			lvi.cchTextMax=static_cast<int>(_tcslen(lpszItem)+1);
			return (int)SendMessage(LVM_INSERTITEM,0,(LPARAM)&lvi);
		}

		BOOL CULListCtrl::SetItemText(int nItem,int nSubItem,LPCTSTR lpszText)
		{
			LVITEM lvi;
			lvi.mask=LVIF_TEXT;
			lvi.iItem=nItem;
			lvi.iSubItem=nSubItem;
			lvi.pszText=(LPTSTR)lpszText;
			lvi.cchTextMax=static_cast<int>(_tcslen(lpszText)+1);
			return (int)SendMessage(LVM_SETITEM,0,(LPARAM)&lvi);
		}
		int CULListCtrl::GetItemCount()
		{
			return (int)SendMessage(LVM_GETITEMCOUNT);
		}

		DWORD CULListCtrl::SetExtendedStyle(DWORD dwNewStyle)
		{
			return (DWORD)SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,(WPARAM)dwNewStyle,(LPARAM)dwNewStyle);
		}

		BOOL CULListCtrl::DeleteAllItems()
		{
			return (BOOL)SendMessage(LVM_DELETEALLITEMS);
		}

		BOOL CULListCtrl::GetColumn(int nCol,LPLVCOLUMN pCol)
		{
			return (BOOL)SendMessage(LVM_GETCOLUMN,(WPARAM)nCol,(LPARAM)pCol);	
		}
	}
}
