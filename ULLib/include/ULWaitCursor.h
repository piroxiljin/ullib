///\file ULWaitCursor.h 
///\brief фаил объ€влени€ класса курсора ожидани€
#include <windows.h>
namespace ULOther
{
	///\class CULWaitCursor
	///\brief класса курсора ожидани€
	class CULWaitCursor
	{
		///\brief хендл курсора ожидани€
		HCURSOR m_hWaitCursor;
		///\brief хендл предыдущего курсора
		HCURSOR m_hCursor;
	public:
		///\brief конструктор
		CULWaitCursor();
		///\brief деструктор
		~CULWaitCursor();
		///\brief функци€ дл€ востановлени€ начального курсора
		void Restore();
	};
}