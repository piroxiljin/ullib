///\file ULPropSheet.cpp
///\brief cpp файл класса root окна(2006)
#include "..\..\ULLib\Include\ULPropSheet.h"
#include "..\..\ULLib\Include\ULRes.h"
namespace ULWnds
{
	namespace ULDlgs
	{
		CULPropSheet* g_thisPreCreate;

		CULPropSheet::CULPropSheet():
			CULWnd(),m_fWizard(FALSE)
		{
		};

		CULPropSheet::~CULPropSheet()
		{
		};

		BOOL CULPropSheet::AddPage(HPROPSHEETPAGE hPropSheetPage)
		{
			if(hPropSheetPage!=NULL)
			{
				m_phPropSheetPage.Resize(m_phPropSheetPage.GetSize()+1);
				m_phPropSheetPage[m_phPropSheetPage.GetSize()-1]=hPropSheetPage;
				return TRUE;
			}
			return FALSE;
		}

		INT_PTR CULPropSheet::Create(HWND hParenWnd,
									TCHAR* szCaption,
									HBITMAP hbmHeader,
									HBITMAP hbmWatermark,
									UINT nWizardFlags,
									BOOL fModal)
		{
			PROPSHEETHEADER PropSheetHeader;
			memset(&PropSheetHeader,0,sizeof(PropSheetHeader));
			PropSheetHeader.dwSize=sizeof(PropSheetHeader);
			PropSheetHeader.hInstance=ULOther::ULGetResourceHandle();
			PropSheetHeader.hwndParent=hParenWnd;
			PropSheetHeader.dwFlags=PSH_USEPSTARTPAGE;
			PropSheetHeader.nStartPage=0;
			PropSheetHeader.nPages=(UINT)m_phPropSheetPage.GetSize();
			PropSheetHeader.phpage=m_phPropSheetPage;
			PropSheetHeader.dwFlags|=PSH_PROPTITLE;			
			PropSheetHeader.pszCaption=szCaption;
			PropSheetHeader.dwFlags|=nWizardFlags;
			m_fWizard=(nWizardFlags)?TRUE:FALSE;
//			PropSheetHeader.dwFlags|=PSH_USECALLBACK;
//			PropSheetHeader.pfnCallback=(PFNPROPSHEETCALLBACK)PropSheetProc;
			if(hbmHeader!=NULL)
			{
				PropSheetHeader.dwFlags|=PSH_USEHBMHEADER;
				PropSheetHeader.dwFlags|=PSH_HEADER;
				PropSheetHeader.hbmHeader=hbmHeader;
			}
			if(hbmWatermark!=NULL)
			{
				PropSheetHeader.dwFlags|=PSH_USEHBMWATERMARK;
				PropSheetHeader.dwFlags|=PSH_WATERMARK;
				PropSheetHeader.hbmWatermark=hbmWatermark;
			}
			if(fModal!=TRUE)
				PropSheetHeader.dwFlags|=PSH_MODELESS;

			g_thisPreCreate=this;
			return PropertySheet(&PropSheetHeader);		 
		}

		INT_PTR CULPropSheet::Create(HWND hParenWnd,
				TCHAR* szCaption,
				int rscHeader,
				int rscWatermark,
				UINT nWizardFlags,
				BOOL fModal)
		{
			return Create(hParenWnd,szCaption,
				::LoadBitmap(ULOther::ULGetResourceHandle(),MAKEINTRESOURCE(rscHeader)),
				::LoadBitmap(ULOther::ULGetResourceHandle(),MAKEINTRESOURCE(rscWatermark)),
				nWizardFlags,fModal);
		}

		BOOL CULPropSheet::IsWizard()
		{
			return m_fWizard;
		}

		BOOL CULPropSheet::OnInitialized(HWND hWnd)
		{
			m_hWnd=hWnd;
			SetWindowLong(GWL_USERDATA,(LONG)(LONG_PTR)this);
			g_thisPreCreate=NULL;
			return TRUE;
		}

		int CULPropSheet::PropSheetProc(HWND hDlg,UINT uMsg,LPARAM /*lParam*/)
		{
			if(uMsg==PSCB_INITIALIZED)
				g_thisPreCreate->OnInitialized(hDlg);
			return 0;
		}
	}
}