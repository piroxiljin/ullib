///\file ULToolBar.h
///\brief Заголовочный файл класса тулбара(12.10.2007)
#pragma once
#ifndef __UL_ULTOOLBAR_H__
#define __UL_ULTOOLBAR_H__

#include <windows.h>
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#include "ULOther.h"
#include "ULSubClass.h"
#include "ULControls.h"
namespace ULWnds
{
	namespace ULBars
	{
		///\class CULToolBar
		///\brief Класс тулбара(12.10.2007)
		class CULToolBar: public CULSubClass
		{
		private:
			///\class CTBToolTip
			///\brief  класс для подсказки, чтоб выполнить обработку TTN_GETDISPINFO
			class CTBToolTip:public ULControls::CULToolTip
			{			
			public:
				CTBToolTip();
				virtual ~CTBToolTip();
				///\brief Указатель на текущий класс тулбара
				CULToolBar* m_pULToolBar;
			protected:
				///\brief Обработчик TTN_GETDISPINFO
				virtual LONG OnGetDispInfo(LPARAM);
			};
			///\brief Объект класса подсказаки
			CTBToolTip m_TBToolTip;
		protected:
			///\brief Cтруктура данных, которая несет необходимую информацию о кнопках
			///\param szToolTip - Тект подсказки
			///\param idCommand - ID команды
			///\param idMenu - ID контекстного меню для 
			///	кнопки(если btnStyle==BTNS_DROPDOWN)
			struct tagInfoButtons
			{
				TCHAR* szToolTip;
				UINT idCommand;	
				UINT idMenu;	
			};
			///\brief массив, который несет необходимую информацию о кнопках
			ULOther::CULArr<tagInfoButtons> m_pInfoButtons;
			///\brief Флаг,указывающий как размещен тулбар по краям родителя
			UINT m_afFlag;
			///\brief Ширина рисунка для кнопки
			int m_dxBitmap;
			///\brief Высота рисунка для кнопки
			int m_dyBitmap;
			///\brief m_tbStyle - стиль
			DWORD m_tbStyle;
		public:
			///\brief Конструктор
			CULToolBar(void);
			///\brief Деструктор
			virtual ~CULToolBar(void);
			///\brief Набор флагов для размещения тулбара по краям родителя
			///\param afTop - по верхнему краю
			///\param afBottom - по нижнему краю
			///\param afLeft - по левому краю
			///\param afRight - по правому краю
			///\param afNon - отстутствует соответствие
			enum enAlignFlags
			{
				afTop=CCS_TOP,				
				afBottom=CCS_BOTTOM,		
				afLeft=CCS_LEFT,			
				afRight=CCS_RIGHT,			
				afNon=CCS_NOPARENTALIGN		
			};
			///\brief Функция создания тулбара
			///\param hParentWndхэндл - родительского окна
			///\param tbID -ID тулбара
			///\param dxButton - ширина кнопок
			///\param dyButton - высота кнопок
			///\param dxBitmap - ширина картинок для кнопок
			///\param dyBitmap - высота картинок для кнопок
			///\param afFlag - положение относительно родителя
			///\param tbStyle - стиль
			///\param tbExStyle - расширенный стиль
			HWND Create(HWND hParentWnd,		
						UINT tbID,				
						int dxButton,			
						int dyButton,			
						int dxBitmap,			
						int dyBitmap,			
						UINT afFlag=afTop,	
						DWORD tbStyle=WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|
						TBSTYLE_AUTOSIZE|CCS_NODIVIDER,
						DWORD tbExStyle=TBSTYLE_EX_DRAWDDARROWS);
			///\brief Функция добавляет кнопку на тулбар
			///\param idCommand - ID контрола(кнопки)
			///\param btnState - состояние кнопки
			///\param btnStyle - стиль кнопки
			///\param szTTip - подсказка для кнопки
			///\param nBitmap - номер картинки для кнопки тулбара с лева направо и ресурса nID
			///\param nID - ID ресурса для картинки
			///\param hInst - HINSTANCE модуля ресурса
			///\param iString - подпись для кнопки
			///\param idMenu - ID контекстного меню для кнопки, если (btnStyle&BTNS_DROPDOWN)==BTNS_DROPDOWN)
			int AddButton(int idCommand,					
						BYTE btnState,						
						BYTE btnStyle,						
						TCHAR* szTTip,						
						int nBitmap,						
						UINT_PTR nID=IDB_STD_SMALL_COLOR,	
						HINSTANCE hInst=HINST_COMMCTRL,		
						INT_PTR iString=0,					
						int idMenu=0);						
			///\brief Функция добавляет кнопку на тулбар
			///\param idCommand - ID контрола(кнопки)
			///\param btnState - состояние кнопки
			///\param btnStyle - стиль кнопки
			///\param szTTip - подсказка для кнопки
			///\param nBitmap - номер картинки для кнопки тулбара с лева направо и ресурса nID
			///\param hBitmap - хендл картинки
			///\param iString - подпись для кнопки
			///\param idMenu - ID контекстного меню для кнопки, если (btnStyle&BTNS_DROPDOWN)==BTNS_DROPDOWN)
			int AddButton(int idCommand,	
						BYTE btnState,		
						BYTE btnStyle,		
						TCHAR* szTTip,		
						int nBitmap,		
						HBITMAP hBitmap,	
						INT_PTR iString=0,	
						int idMenu=0);	  	
			///\brief Функция вставляет кнопку в тулбар
			///\param nInto - позиция вставки
			///\param idCommand - ID контрола(кнопки)
			///\param btnState - состояние кнопки
			///\param btnStyle - стиль кнопки
			///\param szTTip - подсказка для кнопки
			///\param nBitmap - номер картинки для кнопки тулбара с лева направо и ресурса nID
			///\param nID - ID ресурса для картинки
			///\param hInst - HINSTANCE модуля ресурса
			///\param iString - подпись для кнопки
			///\param idMenu - ID контекстного меню для кнопки, если (btnStyle&BTNS_DROPDOWN)==BTNS_DROPDOWN)
			int InsertButton(int nInto,		
						int idCommand,		
						BYTE btnState,		
						BYTE btnStyle,		
						TCHAR* szTTip,		
						int nBitmap,  		
						UINT_PTR nID=IDB_STD_SMALL_COLOR,
						HINSTANCE hInst=HINST_COMMCTRL,	 
						INT_PTR iString=0,				 
						int idMenu=0);					 
			///\brief Функция вставляет кнопку в тулбар
			///\param nInto - позиция вставки
			///\param idCommand - ID контрола(кнопки)
			///\param btnState - состояние кнопки
			///\param btnStyle - стиль кнопки
			///\param szTTip - подсказка для кнопки
			///\param nBitmap - номер картинки для кнопки тулбара с лева направо и ресурса nID
			///\param hBitmap - хендл картинки
			///\param iString - подпись для кнопки
			///\param idMenu - ID контекстного меню для кнопки, если (btnStyle&BTNS_DROPDOWN)==BTNS_DROPDOWN)
			int InsertButton(int nInto,
						int idCommand,
						BYTE btnState,
						BYTE btnStyle,
						TCHAR* szTTip,
						int nBitmap,
						HBITMAP hBitmap,
						INT_PTR iString=0,
						int idMenu=0);
			///\brief Функция удаляет указанную кнопку
			int DeleteButton(int nButton/*!<Номер кнопки*/);
			/*!\brief Изменяет размер тулбара по ширине или высоте родителя
			в зависимости от местоположения
			с подгонкой ширины нулевой секции.
			Вставить в обработчик WM_SIZE окна родителя */
			void AutoSize();
			///\brief Функция возвращает колличество кнопок на тулбаре
			inline unsigned int GetButtonCount()
			{
				return (unsigned int)m_pInfoButtons.GetSize();
			};
      BOOL GetItemRect(int nItem,RECT* lpRect)
      {return (BOOL)SendMessage(TB_GETITEMRECT,(WPARAM)nItem,(LPARAM)lpRect);}
		protected:
			///\brief Функция обработчик WM_WINDOWPOSCHANGING
			virtual LRESULT OnWindowPosChanging(WPARAM,LPARAM);
			///\brief Обработчик TBN_DROPDOWN
      ///\bug переписать так чтоб меню можно было модифицировать
			virtual LRESULT OnDropDown(LPARAM);
		};
	}
}
#endif //__UL_ULTOOLBAR_H__
