///\file ULReBar.h
///\brief Заголовочный файл класса ребара(11.08.2007)
#pragma once
#ifndef __UL_ULREBAR_H__
#define __UL_ULREBAR_H__

#include <windows.h>
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#include "ULSubClass.h"
namespace ULWnds
{
	namespace ULBars
	{
		///\class CULRebar
		///\brief Класс ребара(11.08.2007)
		class CULRebar:public CULSubClass
		{
		public:
			///\brief Конструктор
			CULRebar();
			///\brief Деструктор
			virtual ~CULRebar();
			///\brief Набор флагов для размещения ребара по краям родителя
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
			}m_afFlag;
			///\brief Функия создания ребара
			///\param hParentWnd - хендл родителя
			///\param afFlag - флаг размещения
			///\param dwStyle - свойства
			HWND Create(HWND hParentWnd,enAlignFlags afFlag,DWORD dwStyle=
				WS_CHILD|WS_VISIBLE|WS_BORDER|/*WS_CLIPSIBLINGS|*/
				/*WS_CLIPCHILDREN|*/RBS_VARHEIGHT|CCS_NODIVIDER|RBS_AUTOSIZE);
			///\brief Функия вставки новой клиентской секции 
			///\param hClientWnd-хендл клиента
			///\param szName-имя клиентской секции
			///\param hBitmap-фоновая картинка
			///\param wID - идентификатор банда
			///\param pszClient - размер клиента
			///\param dwStyle=свойства
			BOOL InsertBand(HWND hClientWnd,TCHAR* szName,HBITMAP hBitmap,
				WORD wID=0,SIZE* pszClient=NULL,
				DWORD dwStyle=/*RBBS_GRIPPERALWAYS|*/RBBS_FIXEDBMP|/*RBS_BANDBORDERS|/*RBBS_BREAK|*/RBBS_CHILDEDGE);
			///\brief Функия вставки новой клиентской секции 
			///\param hClientWnd-хендл клиента
			///\param szName-имя клиентской секции
			///\param clrFore-цвет подписи szName
			///\param clrBack-цвет фона
			///\param wID - идентификатор банда
			///\param pszClient - размер клиента
			///\param dwStyle=свойства
			BOOL InsertBand(HWND hClientWnd, TCHAR* szName,	COLORREF clrFore, COLORREF clrBack,
				WORD wID=0,SIZE* pszClient=NULL,
				DWORD dwStyle= RBBS_GRIPPERALWAYS|RBBS_BREAK|RBBS_CHILDEDGE);
			///\brief Убирает все клиентские секции с ребара
			BOOL DeleteBand(int numBand);
			/*!\brief Изменяет размер ребара по ширине или высоте родителя
					в зависимости от местоположения
			Вставить в обработчик WM_SIZE окна родителя */
			void AutoSize();

		};
	}
}
#endif //__UL_ULREBAR_H__