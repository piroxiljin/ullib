///\file ULTrayIcon.h
///\brief заголовочный фаил класса иконки в трее
#pragma once

#ifndef _ULTRAYICON_H__
#define _ULTRAYICON_H__

#include <windows.h>
#include <tchar.h>
namespace ULOther
{
	///\class CULTrayIcon
	///\brief класс иконки в трее
	class CULTrayIcon
	{
	protected:
		NOTIFYICONDATA m_NotifyIconData;
		UINT m_nIconCount;
	public:
		///\brief конструктор
		CULTrayIcon(void);
		///\brief деструктор
		~CULTrayIcon(void);
		///\brief Инициализирует данные
		///\param hWnd - хендл окна, к которому будет привязана иконка
		///\param uCallbackMessage - идентификатор сообщения посылаемое от иконки
		///\return TRUE в случае успеха
		BOOL Create(HWND hWnd,UINT uCallbackMessage);
		///\brief функция добавляет иконку в трэй
		///\param hIcon - хендл иконки
		///\return идентификатор иконки в случае успеха, иначе 0
		UINT AddIcon(HICON hIcon);
		///\brief Функция изменяет иконку в трее
		///\param uID - идентификатор иконки 
		///\return TRUE в случае успеха
		BOOL ChangeIcon(UINT uID,HICON hIcon);
		///\brief фунция задаёт строку подсветки иконки
		///\param uID - идентификатор иконки 
		///\param pszTip - строка 
		///\return TRUE в случае успеха
		BOOL SetIconTip(UINT uID,TCHAR* pszTip);
		///\brief Функия показывает балон с ссобщением
		///\param uID - идентификатор иконки 
		///\param pszInfoTitle - заголовок сообщения
		///\param pszInfo - сообщение
		///\param infoFlags - тип иконки
		///\return TRUE в случае успеха
		BOOL ShowBalloon(UINT uID,TCHAR* pszInfoTitle,TCHAR* pszInfo,DWORD dwInfoFlags);
		///\brief Функция удаляет иконку из трея
		///\param uID - идентификатор иконки 
		///\return TRUE в случае успеха
		BOOL DeleteIcon(UINT uID);
	};
}
#endif //_ULTRAYICON_H__