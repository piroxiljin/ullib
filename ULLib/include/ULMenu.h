///\file ULMenu.h
///\brief Заголовочный файл класса обёртки для меню(24.10.2007)
#pragma once
#ifndef __MENU__H_
#define __MENU__H_
#include <windows.h>
namespace ULWnds
{
	namespace ULControls
	{
		///\class CULMenu
		///\brief Класс обёртка для меню(24.10.2007)
		class CULMenu
		{
		public:
			HMENU m_hMenu;
		public:
			///\brief Конструктор
			CULMenu():m_hMenu(NULL){};
			///\brief Конструктор
			CULMenu(HMENU hMenu):m_hMenu(hMenu){};
			///\brief Деструктор
			virtual ~CULMenu(){};
			///\brief Для подстановки объекта класса там где требуется 
			///только хендл окна
			inline operator HMENU() const{return m_hMenu;};
		//==================inline functions============================
			///\brief Создаёт меню
			///\return TRUE в случае успеха
			inline BOOL CreateMenu()
				{return ((m_hMenu=::CreateMenu())!=NULL);}
			///\brief Создаёт выпадающее меню
			///\return TRUE в случае успеха
			inline BOOL CreatePopupMenu()
				{return ((m_hMenu=::CreatePopupMenu())!=NULL);}
			///\brief  добавляет пункт меню
			///\param uFlags - флаг для создания меню(для строки MF_STRING)
			///\param uIDNewItem - ID пункта меню
			///\param lpNewItem - для MF_STRING строка
			///	для MF_BITMAP ресурс битмапа
			///\return TRUE в случае успеха
			inline BOOL AppendMenu(UINT uFlags,UINT_PTR uIDNewItem,LPCTSTR lpNewItem)
				{return ::AppendMenu(*this,uFlags,uIDNewItem,lpNewItem);}
			///\brief  добавляет пункт меню(ДОПИСАТЬ!!!)
			///\param uFlags - флаг для создания меню
			///\param uIDNewItem - ID пункта меню
			///\return TRUE в случае успеха
			inline BOOL AppendOwnerDrawMenu(UINT uFlags,UINT_PTR uIDNewItem)
				{return ::AppendMenu(*this,uFlags|MF_OWNERDRAW,uIDNewItem,(LPTSTR)this);}
			///\brief Показывает всплывающее меню
			///\param uFlags - Фла или набор флагов выравнивания относительно опорной точки
			///\param pt - опорная точка
			///\param hWnd - окно владелец меню
			///\return TRUE в случае успеха
			inline BOOL TrackPopupMenu(UINT uFlags,POINT pt,HWND hWnd)
				{return ::TrackPopupMenu(*this,uFlags,pt.x,pt.y,0,hWnd,NULL);}
			///\brief Показывает всплывающее меню
			///\param uFlags - Фла или набор флагов выравнивания относительно опорной точки
			///\param pt - опорная точка
			///\param hWnd - окно владелец меню
			///\param lptpm - указатель на структуру, содержащая область, которую перекрывает меню
			///\return TRUE в случае успеха		
			inline BOOL TrackPopupMenuEx(UINT uFlags,POINT pt,HWND hWnd,LPTPMPARAMS lptpm)
				{return ::TrackPopupMenuEx(*this,uFlags,pt.x,pt.y,hWnd,lptpm);}
			///\brief уничтожает меню
			///\return TRUE в случае успеха
			inline BOOL DestroyMenu()
				{return ((m_hMenu)?::DestroyMenu(m_hMenu):FALSE);};
			///\brief Возвращает подменю, который входит в состав текущего меню
			///\return хендл подменю в случае успеха иначе NULL
			inline HMENU GetSubMenu(int nPos)
				{return ::GetSubMenu(*this,nPos);}
			///\brief Загружает меню из ресурсов
			///\param hInstance - хэндл модуля, в котором хранится ресурс
			///\param lpMenuName - имя меню
			///\return TRUE в случае успеха
			inline BOOL LoadMenu(HINSTANCE hInstance,LPCTSTR lpMenuName)
				{return ((m_hMenu=::LoadMenu(hInstance,lpMenuName))!=NULL);}
			///\brief отсоединяет класс меню от хендла
			///\return хендл меню
			inline HMENU Detach()
				{HMENU hTmp=m_hMenu;m_hMenu=NULL;return hTmp;}
		};
	}
}
#endif //__MENU__H_