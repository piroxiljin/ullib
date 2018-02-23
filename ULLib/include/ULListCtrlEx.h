///\file ULListCtrlEx.h 
///\brief ���� ���������� ������ ������������ ���� ��������(BETA)
#ifndef _ULLISTCTRL_EX_H__
#define _ULLISTCTRL_EX_H__
#include "ULControls.h"
#include "commctrl.h"
#include "ULGDI.h"
#include "ULOther.h"
#include "ULDateTimePicker.h"
#include "ULButtons.h"
#include <uxtheme.h>
#if _MSC_VER < 1600
#include <tmschema.h>
#else
#include <vssym32.h>
#endif

namespace ULWnds
{
	namespace ULControls
	{
		///\brief ������������ ���� ������������ ���� ��������
		namespace ULListCtrlEx
		{
			///\brief ��������� ������� ����������� � ������ ������������ ������������
			struct IItemObject
			{
				///\brief ����������
				virtual ~IItemObject(){};
				///\brief ������� ��������� �������
				///\param pDC - ��������� �� ����� ���������, � ������� ������������ ���������
				///\param rc - ������� ������, � ������� ������������ ���������
				///\note ����� ������ �� �������, ���������� ������ ��������� ��� �����������, \n
				///\ � ��� �� ������ ���� �����
				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc)=0;
				///\brief ���������, ���������� ��� ����� �� ������
				///\param rc - ������� ������
				///\note ��� ������ ������ ������ ������ ����� �� ������� � � ����������� ������ ����������� \n
				///\ ���� ��������� � ������� Draw
				virtual void OnClick(RECT& rc)=0;
				///\brief ���������, ���������� ��� ������� �� ������
				///\param rc - ������� ������
				virtual void OnLButtonDown(RECT& rc)=0;
				///\brief ������� ��� ��������� ������� �������
				///\param prc - ����������� �� ��������� � �������� �������
				virtual bool GetRect(RECT* prc)=0;
				///\brief ���������� ���������� �������
				virtual void Clean()=0;	
				///\brief ��������� ���������� ����� ��� ����� ���� windows
				virtual void OnThemeChanged()=0;
			};
			///\class CULListCtrlEx
			///\brief ����� ������������ ���� ��������
			class CULListCtrlEx:
				public ULWnds::ULControls::CULListCtrl
			{
			private:
				///\brief ��������� ����/�������
				int m_nItemSel,m_nSubItemSel;
				///\brief ������������ ���������� ���������
				///\param LCEM_RETURNITEMSEL - ������������� ���������, ����������� \n
				///\ ������ ���� ��� ������������� �����. ��� ����������, ��� ���� ����� �����������\n
				///\ ���������� ����� ����� �����������.
				enum enLCEM
				{
					LCEM_RETURNITEMSEL=WM_APP+1
				};
				///\brief 
				int m_nItemCount;
			public:
				///\brief �����������
				CULListCtrlEx();
				///\brief ����������
				~CULListCtrlEx();
				///\brief ������ ����������� �����������
				///\param hParentWnd - ����� ������������� ����
				///\param uID - ������������� ��������
				///\param x,y - ���������� ����
				///\param cx,cy - ������� ����
				///\param dwStyle - ����� ����
				///\param dwStyleEx - ����������� ����� ����		
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,UINT uID,int x,int y,int cx,int cy,DWORD dwStyle,DWORD dwStyleEx);
				///\brief ������� �������������� ������� ������� �������
				///\param hWnd
				BOOL Attach(HWND hWnd);
				///\brief ��������� ���� 
				///\param nItem - ������� �������
				///\param lpszItem - ������
				///\return ����� ������������ �����
				int InsertItem(int nItem,LPCTSTR lpszItem);
				///\brief ������������� ����� � ������ �������
				///\param nItem - � ����� ��� �������
				///\param nSubItem - � �������� ��� �������
				///\param lpszText - ����� ��� �������
				///\return TRUE � ������ ������
				BOOL SetItemText(int nItem,int nSubItem,LPCTSTR lpszText);
				///\brief ������������� ����� � ������ �������
				///\param nItem - � ����� ��� �������
				///\param nSubItem - � �������� ��� �������
				///\param pItemObject - ��������� �� ����� ����������� � ������
				///\return TRUE � ������ ������
				BOOL SetItemObject(int nItem,int nSubItem,IItemObject* pItemObject);
				///\brief ������� ��� ��������� ������� �� ������
				///\param nItem - � ����� ��� �������
				///\param nSubItem - � �������� ��� �������
				///\return pItemObject - ���������� ��������� �� ����� ����������� � ������ \n
				///\� ������ ������, ����� NULL
				IItemObject* GetItemObject(int nItem,int nSubItem);
				///\brief ������� ��� ����� � ������������
				///\return TRUE � ������ ������
				BOOL DeleteAllItems();
				///\brief ������� ��������� �������
				///\param nItem - ������� ��� ��������
				///\return TRUE � ������ ������
				BOOL DeleteItem(int nItem);
			protected:
				///\brief ���������� CULListCtrl::SetItemData
				BOOL SetItemData(int nItem,DWORD_PTR dwData);
			protected:
				///\brief ���������� ��������� ������������
				virtual LRESULT OnCustomDraw(LPARAM);
				///\brief ��������� ��������� ����������� ������(� ���������� ����� ��������)
				virtual LRESULT OnMeasureItem(WPARAM,LPARAM);
				///\brief ��������� ��������� ��������� ����������������
				virtual LRESULT OnWindowPosChanged(WPARAM,LPARAM);
				///\brief ��������� ��������� ������� ����
				virtual LRESULT OnEraseBkGnd(WPARAM,LPARAM);
				///\brief ��������� ��������� ������������� �� ���������
				virtual LRESULT OnVScroll(WPARAM,LPARAM);
				///\brief ��������� ��������� ����������� �� �����������
				virtual LRESULT OnHScroll(WPARAM,LPARAM);
				///\brief ��������� ��������� �������� ������ ����
				virtual LRESULT OnMouseWheel(WPARAM,LPARAM);
				///\brief ��������� ��������� ������� �� ����� ������ ����
				virtual LRESULT OnLButtonDown(WPARAM,LPARAM);
				///\brief ��������� ��������� ����� �� �����
				virtual LRESULT OnNMClick(LPARAM lParam);
				///\brief ��������� ��������� LCEM_RETURNITEMSEL
				virtual LRESULT OnReturnItemSel(WPARAM,LPARAM);
				///\brief ��������� ��������� WM_COMMAND ��� ��������� ��������� ��������
				virtual LRESULT OnCommand(WPARAM,LPARAM);
				///\brief ��������� ��������� WM_DESTROY
				virtual LRESULT OnDestroy(WPARAM,LPARAM);
				///\brief ��������� ��������� WM_THEMECHANGED
				virtual LRESULT OnThemeChanged(WPARAM,LPARAM);
			};
			//=====================================================================
			///\class CItemText
			///\brief ����� �������� ��������� ������� ��� �����
			class CItemText:
				public IItemObject
			{
				///\brief ������ ��� �������� ��������� ������
				ULOther::CULStr m_strText;
				///\brief ����� ������
				 HICON m_hIcon;
			public:
				///\brief �����������
				CItemText();
				///\brief ������� ��� ��������� ������ � ������
				///\param pszText - ����� � �������
				void SetText(LPCTSTR pszText);
				///\brief ������� ��� ��������� ��������� ������
				LPCTSTR GetText();
				///\brief ������������� ������ ����� �� ������
				///\param hIcon - ����� ������
				void SetIcon(HICON hIcon);

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/){}
				virtual void OnClick(RECT& /*rc*/){}
				virtual bool GetRect(RECT* /*prc*/){return false;}
				virtual void Clean();
				virtual void OnThemeChanged(){};
			};
			//=====================================================================
			///\class CItemEdit
			///\brief ����� ����� ������� ��� �����
			class CItemEdit:
				public IItemObject		
			{	
			public:
				class CEdit:
					public CULEdit
				{
				public:
					CEdit();
					virtual LRESULT OnKillFocus(WPARAM,LPARAM);
					virtual LRESULT OnActivate(WPARAM wParam,LPARAM);
				};
				///\brief ������ ��� ������ ������ ������ � ������� � ��������� � ������ Edit
				CEdit m_Edit;
			public:
				///\brief ������ �������� �������
				///\param hParentWnd - ����� ������������� ����, ������ ��� ����� ���������� CULListCtrlEx
				///\param uID - ������������� ��������
				///\param pszStr - ��������� ����� � �����
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,UINT uID,LPCTSTR pszStr);
				///\brief ����������
				~CItemEdit();

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/){}
				virtual void OnClick(RECT& rc);
				virtual bool GetRect(RECT* /*prc*/){return false;}
				virtual void Clean();
				virtual void OnThemeChanged(){};
			};
			//=====================================================================
			///\class CItemComboBox
			///\brief ����� ���������� ������� ��� �����
			class CItemComboBox:
				public IItemObject		
			{	
			protected:
				///\brief ����� ���� ��
				HTHEME m_hTheme;
			protected:
				class CComboBox:
					public CULComboBox
				{
				public:
					CComboBox();
					virtual LRESULT OnKillFocus(WPARAM,LPARAM);
				};
				class CEdit:
					public CULEdit
				{
				public:
					CEdit();
				protected:
					virtual LRESULT OnKillFocus(WPARAM,LPARAM);
				};
			public:
				///\brief ������ ��� ������ ������ ������ � ������� � ��������� � ������ ComboBox
				CComboBox m_ComboBox;
			protected:
				///\brief ������ ��� ������ ������ ������ � �������
				CEdit m_Edit;
			public:
				///\brief ����������
				~CItemComboBox();
				///\brief ������ �������� �������
				///\param hParentWnd - ����� ������������� ����, ������ ��� ����� ���������� CULListCtrlEx
				///\param uID - ������������� ��������
				///\param fDropDownList - ���� ��� �������� TRUE(�� ��������)/FALSE(� ������)
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,UINT uID,BOOL fDropDownList);

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/);
				virtual void OnClick(RECT& rc);
				virtual bool GetRect(RECT* prc);
				virtual void Clean();
				virtual void OnThemeChanged();
			};
			//=====================================================================
			///\class CItemDateTimePicker
			///\brief ����� �������� ������� ���� ������� ��� �����
			class CItemDateTimePicker:
				public IItemObject
			{
			protected:
				///\brief ����� ���� ��
				HTHEME m_hTheme;
			public:
				class CDateTimePicker:
					public CULDateTimePicker
				{
				public:
					CDateTimePicker();
				protected:
					virtual LRESULT OnKillFocus(WPARAM wParam,LPARAM);
				};
				///\brief ������ ��� ������ ������ ������ � ������� � ��������� � ������ DateTimePicker
				CDateTimePicker m_DateTimePicker;
			public:
				///\brief ����������
				~CItemDateTimePicker();
				///\brief ������ �������� �������
				///\param hParentWnd - ����� ������������� ����, ������ ��� ����� ���������� CULListCtrlEx
				///\param uID - ������������� ��������
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,WORD uID);

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/);
				virtual void OnClick(RECT& rc);
				virtual void Clean();
				virtual bool GetRect(RECT* prc);
				virtual void OnThemeChanged();
			};
			//=====================================================================
			///\class CItemButton
			///\brief ����� ������ ������� ��� �����
			class CItemButton:
				public IItemObject		
			{	
			protected:
				///\brief ����� ���� ��
				HTHEME m_hTheme;
			public:
				class CButton:
					public ULButtons::CULButton
				{
				public:
					CButton();
					virtual LRESULT OnKillFocus(WPARAM,LPARAM);
				};
				///\brief ������ ��� ������ ������ ������ � �������
				CButton m_Button;
			public:
				///\brief ����������
				~CItemButton();
				///\brief ������ �������� �������
				///\param hParentWnd - ����� ������������� ����, ������ ��� ����� ���������� CULListCtrlEx
				///\param uID - ������������� ��������
				///\param pszStr - ��������� ����� � ������
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,UINT uID,LPCTSTR pszStr);

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/);
				virtual void OnClick(RECT& rc);
				virtual bool GetRect(RECT* /*prc*/){return false;}
				virtual void Clean();
				virtual void OnThemeChanged();
			};
