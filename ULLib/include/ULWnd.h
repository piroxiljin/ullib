///\file ULWnd.h
///\brief Заголовочный файл класса root окна(24.10.2007)
#pragma once
#ifndef __ULWND_H__
#define __ULWND_H__

#include <windows.h>
#include "ULMessageMap.inl"

namespace ULWnds
{
	///\class CULWnd
	///\brief Класс root для всех дочерних окон(24.10.2007)
	class CULWnd
	{
	protected:
		///\brief Функция окна
		static LRESULT WndProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam);
	public:
		///\brief Конструктор
		CULWnd(void);
		///\brief Конструктор копирования
		CULWnd(CULWnd& Wnd);
		///\brief Конструктор 
		CULWnd(HWND hwnd);
		///\brief Десруктор
		virtual ~CULWnd(void);
		///\brief Объект класса добавления и обработки сообщений
		///сообщения добавляются в конструкторе класса
		CULMessageMap<CULWnd> MessageMap;
		///\brief Функция для получения класса окна по его хендлу,
		///если окно создовалось при помощи этого класса,
		///т.к.в обработчике WM_CREATE или WM_INITDIALOG в GWL_USERDATA помещается this
		///\param hWnd Хэндл окна
		///\return указатель на класс окна
		static CULWnd* FromHandle(HWND hWnd)
			{return (CULWnd *)(LONG_PTR)::GetWindowLong(hWnd, GWL_USERDATA);}
		///\brief Функция окна необходимая для сабклассирования дочерними контролами
		WNDPROC m_lpSubClassWndProc;
		///\brief функция вызываемая перед обработкой сообщения
		///\необходима инициализация GetApp()->MessageMap.InitializePreTranslateMessage (рекомендуется вызывать в конструкторе)
		///\после того как функция будет не нужна, её необходимо освободить
		///\ GetApp()->MessageMap.UnInitializePreTranslateMessage (рекомендуется вызывать в деструкторе)
		///\param pMsg - указатель на структуру несущую информацию о сообщении
		///\return TRUE для продолжении обработкии сообщения, FALSE для прекращения обработки сообщения
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		///\brief хэндл текущего окна 
		HWND m_hWnd;
		///\brief хэндл родительского окна
		HWND m_hParentWnd;
		///\brief Для подстановки объекта класса там где требуется 
		///только хендл окна
		inline operator HWND() const{return m_hWnd;}
		///\brief Оператор копирования
		virtual void operator = (CULWnd&);
	//==================inline functions============================
		///\brief Дефолтовая функция окна
		inline virtual LRESULT DefWindowProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
			{return ::DefWindowProc(*this, uMsg, wParam, lParam);};
		///\brief Вызов функции окна
		inline virtual LRESULT CallWindowProc(UINT uMsg,WPARAM wParam,LPARAM lParam)
			{return ::CallWindowProc(m_lpSubClassWndProc,*this, uMsg, wParam, lParam);}	
		///\brief Получение текста окна
		///\param lpString - строка
		///\param nMaxCount - максимальная лдина строки
		///\return колличество записанных символов в lpString
		inline int GetWindowText(LPTSTR lpString,int nMaxCount)
			{return ::GetWindowText(*this,lpString,nMaxCount);}
		///\brief Получение длины текста окна
		///\return колличество символов в окне
		inline int GetWindowTextLength()
			{return ::GetWindowTextLength(*this);}
		///\brief Установка текста в окно
		///\param lpString - Текст
		///\return TRUE в случае успеха
		inline BOOL SetWindowText(LPTSTR lpString)
			{return ::SetWindowText(*this,lpString);}
		///\brief отправка сообщения в окно
		///\param Msg - Сообщение
		///\param wParam - Параметр 1
		///\param lParam - Параметр 2
		///\return ответ обработчика сообщения
		inline LRESULT SendMessage(UINT Msg,WPARAM wParam=0,LPARAM lParam=0)
			{return ::SendMessage(*this,Msg,wParam,lParam);}
		///\brief постановка сообщения в окна в конец очереди цикла сообщений
		///\param Msg - Сообщение
		///\param wParam - Параметр 1
		///\param lParam - Параметр 2
		///\return TRUE в случае успеха
		inline BOOL PostMessage(UINT Msg,WPARAM wParam=0,LPARAM lParam=0)
			{return ::PostMessage(*this,Msg,wParam,lParam);}
		///\brief Установка фокуса
		///\return возвращает фокус предыдущего окна
		inline HWND SetFocus()
			{return ::SetFocus(*this);}
		///\brief Уничтожает окно
		///\return TRUE в случае успеха
		inline BOOL DestroyWindow()
			{return ((m_hWnd!=NULL)?::DestroyWindow(*this):FALSE);}
		///\brief Делает окно активным
		///\return Пердыдущее активное окно
		inline HWND SetActiveWindow()
			{return ::SetActiveWindow(*this);}
		///\brief Помещает окно на передний план и делает его активным
		///\return TRUE в случае успеха
		inline BOOL SetForegroundWindow()
			{return ::SetForegroundWindow(*this);}
		///\brief Возвращает родителя
		///\return Хэндл родителя
		inline HWND GetParent()
			{return ::GetParent(*this);};
		///\brief Устанавливает нового родителя
		///\return Хэндл предыдущего родителя
		inline HWND SetParent(HWND hWndNewParent)
			{m_hParentWnd=hWndNewParent;return ::SetParent(*this,hWndNewParent);};
		///\brief Изменяет состояние видимости окна
		///\param nCmdShow - Состояние
		///\return TRUE в случае предыдущей видимости, иначе FALSE
		inline BOOL ShowWindow(int nCmdShow)
			{return ::ShowWindow(*this,nCmdShow);};
		///\brief Обновляет окно
		///\return TRUE в случае предыдущей видимости, иначе FALSE
		inline BOOL UpdateWindow()
			{return ::UpdateWindow(*this);}
		///\brief Изменяет позицию окна
		///\param hWndInsertAfter - положение окна по Z координате
		///возможны HWND_BOTTOM,HWND_NOTOPMOST,HWND_TOP,HWND_TOPMOST
		///\param X,Y - Координаты
		///\param cx,cy - Размеры
		///\param uFlags - флаг отображения
		///\return TRUE в случае успеха
		inline BOOL SetWindowPos(HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags)
			{return ::SetWindowPos(*this,hWndInsertAfter,X,Y,cx,cy,uFlags);}
		///\brief "Изменяет multiple-window – position structure"
		///\param hWinPosInfo - "Handle to a multiple-window – position structure"
		///	содержащая информацию об одной или более структур
		///\param hWndInsertAfter - положение окна по Z координате
		///возможны HWND_BOTTOM,HWND_NOTOPMOST,HWND_TOP,HWND_TOPMOST
		///\param x,y - Координаты
		///\param cx,cy - Размеры
		///\param uFlags - флаг отображения
		///\return "Изменяет multiple-window – position structure"
		inline HDWP DeferWindowPos(HDWP hWinPosInfo,HWND hWndInsertAfter,
			int x,int y,int cx,int cy,UINT uFlags)
			{return ::DeferWindowPos(hWinPosInfo,*this,hWndInsertAfter,x,y,cx,cy,uFlags);};
		///\brief Перемецает окно
		///\param X,Y - Координаты
		///\param nWidth,nHeight - Размеры
		///\param fRepaint - флаг наличия перерисовки после перемещения
		///\return TRUE в случае успеха
		inline BOOL MoveWindow(int X,int Y,int nWidth,int nHeight,BOOL fRepaint)
			{return ::MoveWindow(*this,X,Y,nWidth,nHeight,fRepaint);}
		///\brief Возвращает инфрмацию об окне
		///\param nIndex - ID поля возвращаемой информации
		///\param запрашиваемая информация
		inline LONG GetWindowLong(int nIndex)
			{return ::GetWindowLong(*this,nIndex);}
		///\brief устанавливает новое значение в поле окна
		///\param nIndex- ID поля 
		///\param dwNewLong - новое значение
		///\return предыдущее значение
		inline LONG SetWindowLong(int nIndex,LONG dwNewLong)
			{return ::SetWindowLong(*this,nIndex,dwNewLong);}
		///\brief Модифицирует стиль окна
		///\param dwRemStyle - Убираемый стиль
		///\param dwAddStyle - Устанавливаемый стиль
		///\param uFlags - Флаг обновления окна
		///\return TRUE в случае успеха
		inline BOOL ModifySyle(DWORD dwRemStyle,DWORD dwAddStyle,UINT uFlags=SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED)
		{	
			SetWindowLong(GWL_STYLE,
				(GetWindowLong(GWL_STYLE)&~dwRemStyle)|dwAddStyle);
			return SetWindowPos(NULL,0,0,0,0,uFlags);
		}
		///\brief Модифицирует расширенный стиль окна
		///\param dwRemStyleEx - Убираемый стиль
		///\param dwAddStyleEx - Устанавливаемый стиль
		///\param uFlags - Флаг обновления окна
		///\return TRUE в случае успеха
		inline BOOL ModifySyleEx(DWORD dwRemStyleEx,DWORD dwAddStyleEx,UINT uFlags=SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED)
		{	
			SetWindowLong(GWL_EXSTYLE,
				(GetWindowLong(GWL_EXSTYLE)&(~dwRemStyleEx))|dwAddStyleEx);
			return SetWindowPos(NULL,0,0,0,0,uFlags);
		}
		///\brief Функция для получения размера клиентской области
		///\param lpRect - Указатель на получаемый размер
		///\return TRUE в случае успеха
		inline BOOL GetClientRect(LPRECT lpRect)
			{return ::GetClientRect(*this,lpRect);}
		///\brief Функция для получения расположения окна
		///\param lpRect - Указатель на получаемое расположение
		///\return TRUE в случае успеха
		inline BOOL GetWindowRect(LPRECT lpRect)
			{return ::GetWindowRect(*this,lpRect);}
		///\brief Устанавливает шрифт окна
		///\param hFont - Хэндл шрифта
		///\param fRedraw - Перерисует себя если TRUE
		inline void SetFont(HFONT hFont,BOOL fRedraw)
			{SendMessage(WM_SETFONT,(WPARAM)hFont,(LPARAM)fRedraw);}
		///\brief Обновляет указанный прямоугольник на окне
		///\param lpRect - прямоугольник для обновления, если NULL, то обновиться всё окно
		///\param fErase - при TRUE стерает содержимое
		///\return TRUE в случае успеха
		inline BOOL InvalidateRect(CONST RECT *lpRect=NULL,BOOL fErase=FALSE)
			{return ::InvalidateRect(*this,lpRect,fErase);}
		///\brief Выводит диалоговое окно
		///\param lpText - тект
		///\param lpCaption - заголовок
		///\param uType - тип окна
		///\return  
		///	IDABORT Abort button was selected. 
		///	IDCANCEL Cancel button was selected. 
		///	IDCONTINUE Continue button was selected. 
		///	IDIGNORE Ignore button was selected. 
		///	IDNO No button was selected. 
		///	IDOK OK button was selected. 
		///	IDRETRY Retry button was selected. 
		///	IDTRYAGAIN Try Again button was selected. 
		///	IDYES Yes button was selected. 
		inline int MessageBox(LPCTSTR lpText,LPCTSTR lpCaption,UINT uType)
			{return ::MessageBox(*this,lpText,lpCaption,uType);}
		///\brief Возвращает контекст окна
		///\return контекст окна
		inline HDC GetDC()
			{return ::GetDC(*this);}
		///\brief Задаёт регион для окна
		///\param hRgn - хэндл региона
		///\param fRedraw - флаг перерисовки после установки региона
		///\return TRUE в случае успеха
		inline BOOL SetWindowRgn(HRGN hRgn,BOOL fRedraw)
			{return ::SetWindowRgn(*this,hRgn,fRedraw);}
		///\brief Возвращает регион для окна
		///\param hRgn - хэндл возвращаемого региона
		///\return 
		///	NULLREGION The region is empty. 
		///	SIMPLEREGION The region is a single rectangle. 
		///	COMPLEXREGION The region is more than one rectangle. 
		///	ERROR The specified window does not have a region, 
		///	or an error occurred while attempting to return the region.  
		inline int GetWindowRgn(HRGN hRgn)
			{return ::GetWindowRgn(*this,hRgn);}
		///\brief Переносит окно на вперёд по Z координате
		///\return TRUE в случае успеха
		inline BOOL BringWindowToTop()
			{return ::BringWindowToTop(*this);}
		///\brief Переводит координату относительно текущего окна в абсолютную координату экрана
		///\param lpPoint - указатель на координату
		///\return TRUE в случае успеха
		inline BOOL ScreenToClient(LPPOINT lpPoint)
			{return ::ScreenToClient(*this,lpPoint);}
		///\brief Осуществляет перерисовку окна
		///\param lprcUpdate - перерисовываемый прямоугольник. Если NULL, то перерисовывается весь прямоугольник.
		///\param hrgnUpdate - перерисовываемый регион. Если NULL, то перерисовывается весь регион.
		///\param flags - флпг перерисовки
		///\return TRUE в случае успеха
		inline BOOL RedrawWindow(CONST RECT *lprcUpdate,HRGN hrgnUpdate,UINT flags)
			{return ::RedrawWindow(*this,lprcUpdate,hrgnUpdate,flags);}
		///brief активирует/дезактивирует перерисовку окна
		///\param fRedraw - Флаг активации
		///\return TRUE в случае успеха
		inline BOOL SetRedraw(BOOL fRedraw)
			{return (SendMessage(WM_SETREDRAW,WPARAM(fRedraw))!=0);}
		///\brief "включает/выключает" окно
		///\param fEnable - флаг включения/выключения
		///\return TRUE в случае успеха
		inline BOOL EnableWindow(BOOL fEnable)
			{return ::EnableWindow(*this,fEnable);}
		///\brief Установка таймера для окна
		///\param nIDEvent - ID таймера, используется для изменения времени срабатывания
		///\param uElapse - время срабатывания в мс
		///\return ID таймера
		inline UINT_PTR SetTimer(UINT_PTR nIDEvent,UINT uElapse)
			{return ::SetTimer(*this,nIDEvent,uElapse,NULL);}
		///\brief Уничтожает выбранный таймер
		///\param uIDEvent - ID таймера, который вернул SetTimer
		///\return TRUE в случае успеха
		BOOL KillTimer(UINT_PTR uIDEvent)
			{return ::KillTimer(*this,uIDEvent);}
		///\brief Устанавливает меню для окна
		///\param hMenu - хендл меню
		///\return TRUE в случае успеха
		BOOL SetMenu(HMENU hMenu)
			{return ::SetMenu(*this,hMenu);}
		///\brief Получает хендл на дочерний контрол
		///\param nIDDlgItem - ID контрола
		///\return Хендл контроа
		inline HWND GetDlgItem(int nIDDlgItem)
			{return ::GetDlgItem(*this,nIDDlgItem);}
		///\brief Проверяет видимость окна
		///\return TRUE если видимо
		inline BOOL IsWindowVisible()
			{return ::IsWindowVisible(*this);}
		///\brief Определяет существует ли окно
		///\return TRUE если существует
		inline BOOL IsWindow()
			{return ::IsWindow(*this);}
		///\brief Переводит координаты клиента в экранные
		///\param lpPoint - структура с координатой
		///\return FALSE в случае неудачи
		BOOL ClientToScreen(LPPOINT lpPoint)
			{return ::ClientToScreen(*this,lpPoint);}
		///\brief Устанавливает иконку на окно
		///\param hIcon - хендл иконjyrb
		///\param fBig - если TRUE, то будет установлена большая иконка, иначе маленькая
		///\return хендл предыдущей установленной иконки в случае успеха, иначе NULL
		HICON SetIcon(HICON hIcon,BOOL fBig)
			{return (HICON)SendMessage(WM_SETICON,(WPARAM)hIcon,(LPARAM)((fBig)?ICON_BIG:ICON_SMALL));}
		///\brief Утанавливает прозрачность окна по а-каналу и/или по цветовому ключу
		///\param crKey - цветовой ключ, по по которому окно будет прозрачно
		///\param bAlpha - альфа-канал
		///\param  dwFlags - критерий работы функции по ключу(LWA_COLORKEY)
		///	и/или по альфаканалу(LWA_ALPHA)
		///\return FALSE в случае неудачи
	#if(_WIN32_WINNT >= 0x0500)
		BOOL SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,DWORD dwFlags)
			{return ::SetLayeredWindowAttributes(*this,crKey,bAlpha,dwFlags);}
	#endif
		///\brief отсоединяет класс окна от хендла
		///\return хендл окна
		inline HWND Detach()
			{HWND hTmp=m_hWnd;m_hWnd=NULL;return hTmp;}
		///\brief Функция заносит/изменяет свойство в списке свойств окна
		///\param lpString - имя свойства
		///\param hData - даннык
		///\return TRUE в случае успеха
		BOOL SetProp(LPTSTR lpString,HANDLE hData)
			{return ::SetProp(*this,lpString,hData);}
		///\brief Функция получает свойство из списка свойств окна
		///\param lpString - имя свойства
		///\return данные
		HANDLE GetProp(LPTSTR lpString)
			{return ::GetProp(*this,lpString);}
		///\brief сворачивает окно
		///\return TRUE в слуыае успеха
		BOOL CloseWindow()
			{return ::CloseWindow(*this);};
		///\brief возвращает меню окна
		///\return меню окна
		HMENU GetMenu()
			{return ::GetMenu(*this);}
		///\brief возвращает запрашиваемое окно
		///\param uCmd - параметр запроса
		///\return хендл запрашиваемого окна
		HWND GetWindow(UINT uCmd)
			{return ::GetWindow(*this,uCmd);}
		///\brief функция для изменения полей класса окна
		///\param nIndex - индекс поля
		///\param dwNewLong - значение поля
		///\return предыдущее значение
		DWORD SetClassLong(int nIndex,LONG dwNewLong)
			{return ::SetClassLong(*this,nIndex,dwNewLong);}
	};
}
#endif //__ULWND_H__