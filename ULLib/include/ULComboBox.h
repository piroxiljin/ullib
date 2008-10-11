///\file ULComboBox.h 
///\brief фаил объ€влени€ класса лист контрола
#ifndef _ULCOMBOBOX_H__
#define _ULCOMBOBOX_H__
#include "ULSubClass.h"
#include "commctrl.h"

namespace ULWnds
{
	namespace ULControls
	{
		///\class CULComboBox
		///\brief класс комбобокса
		class CULComboBox:
			public ULWnds::CULSubClass
		{
		public:
			///\brief  онструктор
			CULComboBox();
			///\brief ‘ункци€ дл€ создани€ листконтрола
			///\param hParentWnd - хендл родительского окна
			///\param uID - ID листконтрола
			///\param x,y - координата листконтрола
			///\param cx,cy - размер листконтрола
			///\param dwStyle - стиль листконтрола
			///\param dwStyleEx - расширенный стиль 
			///\return TRUE в случае успеха
			BOOL Create(HWND hParentWnd,UINT uID,int x,int y,int cx,int cy,DWORD dwStyle,DWORD dwStyleEx);
			///\brief добавл€ет строку в комбобокс
			///\param pszStr - строка
			///\return номер добавленой строки в случае успеха иначе CB_ERR или CB_ERRSPACE
			int AddString(LPCTSTR pszStr);
			///\brief прив€зывает данные к итему
			///\param nItem - номер итема
			///\param dwData - данные
			///\return TRUE  в случае успеха
			BOOL SetItemData(int nItem,DWORD dwData);
			///\brief возвращает данные прив€зыванные к итему
			///\param nItem - номер итема
			///\return даныне, в случае ошибке CB_ERR
			DWORD GetItemData(int nItem);
			///\brief выбирает строку из листа в комбобокс
			///\param nItem - выбираемый итем
			///\return индекс выбранного итема. если nItem не попадает в диапазон итемов, то CB_ERR 
			int SetCurSel(int nItem);
			///\brief получает номер выбранной строки в комбике
			///\return индекс выбранного итема. если ничего не выбрано, то  CB_ERR
			int GetCurSel();
			///\brief ”дал€ет все итемы
			void ResetContent();
			///\brief показывает/пр€чет листбокс
			///\param fShowIt - флаг (показывает/пр€чет)
			void ShowDropDown(BOOL fShowIt);
			///\brief ¬озвращает информациб о комбобоксе
			///\param pcbi - указатель на экземпл€р структуры с информацией
			///\return TRUE в случае успеха
			BOOL GetComboBoxInfo(PCOMBOBOXINFO pcbi);
		};
	}
}

#endif //_ULCOMBOBOX_H__