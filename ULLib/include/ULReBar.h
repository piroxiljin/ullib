///\file ULReBar.h
///\brief «аголовочный файл класса ребара(11.08.2007)
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
		///\brief  ласс ребара(11.08.2007)
		class CULRebar:public CULSubClass
		{
		public:
			///\brief  онструктор
			CULRebar();
			///\brief  онструктор копировани€
			CULRebar(CULRebar	&);
			///\brief ƒеструктор
			virtual ~CULRebar();
			///\brief оператор копировани€
			void operator=(CULRebar&);
			///\brief Ќабор флагов дл€ размещени€ ребара по кра€м родител€
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
			///\brief ‘унки€ создани€ ребара
			///\param hParentWnd - хендл родител€
			///\param dwID - идентификатор
			///\param afFlag - флаг размещени€
			///\param dwStyle - свойства
			///\return TRUE в случае успеха
			BOOL Create(HWND hParentWnd,DWORD dwID,enAlignFlags afFlag,DWORD dwStyle=
				WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPSIBLINGS|
				WS_CLIPCHILDREN|RBS_VARHEIGHT|CCS_NODIVIDER|RBS_AUTOSIZE);
			///\brief ‘унки€ вставки новой клиентской секции 
			///\param nInto - позици€ вставки
			///\param hClientWnd-хендл клиента
			///\param szName-им€ клиентской секции
			///\param hBitmap-фонова€ картинка
			///\param wID - идентификатор банда
			///\param pszClient - размер клиента
			///\param dwStyle=свойства
			///\return TRUE в случае успеха
			///\note ≈сли установлен стиль RBBS_USECHEVRON, то необходимо \n
			///\ установить размер банда при котором будет по€вл€тьс€ шеврон \n
			///\ и в lParam банда занести указатель на класс ULWnds::ULBars::CULToolBar, \n
			///\ который устанавливает€ в банд
			BOOL InsertBand(int nInto,HWND hClientWnd,TCHAR* szName,HBITMAP hBitmap,
				WORD wID=0,SIZE* pszClient=NULL,
				DWORD dwStyle=RBBS_GRIPPERALWAYS|RBBS_FIXEDBMP|RBS_BANDBORDERS|RBBS_CHILDEDGE);
			///\brief ‘унки€ вставки новой клиентской секции 
			///\param nInto - позици€ вставки
			///\param hClientWnd-хендл клиента
			///\param szName-им€ клиентской секции
			///\param clrFore-цвет подписи szName
			///\param clrBack-цвет фона
			///\param wID - идентификатор банда
			///\param pszClient - размер клиента
			///\param dwStyle=свойства
			///\return TRUE в случае успеха
			BOOL InsertBand(int nInto,HWND hClientWnd, TCHAR* szName,	COLORREF clrFore, COLORREF clrBack,
				WORD wID=0,SIZE* pszClient=NULL,
				DWORD dwStyle= RBBS_GRIPPERALWAYS|RBBS_CHILDEDGE|RBBS_USECHEVRON);
			///\brief ”бирает все клиентские секции с ребара
			///\param numBand - номер банда
			///\return TRUE в случае успеха
			BOOL DeleteBand(int numBand);
			/*!\brief »змен€ет размер ребара по ширине или высоте родител€
					в зависимости от местоположени€
			¬ставить в обработчик WM_SIZE окна родител€ */
			void AutoSize();
			///\brief возвращает число добавленых бандов
			///\return число добавленых бандов
			int GetBandCount()
				{return (int)SendMessage(RB_GETBANDCOUNT);}
			///\brief возвращает информацию о банде
			///\param nBand - номер банда
			///\param lprbbi - указатель на структуру банда
			///\return TRUE  в случае успеха
			BOOL GetBandInfo(int nBand,LPREBARBANDINFO lprbbi)
				{return (SendMessage(RB_GETBANDINFO,(WPARAM)nBand,(LPARAM)lprbbi)!=0);}
			///\brief заносит информацию о банде
			///\param nBand - номер банда
			///\param lprbbi - указатель на структуру банда
			///\return TRUE  в случае успеха
			BOOL SetBandInfo(int nBand,LPREBARBANDINFO lprbbi)
				{return (SendMessage(RB_SETBANDINFO,(WPARAM)nBand,(LPARAM)lprbbi)!=0);}
			///\brief минимизировать банд
			///\param nBand - номер банда
			void MinimizeBand(int nBand)
				{SendMessage(RB_MINIMIZEBAND,(WPARAM)nBand);}
			///\brief максимизировать банд
			///\param nBand - номер банда
			void MaximizeBand(int nBand)
				{SendMessage(RB_MAXIMIZEBAND,(WPARAM)nBand);}
		protected:
			virtual LRESULT OnChevronPushed(LPARAM);
		};
	}
}
#endif //__UL_ULREBAR_H__