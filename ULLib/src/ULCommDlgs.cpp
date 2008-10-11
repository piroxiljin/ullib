///\file ULCommDlgs.cpp
///\brief cpp файл классов стандартных диалоговых окон(02.01.2007)
#include "..\\include\\ULCommDlgs.h"
#include "..\\include\\ULRes.h"


namespace ULWnds
{
	namespace ULDlgs
	{
		namespace ULCommDlgs
		{
			//==================CULCommDlg=======================================
			LRESULT CULCommDlg::WndProc(HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam)
			{
				CULWnd *pULWnd=NULL;
				switch(uMsg)
				{
				case WM_INITDIALOG:
					{
						LPCHOOSECOLOR lpсс=(CHOOSECOLOR*)lParam;
						if(lpсс->lStructSize==sizeof(CHOOSECOLOR))
						{
							::SetWindowLong (hWnd, GWL_USERDATA, (LONG)lpсс->lCustData);
							pULWnd = (CULWnd *) lpсс->lCustData; // получим указатель на класс
						}
						LPOPENFILENAME lpofn=(LPOPENFILENAME)lParam;
						if(lpofn->lStructSize==sizeof(OPENFILENAME))
						{
							::SetWindowLong (hWnd, GWL_USERDATA, (LONG)lpofn->lCustData);
							pULWnd = (CULWnd *) lpofn->lCustData; // получим указатель на класс
						}
						pULWnd->m_hWnd=hWnd;
						break;
					}
				default:
					pULWnd = FromHandle(hWnd);
				}

				if(pULWnd!=NULL)
				{
					LRESULT lRes=pULWnd->OnMessage(uMsg,wParam,lParam);
					if(lRes)
						return lRes;

					if(uMsg==WM_COMMAND)
					{
						BOOL fRet=pULWnd->MessageMap.ProcessCommand(pULWnd,wParam,lParam);
						if(fRet)
							return fRet;
					}
					else 
						if(uMsg==WM_NOTIFY)
						{
							BOOL fRet=pULWnd->MessageMap.ProcessNotify(pULWnd,(NMHDR*)lParam);
							if(fRet)
								return fRet;
						}
					BOOL fRet=pULWnd->MessageMap.ProcessMessage(pULWnd,uMsg,wParam,lParam);
					if(fRet)
						return fRet;
				}
				return FALSE;
			}
			//==================CULColorDlg=======================================
			CULColorDlg::CULColorDlg(COLORREF clrInit,
					DWORD dwFlags):
					CULCommDlg()				
			{
				m_cc.lStructSize=sizeof(m_cc);
				m_cc.hInstance=(HWND)ULOther::ULGetResourceHandle();
				m_cc.Flags=dwFlags;
				m_cc.lpCustColors=m_acrCustClr;
				m_cc.rgbResult=clrInit;
				m_cc.lpfnHook=(LPCCHOOKPROC)CULCommDlg::WndProc;
				m_cc.lCustData=(LPARAM)this;
			};
			CULColorDlg::~CULColorDlg()
			{
			};

			int CULColorDlg::CreateModal(short idTempl, HWND hParentWnd)
			{
				m_cc.lpTemplateName=MAKEINTRESOURCE(idTempl);
				m_cc.hwndOwner=hParentWnd;
				m_fModal=TRUE;
				return ChooseColor(&m_cc);
			};
			//==================CULFileDialog=======================================

			CULFileDlg::CULFileDlg(BOOL fOpenFileDlg,
					LPCTSTR lpszDefExt,
					LPCTSTR lpszFileName,
					DWORD dwFlags,
					LPCTSTR lpszFilter,
					DWORD dwFilterIndex):
				CULCommDlg()
			{
				m_fOpenFileDlg=fOpenFileDlg;
				ZeroMemory(&m_ofn, sizeof(m_ofn));
				m_ofn.lStructSize = sizeof(m_ofn);
				m_ofn.hInstance=ULOther::ULGetResourceHandle();
				m_ofn.lpstrDefExt=lpszDefExt;
				m_ofn.nFileExtension=0;
				m_ofn.lpstrFile=const_cast<LPTSTR>(lpszFileName);
				m_ofn.Flags=dwFlags;
				m_ofn.Flags|=(lpszDefExt!=NULL)?OFN_EXTENSIONDIFFERENT:0;

				m_ofn.lpstrFilter=lpszFilter;
				m_ofn.lpstrFile=m_strFile;
				m_ofn.nMaxFile=(DWORD)m_strFile.GetSize();
				m_ofn.lpstrFileTitle=m_strFileTitle;
				m_ofn.nMaxFileTitle=(DWORD)m_strFileTitle.GetSize();
				m_ofn.nFilterIndex=dwFilterIndex;
				m_ofn.lpstrFile[0]=_T('\0');
				m_ofn.lCustData=(LPARAM)this;
				m_ofn.lpfnHook=(LPOFNHOOKPROC)CULCommDlg::WndProc;
			}

			int CULFileDlg::CreateModal(short idTempl, HWND hParentWnd)
			{
				m_ofn.lpTemplateName=MAKEINTRESOURCE(idTempl);
				m_ofn.hwndOwner=hParentWnd;
				m_fModal=TRUE;
				if(m_fOpenFileDlg)
					return GetOpenFileName(&m_ofn);
				else
					return GetSaveFileName(&m_ofn);
			}

			LPCTSTR CULFileDlg::SetDefExt(LPCTSTR lpszDefExt)
			{
				LPCTSTR lpszOld=m_ofn.lpstrDefExt;
				m_ofn.lpstrDefExt=lpszDefExt;
				return lpszOld;
			}
		}
	}
}