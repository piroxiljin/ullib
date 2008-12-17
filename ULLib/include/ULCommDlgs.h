///\file ULCommDlgs.h
///\brief Заголовочный файл классов стандартных диалоговых окон(02.01.2007)
#pragma once
#ifndef __UL_COMMDLG_H__
#define __UL_COMMDLG_H__
#include "ULDlg.h"
#include "ULOther.h"

namespace ULWnds
{
	namespace ULDlgs
	{
		///\namespace ULCommDlgs
		///\brief Пространство имён классов стандартных диалогов
		namespace ULCommDlgs
		{
			///\class CULCommDlg
			///\brief класс родитель - заглушка для стандартных диалогов
			class CULCommDlg:
				public ULWnds::ULDlgs::CULDlg
			{
			private:
				///\brief Заглушка для ULWnds::ULDlgs::CULDlg::Create
				HWND Create(short /*idTempl*/,	
					HWND /*hParentHWND=NULL*/)
				{return NULL;}
			protected:
				///\brief Функция окна
				static LRESULT WndProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
			public:
				///\brief Конструктор
				CULCommDlg();
				///\brief Деструктор
					virtual ~CULCommDlg(){};
			};
			///\class CULColorDlg
			///\brief Класс Выбора цвета
			class CULColorDlg:
				public CULCommDlg
			{
			public:
				///\brief Структура для организации диалога выбора цвета
				CHOOSECOLOR m_cc;
				///\brief Массив спец-цветов
				COLORREF m_acrCustClr[16]; 
			public:
				///\brief Конструктор
				///\param clrInit - цвет поумолчанию
				///\param dwFlags - флаги для огранизации диалога
				explicit CULColorDlg(COLORREF clrInit = 0,
					DWORD dwFlags=CC_RGBINIT|CC_ANYCOLOR|CC_ENABLEHOOK);
				///\brief Деструктор
				virtual ~CULColorDlg();
				///\brief Создание модального диалога
				///\param idTempl - Шаблон диалога, если утановлен флаг CC_ENABLETEMPLATE
				///\param hParentWnd - Хендл родителя
				///\return Код возврата
				int CreateModal(short idTempl,HWND hParentWnd);	
				///\brief Возвращает массив спец - цветов 
				///\return массив спец - цветов 
				COLORREF* GetSavedCustomColors()
					{return &m_acrCustClr[0];}
				///\brief Возвращает выбранный цвет
				///\return выбранный цвет
				COLORREF GetColor()
					{return m_cc.rgbResult;}	
			};
			///\class CULFileDlg
			///\brief Диалога открытия/сохранения фаилов(недоработаный)
			class CULFileDlg:
				public CULCommDlg
			{
			protected:
				///\brief Флаг открытия/сохранения фаила
				BOOL m_fOpenFileDlg;
				///\brief Буфер для имени и пути фаила
				ULOther::CULStr m_strFile;
				///\brief Буфер для имени фаила
				ULOther::CULStr m_strFileTitle;
			public:
				///\brief структура открытия фаилов
				OPENFILENAME m_ofn;
			public:
				///\brief Конструктор
				///\param fOpenFileDlg - TRUE диалог отрытия фаила, FALSE диалог сохранения фаила
				///\param lpszDefExt - расширение фаила поумолчанию
				///\param lpszFileName - Имя фаила поумолчанию
				///\param dwFlags - флаги диалога открытия фаилов
				///\param lpszFilter - фильтр открытия фаилов
				///\param dwFilterIndex - индекс текущего выбранного фильтра
				explicit CULFileDlg(BOOL fOpenFileDlg,
					LPCTSTR lpszDefExt = NULL,
					LPCTSTR lpszFileName = NULL,
					DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT/*|OFN_ENABLEHOOK*/,
					LPCTSTR lpszFilter = NULL,
					DWORD dwFilterIndex=0);
				///\brief Деструктор
				virtual ~CULFileDlg(){};
				///\brief Создание модального диалога
				///\param idTempl - Шаблон диалога, если утановлен флаг CC_ENABLETEMPLATE
				///\param hParentWnd - Хендл родителя
				///\return Код возврата
				int CreateModal(short idTempl, HWND hParentWnd);
				///\brief Устанавливает разширение поумолчанию
				///\param lpszDefExt - буфер с расширение поумолчанию
				///\return Предыдущее значение расширения поумолчанию, иначе NULL
				LPCTSTR SetDefExt(LPCTSTR lpszDefExt);
				///\brief Возвращает раcширение поумолчанию
				///\return Расширения поумолчанию, иначе NULL
				LPCTSTR GetFileExt() 
					{return m_ofn.lpstrDefExt;}
				///\brief Возвращает выбранный фаил
				///\return Выбранный фаил, иначе NULL
				LPCTSTR GetFileTitle()
					{return m_ofn.lpstrFileTitle;}
				///\brief Возвращает выбранный фаил и путь
				///\return Выбранный фаил и путь, иначе NULL
				LPCTSTR GetFileName()
					{return m_ofn.lpstrFile;}
			};
		}
	}
}
#endif //__UL_COMMDLG_H__

/* 
CFindReplaceDialog
 Lets user initiate a find or replace operation in a text file.
 
CFontDialog
 Lets user specify a font.
 
CPrintDialog
 Lets user specify information for a print job.
*/