#pragma message(__FILE__":���������� �� IOM_GETITEMDATA")
			const int IOM_GETITEMDATA=WM_APP+1;
			//=====================================================================
			///\class CItemCheckBox
			///\brief ����� �������� ������� ��� �����
			class CItemCheckBox:
				public IItemObject		
			{	
			protected:
				///\brief ����� ���� ��
				HTHEME m_hTheme;
			protected:
				class CButton:
					public ULButtons::CULButton
				{
				protected:
					DWORD m_dwData;
				public:
					CButton();
					void SetItemData(DWORD dwData);
				protected:
					virtual LRESULT OnKillFocus(WPARAM,LPARAM);
					virtual LRESULT OnGetItemData(WPARAM,LPARAM);

				};
			public:
				///\brief ������ ��� ������ ������ ������ � �������
				CButton m_Button;
			public:
				///\brief ����������
				~CItemCheckBox();
				///\brief ������ �������� �������
				///\param hParentWnd - ����� ������������� ����, ������ ��� ����� ���������� CULListCtrlEx
				///\param uID - ������������� ��������
				///\param pszStr - ��������� ����� � ������
				///\return TRUE � ������ ������
				BOOL Create(HWND hParentWnd,UINT uID,LPCTSTR pszStr);
				///\brief �������������/������� ������
				///\param fCheck - ���� ���������
				void SetCheck(BOOL fCheck);
				///\brief ���������� ��������� ��������
				///\return ��������� ��������
				BOOL GetCheck();

				void SetItemData(DWORD dwData);

				virtual void Draw(ULGDI::ULDC::CULDC* pDC,RECT& rc);
				virtual void OnLButtonDown(RECT& /*rc*/);
				virtual void OnClick(RECT& rc);
				virtual bool GetRect(RECT* /*prc*/){return false;}
				virtual void Clean();
				virtual void OnThemeChanged();
			};
		}
	}
}

#endif //_ULLISTCTRL_EX_H__