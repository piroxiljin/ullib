///\file ULWnd.cpp
///\brief cpp файл класса root окна(07.10.2007)
#include "..\..\ULLib\Include\UlWnd.h"
namespace ULWnds
{

	CULWnd::CULWnd(void):
		m_hParentWnd(NULL),
		m_hWnd(NULL),
		m_lpSubClassWndProc(NULL)
	{
	}
	CULWnd::CULWnd(CULWnd& Wnd):
		m_hParentWnd(Wnd.m_hParentWnd),
		m_hWnd(Wnd.m_hWnd),
		m_lpSubClassWndProc(Wnd.m_lpSubClassWndProc),
		MessageMap(Wnd.MessageMap)
	{
	}

	CULWnd::CULWnd(HWND hwnd):m_hWnd(hwnd)
	{
		m_hParentWnd=GetParent();
		m_lpSubClassWndProc=NULL;
		CULWnd* pWnd=FromHandle(hwnd);
		if(pWnd)
		{
			m_lpSubClassWndProc=pWnd->m_lpSubClassWndProc;
			MessageMap=pWnd->MessageMap;
		}
	}

	CULWnd::~CULWnd(void)
	{
		DestroyWindow();//уничтожаем окно при уничтожении класса
	}

	void CULWnd::operator = (CULWnd& Wnd)
	{
		m_hParentWnd=Wnd.m_hParentWnd;
		m_hWnd=Wnd.m_hWnd;
		m_lpSubClassWndProc=Wnd.m_lpSubClassWndProc;
		MessageMap=Wnd.MessageMap;
	}

	BOOL CULWnd::PreTranslateMessage(MSG* /*pMsg*/)
	{
		return TRUE;
	};
	//================================================
	//Функция окна
	//здесь при создании окна (WM_INITDIALOG,WM_NCCREATE)
	//сохраняется this в GWL_USERDATA для последующего использования
	//в WndProc нестатических членов класса 
	//в WM_INITDIALOG this передаётся через CreateDialogParam
	//в WM_NCCREATE this передаётся через CreateWindow
	//================================================
	LRESULT CULWnd::WndProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
	{
		LONG dwNewLong;
		CULWnd *pULWnd=NULL;
		switch(uMsg)
		{
		case WM_CREATE:
			{
				dwNewLong=(LONG)(LONG_PTR) ((LPCREATESTRUCT) lParam)->lpCreateParams;
				::SetWindowLong (hWnd, GWL_USERDATA,dwNewLong);
				// получим указатель на класс
				pULWnd = (CULWnd*)(((LPCREATESTRUCT) lParam)->lpCreateParams); 
				pULWnd->m_hWnd=hWnd;
				break;
			}
		default:
			{
			   pULWnd = FromHandle(hWnd);
			}
		}

		if(pULWnd!=NULL)
		{
			if(uMsg==WM_COMMAND)
			{
					BOOL fRet=pULWnd->MessageMap.ProcessCommand(pULWnd,wParam,lParam);
					if(fRet)
						return fRet;
			}
			else 
				if(uMsg==WM_NOTIFY)
				{
					BOOL fRet=pULWnd->MessageMap.ProcessNotify(pULWnd,(NMHDR*)lParam);
					if(fRet)
						return fRet;
				}
			BOOL fRet=pULWnd->MessageMap.ProcessMessage(pULWnd,uMsg,wParam,lParam);
			if(fRet)
				return fRet;
			else
				return pULWnd->DefWindowProc(uMsg, wParam, lParam);
		}
		else
			return ::DefWindowProc(hWnd,uMsg, wParam, lParam);
	}
}