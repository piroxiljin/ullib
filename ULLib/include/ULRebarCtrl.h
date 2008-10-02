///\file ULRebarCtrl.h
///\brief Заголовочный файл класса ребара размещенного на плавающей панельке(31.08.2008)
#pragma once
#ifndef __UL_ULREBARCTRL_H__
#define __UL_ULREBARCTRL_H__
#include "ULRebar.h"
#include "ULWndCtrl.h"
namespace ULWnds
{
	namespace ULWndCtrls
	{
		///\class CULToolBarCtrl
		///\brief Класс тулбара размещенного на плавающей панельке(12.10.2007)
		class CULRebarCtrl :
			public CULWndCtrl
		{
		private:
			bool m_fAutoSize;
		protected:
			///\brief Непосредственно сам тулбар
			ULBars::CULRebar m_Rebar;
			///\brief Функция окна
			static LRESULT ClientWndProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
			///\brief Функция окна необходимая для сабклассирования дочерними контролами
			WNDPROC m_lpSubClassWndProc;
		public:
			//================================================
			///\brief Конструктор
			//================================================
			CULRebarCtrl(void);
				///\brief Конструктор копирования
			CULRebarCtrl(CULRebarCtrl&);
			///\brief Деструктор
			virtual ~CULRebarCtrl(void);
			///\brief оператор копирования
			void operator=(CULRebarCtrl&);
			///\brief Функция возвращает ссылку на тулбар
			inline ULBars::CULRebar& GetRebar(){return m_Rebar;};
			///\brief Функция создания тулбарконтрола
			///\param hParentWnd - хендл родителя(носителя)
			///\param tbID - идентификатор тулбара
			///\param nXPos,nYPos - позиция тулбарконтрола при создании в
			///	плавающем состоянии
			///\param dxButton,dyButton - размер кнопки тулбара
			///\param dxBitmap,dyBitmap - размер картинки для кнопки тулюара
			///\param dwDockedState - назначение стыковки на момент создания
			///\param fDocked - состояние стыковки на момент создания
			///\param tbStyle - стиль тулбара
			///\param tbExStyle - рачширенный стиль тулбара
			///\param dwDockingStyles - стили панели
			BOOL CreateRebarCtrl(HWND hParentWnd,
							int nXPos,
							int nYPos,
							DWORD dwDockedState);
		protected:
			///\brief Обработчик WM_SIZE
			virtual LRESULT OnSize(WPARAM nType,LPARAM point);
		};
	}
} 
#endif //__UL_ULREBARCTRL_H__
