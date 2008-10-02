///\file ULToolBar.cpp
///\brief cpp файл класса тулбара(11.08.2007)
///\bug переписать OnDropDown
#include "..\..\ULLib\Include\ULToolbar.h"
#include "..\..\ULLib\Include\ULMenu.h"
#include "..\..\ULLib\Include\ULRes.h"
namespace ULWnds
{
	namespace ULBars
	{
		CULToolBar::CULToolBar(void):
			m_dxBitmap(0),
			m_dyBitmap(0)
		{
			MessageMap.AddMessage<CULToolBar>(WM_WINDOWPOSCHANGING,&CULToolBar::OnWindowPosChanging);
			MessageMap.AddReflectNotify<CULToolBar>(TBN_DROPDOWN,&CULToolBar::OnDropDown);
		};

		CULToolBar::~CULToolBar(void)
		{
		};

		HWND CULToolBar::Create(HWND hParentWnd,
						UINT tbID,//ID тулбара
						int dxButton,//ширина кнопки
						int dyButton,//высота кнопки
						int dxBitmap,//ширина картинки для кнопки
						int dyBitmap,//высота картинки для кнопки
						UINT afFlag,
						DWORD tbStyle,
						DWORD tbExStyle)
		{
			m_tbStyle=tbStyle;
			INITCOMMONCONTROLSEX icex;
			icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
			icex.dwICC  = ICC_BAR_CLASSES;
			InitCommonControlsEx(&icex);
		//==================================
			m_dxBitmap=dxBitmap;
			m_dyBitmap=dyBitmap;
			m_hParentWnd=hParentWnd;
			m_afFlag=afFlag;
			tbStyle|=afFlag;

			m_hWnd = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, 
				tbStyle, 0, 0, dxButton, dyButton, hParentWnd, 
				(HMENU)(INT_PTR)tbID, ULOther::ULGetResourceHandle(), NULL); 
			if(m_hWnd!=NULL)
			{
				SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0); 
				SendMessage(TB_SETEXTENDEDSTYLE , 0, tbExStyle ); 
			}
			//сабклассим тултип
			m_TBToolTip.m_pULToolBar=this;		
			m_TBToolTip.Attach((HWND)SendMessage(TB_GETTOOLTIPS));
			//сабклассируем тулбар
			return (Attach(m_hWnd))?m_hWnd:NULL;
		};

		int CULToolBar::AddButton(int idCommand,
						BYTE btnState,
						BYTE btnStyle,
						TCHAR* szTTip,
						int nBitmap,
						UINT_PTR nID,
						HINSTANCE hInst,
						INT_PTR iString,
						int idMenu)//ID контекстного меню для кнопки(если btnStyle==BTNS_DROPDOWN)
		{
		//========================добавление в массив m_InfoButtons===============
			ULOther::CULArr<tagInfoButtons> tmppInfoButtons(m_pInfoButtons.GetSize());
			m_pInfoButtons.Resize(m_pInfoButtons.GetSize()+1);
			if((btnStyle&BTNS_SEP)==0)
			{
				if((btnStyle&BTNS_DROPDOWN)!=0)
					m_pInfoButtons[m_pInfoButtons.GetSize()+1-1].idMenu=idMenu;
				else
					m_pInfoButtons[m_pInfoButtons.GetSize()-1].idMenu=0;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].szToolTip=szTTip;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].idCommand=idCommand;
			}
			else
			{
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].idMenu=0;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].szToolTip=NULL;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].idCommand=0;
			}
		//=========================================================================	
			btnState|=(m_afFlag&CCS_VERT)?TBSTATE_WRAP:0;
			TBBUTTON tbButtonsAdd={nBitmap, idCommand, 
				btnState,
				btnStyle,
		#if defined(_WIN32) | defined(_WIN64)
				{0},
		#endif
				/*dwData*/0, iString};

			TBADDBITMAP tb;
			int  stdidx;
			tb.hInst=(nID>IDB_HIST_LARGE_COLOR)?NULL:hInst;
			tb.nID = nID;

			if(nID>IDB_HIST_LARGE_COLOR)
			{
				HIMAGELIST himl=(HIMAGELIST)SendMessage(TB_GETIMAGELIST,0,0);
				stdidx=ImageList_AddMasked(himl,(HBITMAP)nID,RGB(192,192,192));
				SendMessage(TB_SETIMAGELIST,0,LPARAM(himl));
			}
			else
			{
				stdidx = (int)SendMessage(TB_ADDBITMAP, nBitmap, (LPARAM)&tb);
			}
			tbButtonsAdd.iBitmap +=stdidx;

			SendMessage(TB_SETBUTTONSIZE,0,(LPARAM)MAKELONG(m_dxBitmap,m_dyBitmap));
			SendMessage(TB_SETBITMAPSIZE,0,(LPARAM)MAKELONG(m_dxBitmap,m_dyBitmap));
			return (BOOL)SendMessage (TB_ADDBUTTONS,1,(LPARAM) &tbButtonsAdd);
		};

		int CULToolBar::AddButton(int idCommand,//ID контрола(кнопки)
						BYTE btnState,//состояние кнопки
						BYTE btnStyle,//стиль кнопки
						TCHAR* szTTip,//тултип для кнопки
						int nBitmap,//номер картинки для кнопки тулбара 
						HBITMAP hBitmap,//ID ресурса для картинки
						INT_PTR iString,//подпись для кнопки
						int idMenu)//ID контекстного меню для кнопки(если btnStyle==BTNS_DROPDOWN)
		{
			return AddButton(idCommand,btnState,btnStyle,szTTip,nBitmap,(INT_PTR)hBitmap,
				NULL,iString,idMenu);
		}

		int CULToolBar::InsertButton(int nInto,//куда вставить
						int idCommand,
						BYTE btnState,
						BYTE btnStyle,
						TCHAR* szTTip,
						int nBitmap,
						UINT_PTR nID,
						HINSTANCE hInst,
						INT_PTR iString,
						int idMenu)
		{
		//========================вставка в массив m_InfoButtons===============
			ULOther::CULArr<tagInfoButtons> tmppInfoButtons(m_pInfoButtons.GetSize());
			m_pInfoButtons.Resize(m_pInfoButtons.GetSize()+1);
			if((btnStyle&BTNS_SEP)==0)
			{
				if((btnStyle&BTNS_DROPDOWN)!=0)
					m_pInfoButtons[nInto].idMenu=idMenu;
				m_pInfoButtons[nInto].szToolTip=szTTip;
				m_pInfoButtons[nInto].idCommand=idCommand;
			}
			else
			{
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].idMenu=0;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].szToolTip=NULL;
				m_pInfoButtons[m_pInfoButtons.GetSize()-1].idCommand=0;
			}
			memcpy(m_pInfoButtons+nInto+1,tmppInfoButtons+nInto,(m_pInfoButtons.GetSize()-nInto-1)*sizeof(tagInfoButtons));
		//===========================================================
			btnState|=(m_afFlag&CCS_VERT)?TBSTATE_WRAP:0;
			TBBUTTON tbButtonsAdd={nBitmap, idCommand, 
				btnState,
				btnStyle,
		#if defined(_WIN32) | defined(_WIN64)
				{0},
		#endif
				/*dwData*/0, iString};
			if((btnStyle&BTNS_SEP)==0)
			{
				TBADDBITMAP tb;
				int  stdidx;
				tb.hInst=(nID>IDB_HIST_LARGE_COLOR)?NULL:hInst;
				tb.nID = nID;

				if(nID>IDB_HIST_LARGE_COLOR)
				{
					HIMAGELIST himl=(HIMAGELIST)SendMessage(TB_GETIMAGELIST,0,0);
					stdidx=ImageList_AddMasked(himl,(HBITMAP)nID,RGB(192,192,192));
					SendMessage(TB_SETIMAGELIST,0,LPARAM(himl));
				}
				else
				{
					stdidx = (int)SendMessage (TB_ADDBITMAP, nBitmap, (LPARAM)&tb);
				}
				tbButtonsAdd.iBitmap +=stdidx;
			}
			SendMessage(TB_SETBUTTONSIZE,0,(LPARAM)MAKELONG(m_dxBitmap,m_dyBitmap));
			SendMessage(TB_SETBITMAPSIZE,0,(LPARAM)MAKELONG(m_dxBitmap,m_dyBitmap));
			SendMessage(TB_INSERTBUTTON,nInto,LPARAM(&tbButtonsAdd));
			return 0;
		};

		int CULToolBar::InsertButton(int nInto,//куда вставить
						int idCommand,
						BYTE btnState,
						BYTE btnStyle,
						TCHAR* szTTip,
						int nBitmap,//номер картинки для кнопки тулбара 
						HBITMAP hBitmap,//ID ресурса для картинки
						INT_PTR iString,
						int idMenu)
		{
			return InsertButton(nInto,idCommand,btnState,btnStyle,szTTip,nBitmap,
				(INT_PTR)hBitmap,NULL,iString,idMenu);
		}

		int CULToolBar::DeleteButton(int nButton)
		{
		//========================удаление из массива m_InfoButtons===============
			ULOther::CULArr<tagInfoButtons> tmppInfoButtons(m_pInfoButtons.GetSize());
			memcpy(tmppInfoButtons,m_pInfoButtons,(m_pInfoButtons.GetSize())*sizeof(tagInfoButtons));
			m_pInfoButtons.Resize(m_pInfoButtons.GetSize()-1);
			int counter=0;
			for(int i=0;i<signed(m_pInfoButtons.GetSize()+1);i++)
				if(i!=nButton)
				{
					memcpy(m_pInfoButtons+counter,tmppInfoButtons+i,sizeof(tagInfoButtons));
					counter++;
				};
		//=========================================================================	
			SendMessage(TB_DELETEBUTTON,nButton,0);
			return 0;
		};


		void CULToolBar::AutoSize()//вставить в обработчик WM_SIZE окна родителя
		{
			if((m_afFlag&CCS_VERT)!=CCS_VERT)
				SendMessage(TB_AUTOSIZE); 
		};

		LRESULT CULToolBar::OnWindowPosChanging(WPARAM,LPARAM lParam)
		{
			if((m_tbStyle&TBSTYLE_AUTOSIZE)==0)
			{
				WINDOWPOS* pWP=(WINDOWPOS*)lParam;
//				RECT rcTBWidth;
/*				SendMessage(TB_GETITEMRECT,
					GetButtonCount()-1,(LPARAM)&rcTBWidth);
				if((pWP->cx>rcTBWidth.right))
	*/					pWP->cx=50;//rcTBWidth.right;
		}
			return FALSE;
		};

		LRESULT CULToolBar::OnDropDown(LPARAM lParam)
		{
			#define lpnm   ((LPNMHDR)lParam)
			#define lpnmTB ((LPNMTOOLBAR)lParam)
			RECT rc;
			TPMPARAMS tpm;
			::SendMessage(lpnmTB->hdr.hwndFrom, TB_GETRECT,
				(WPARAM)lpnmTB->iItem, (LPARAM)&rc);
				MapWindowPoints(lpnmTB->hdr.hwndFrom,
				HWND_DESKTOP, (LPPOINT)&rc, 2);                         
			tpm.cbSize = sizeof(TPMPARAMS);
			tpm.rcExclude = rc;
			for(unsigned int i=0;i<m_pInfoButtons.GetSize();i++)
				if(lpnmTB->iItem==(signed)m_pInfoButtons[i].idCommand)
				{
					ULControls::CULMenu PopupMenu;
					ULControls::CULMenu LoadedMenu;
					LoadedMenu.LoadMenu(ULOther::ULGetResourceHandle(), MAKEINTRESOURCE(m_pInfoButtons[i].idMenu)); 
					PopupMenu=LoadedMenu.GetSubMenu(1);
					POINT pt={rc.left, rc.bottom};
					PopupMenu.TrackPopupMenuEx(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,               
						pt, m_hParentWnd, &tpm); 				
				}
			return TBDDRET_DEFAULT;
		}
		CULToolBar::CTBToolTip::CTBToolTip():ULControls::CULToolTip()
		{
			MessageMap.AddReflectNotify<CTBToolTip>(TTN_GETDISPINFO,&CTBToolTip::OnGetDispInfo);
		};

		CULToolBar::CTBToolTip::~CTBToolTip(){};
		LONG CULToolBar::CTBToolTip::OnGetDispInfo(LPARAM lParam)
		{
			#define lpnm   ((LPNMHDR)lParam)
			#define lpttt ((LPTOOLTIPTEXT)lParam)
			lpttt->hinst = ULOther::ULGetResourceHandle(); 
			UINT_PTR idButton = lpttt->hdr.idFrom; 
			for(unsigned int i=0;i<m_pULToolBar->m_pInfoButtons.GetSize();i++)
				if(idButton==m_pULToolBar->m_pInfoButtons[i].idCommand)
				{
					lpttt->lpszText = m_pULToolBar->m_pInfoButtons[i].szToolTip;
					break;
				}
			return TRUE;
		};
	}
}