///\file ULHotKey.h
///\brief «аголовочный файл класса обЄртки лд€ HOTKEY контрола(09.09.2007)
#pragma once
#ifndef __HOTKEY__H_
#define __HOTKEY__H_
#include "ULSubClass.h"
#include <commctrl.h>
namespace ULWnds
{
	namespace ULControls
	{
		///\class CULHotKey
		///\brief  ласс обЄртка лд€ EDIT контрола(16.07.2007)
		class CULHotKey:public CULSubClass
		{
		public:
			///\brief варианты запретов
			enum enCombInv
			{
				ciA=	HKCOMB_A,
				ciC=	HKCOMB_C,
				ciCA=	HKCOMB_CA,
				ciNone=	HKCOMB_NONE,
				ciS=	HKCOMB_S,
				ciSA=	HKCOMB_SA,
				ciSC=	HKCOMB_SC,
				ciSCA=	HKCOMB_SCA
			};
			///\brief варианты дополнительных гор€чих клавиш
			enum enModifierKey
			{
				mfAlt		=HOTKEYF_ALT,
				mfControl	=HOTKEYF_CONTROL,
				mfExt		=HOTKEYF_EXT,
				mfShift		=HOTKEYF_SHIFT
			};
			///\brief структура гор€чих клавиш
			///\param wHotkey - гор€чие клавиши упакованные в слово
			///\param hkStruct - разделенные гор€чие клавиши
			union unHotKey
			{
				WORD wHotkey;
				///\brief структура разделенных гор€чих клавиш
				///\param bVirtualKey - гор€ча€ клавиша
				///\param bModifierKey - дополнительна€ гор€ча€ клавиша
				struct tagHotKey
				{
					BYTE bVirtualKey;
					BYTE bModifierKey;
				}hkStruct;
			};
		public:
			///\brief  онструктор
			CULHotKey();
			///\brief ƒеструктор
			virtual ~CULHotKey();
			///\brief ‘ункци€ дл€ создани€ хотке€
			///\param hParentWnd - хендл родительского окна
			///\param uID - ID кнопки
			///\param x,y - координата кнопки
			///\param cx,cy - размер кнопки
			///\param dwStyle - стиль эдита
			///\param dwStyleEx - расштренный стиль эдита
			///\return TRUE в случае успеха
			BOOL Create(HWND hParentWnd,UINT uID,int x,int y,
				int cx,int cy,DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_TABSTOP,
				DWORD dwStyleEx=WS_EX_CLIENTEDGE);
		//==================inline functions============================
			///\brief возвращает текущую гор€чую клавишу
			///\return CULHotKey::unHotKey
			inline unHotKey GetHotKey()
			{	
				unHotKey HotKey;
				HotKey.wHotkey=(WORD)SendMessage(HKM_GETHOTKEY);
				return HotKey;
			}
			///\brief устанавливает гор€чую клавишу
			///\param HotKey - гор€ча€ клавиша
			inline void SetHotKey(unHotKey HotKey)
				{SendMessage(HKM_SETHOTKEY,(WPARAM)HotKey.wHotkey);}
			///\brief устанавливает гор€чую клавишу
			///\param bVirtualKey - гор€ча€ клавиша
			///\param bModifierKey - дополнительна€ клавиша
			inline void SetHotKey(BYTE bVirtualKey,BYTE bModifierKey)
				{SendMessage(HKM_SETHOTKEY,MAKELPARAM(bVirtualKey,bModifierKey));}
			///\brief устанавливает запреты на выбор гор€чей клавиши
			///\param bCombInv - варианты запретов
			///\param bModifierKey - дополнительна€ клавиша, котора€ добавитьс€ к запрещенной 
			inline void SetRules(BYTE bCombInv,BYTE bModifierKey)
				{SendMessage(HKM_SETHOTKEY,(WPARAM)bCombInv,(LPARAM)bModifierKey);}
		};
	}
}
#endif //__HOTKEY__H_