///\file ULTrayIcon.cpp
///\brief фаил реализации класса иконки в трее
#define _WIN32_IE 0x0500
#include "ULTrayIcon.h"

/*
#if (_WIN32_IE >= 0x0501)
#define NIN_BALLOONSHOW     (WM_USER + 2)
#define NIN_BALLOONHIDE     (WM_USER + 3)
#define NIN_BALLOONTIMEOUT  (WM_USER + 4)
#define NIN_BALLOONUSERCLICK (WM_USER + 5)
#endif
*/
namespace ULOther
{
	CULTrayIcon::CULTrayIcon(void):
		m_nIconCount(0)
	{
		::ZeroMemory(&m_NotifyIconData,sizeof(m_NotifyIconData));
		m_NotifyIconData.cbSize=sizeof(m_NotifyIconData);
	}

	CULTrayIcon::~CULTrayIcon(void)
	{
		for(UINT i=1;i<=m_nIconCount;++i)
			DeleteIcon(i);
	}

	BOOL CULTrayIcon::Create(HWND hWnd,UINT uCallbackMessage)
	{
		if(!::IsWindow(hWnd))
			return FALSE;
		m_NotifyIconData.hWnd=hWnd;
		if(uCallbackMessage<WM_USER)
			return FALSE;
		m_NotifyIconData.uCallbackMessage=uCallbackMessage;
		m_NotifyIconData.uFlags=NIF_MESSAGE;
		return TRUE;
	}

	UINT CULTrayIcon::AddIcon(HICON hIcon)
	{
		m_nIconCount++;
		m_NotifyIconData.hIcon=hIcon;
		m_NotifyIconData.uFlags|=NIF_ICON;
		m_NotifyIconData.uID=m_nIconCount;
		return (::Shell_NotifyIcon(NIM_ADD,&m_NotifyIconData))?
			m_NotifyIconData.uID:0;
	}
	BOOL CULTrayIcon::ChangeIcon(UINT uID,HICON hIcon)
	{
		m_NotifyIconData.hIcon=hIcon;
		m_NotifyIconData.uFlags=NIF_ICON;
		m_NotifyIconData.uID=uID;
		return ::Shell_NotifyIcon(NIM_MODIFY,&m_NotifyIconData);
	}
	BOOL CULTrayIcon::SetIconTip(UINT uID,TCHAR* pszTip)
	{
		if(!pszTip)
			return FALSE;
		_tcscpy_s(m_NotifyIconData.szTip,sizeof(m_NotifyIconData.szTip)/sizeof(m_NotifyIconData.szTip[0]),
			pszTip);
		m_NotifyIconData.uFlags=NIF_TIP;
		m_NotifyIconData.uID=uID;
		return ::Shell_NotifyIcon(NIM_MODIFY,&m_NotifyIconData);
	}
	BOOL CULTrayIcon::ShowBalloon(UINT uID,TCHAR* pszInfoTitle,TCHAR* pszInfo,DWORD dwInfoFlags)
	{
		m_NotifyIconData.uFlags=NIF_INFO;
		if(pszInfoTitle)
			_tcscpy_s(m_NotifyIconData.szInfoTitle,
				sizeof(m_NotifyIconData.szInfoTitle)/sizeof(m_NotifyIconData.szInfoTitle[0]),
				pszInfoTitle);
		if(pszInfo)
			_tcscpy_s(m_NotifyIconData.szInfo,
				sizeof(m_NotifyIconData.szInfo)/sizeof(m_NotifyIconData.szInfo[0]),
				pszInfo);
		m_NotifyIconData.dwInfoFlags=infoFlags;
		m_NotifyIconData.uID=uID;
		return ::Shell_NotifyIcon(NIM_MODIFY,&m_NotifyIconData);
	}

	BOOL CULTrayIcon::DeleteIcon(UINT uID)
	{
		m_NotifyIconData.uID=uID;
		return ::Shell_NotifyIcon(NIM_DELETE,&m_NotifyIconData);
	}
}