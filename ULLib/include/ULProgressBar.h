///\file ULProgressBar.h
///\brief заголовочный фаил класса обЄртки дл€ ProgressBar
#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__
#include "ULSubClass.h"
namespace ULWnds
{
	namespace ULControls
	{
		///\class CULProgressBar
		///\brief  ласс контрола прогрессбара
		class CULProgressBar:
			public ULWnds::CULSubClass
		{
		public:
			///\brief конструктор
			CULProgressBar();
			///\brief —оздаЄт прогрессбар
			///\param hParentWnd - хендл родительского окна
			///\param uID - ID слайдера
			///\param x,y - координата слайдера
			///\param cx,cy - размер слайдера
			///\param dwStyle - стиль слайдера
			///\param dwStyleEx - расширенный стиль 
			///\return TRUE в случае успеха
			BOOL Create(HWND hParentWnd,UINT uID,int x,int y,int cx,int cy,
				DWORD dwStyle=WS_CHILD|WS_VISIBLE,DWORD dwStyleEx=NULL);
			///\return ¬озвращает текущую позицию прогрессбара
			int GetPos();
			///\brief ¬озвращает диапазон прогрессбара
			///\param pnLower,pnUpper - указатели на нижнее и верхнее значение
			///\return TRUE в случае успеха
			BOOL GetRange(int* pnLower,int* pnUpper);
			///\brief устанавливает смещение от текущей позиции
			///\param nIncrement - смещение
			///\return предыдущее значение прогресса
			int DeltaPos(int nIncrement);
			///\brief 
			COLORREF SetBkColor(COLORREF clrNew);
			///\brief устанавливает новую абсолютную позицию
			///\param nPos - значение позиции
			///\return предыдуща€ позици€
			int SetPos(int nPos);
			///\brief установка диапазона
			///\param nLower,nUpper - нижний и верхний предел диапазона
			void SetRange(short nLower,short nUpper);
			///\brief установка диапазона 32х битными значени€ми
			///\param nLower,nUpper - нижний и верхний предел диапазона
			void SetRange32(int nLower,int nUpper);
			///\brief установка новой позиции
			///\param nStep - значение новой позиции
			///\return предыдуща€ позици€
			int SetStep(int nStep);
			///\brief смещение позиции на одну единицу
			///\return предыдуща€ позици€
			int StepIt();
		};
	}
}
#endif //__PROGRESSBAR_H__
