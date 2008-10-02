///\file ULReBar.cpp
///\brief cpp файл класса ребара(11.08.2007)
#include "..\..\ULLib\Include\ULRebar.h"
#include "..\..\ULLib\Include\ULRes.h"
namespace ULWnds
{
	namespace ULBars
	{
		CULRebar::CULRebar():CULSubClass()
		{
		}

		CULRebar::CULRebar(CULRebar& rebar):CULSubClass(rebar),
			m_afFlag(rebar.m_afFlag)
		{
		}

		CULRebar::~CULRebar()
		{
		}

		void CULRebar::operator=(CULRebar& rebar)
		{
			m_afFlag=rebar.m_afFlag;
			ULWnds::CULSubClass::operator=(rebar);
		}

		HWND CULRebar::Create(HWND hParentWnd,enAlignFlags afFlag,DWORD dwStyle)
		{
			REBARINFO     rbi;
			INITCOMMONCONTROLSEX icex;
			HINSTANCE hinst=ULOther::ULGetResourceHandle();
			icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
			icex.dwICC   = ICC_COOL_CLASSES;
			InitCommonControlsEx(&icex);
			m_hWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
									REBARCLASSNAME,
									NULL,
									dwStyle|afFlag,
									0,0,0,0,//200,0,500,500,
									hParentWnd,
									NULL,
									hinst,
									NULL);
			m_afFlag=afFlag;
			if(!m_hWnd)
				return NULL;
			rbi.cbSize = sizeof(REBARINFO);  
			rbi.fMask  = 0;
			rbi.himl   = (HIMAGELIST)NULL;
			if(!SendMessage(RB_SETBARINFO, 0, (LPARAM)&rbi))
				return NULL;
			return (Attach(m_hWnd))?m_hWnd:NULL;
		};

		BOOL CULRebar::InsertBand(HWND hClientWnd,TCHAR* szName, HBITMAP hBitmap,
								WORD wID,SIZE* pszClient,DWORD dwStyle)
		{
			REBARBANDINFO rbBand;
			rbBand.cbSize = sizeof(REBARBANDINFO);  
			rbBand.fMask = RBBIM_STYLE|
				RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_SIZE|RBBIM_BACKGROUND;
			rbBand.fMask |=((rbBand.lpText=szName)!=NULL)?RBBIM_TEXT:0;
			rbBand.fMask |=((rbBand.hbmBack=hBitmap)!=NULL)?RBBIM_BACKGROUND:0;
			rbBand.fMask |=((rbBand.wID=wID)!=NULL)?RBBIM_ID:0;
			rbBand.fStyle =dwStyle;
			RECT rect;
			if(pszClient==NULL)
				::GetWindowRect(hClientWnd,&rect);
			else
				::SetRect(&rect,0,0,pszClient->cx,pszClient->cy);
			rbBand.hwndChild  = hClientWnd;
			if((m_afFlag==afTop)||(m_afFlag==afBottom))
			{
				rbBand.cxMinChild = rect.right-rect.left+((dwStyle&RBBS_CHILDEDGE)?2*::GetSystemMetrics(SM_CXEDGE):0);
				rbBand.cyMinChild = rect.bottom-rect.top+((dwStyle&RBBS_CHILDEDGE)?2*::GetSystemMetrics(SM_CYEDGE):0);
			}
			else
			{
				rbBand.cxMinChild = rect.bottom-rect.top+2*::GetSystemMetrics(SM_CYEDGE);
				rbBand.cyMinChild = rect.right-rect.left+2*::GetSystemMetrics(SM_CXEDGE);
			}
			return (SendMessage(RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand)!=NULL);
		}

		BOOL CULRebar::InsertBand(HWND hClientWnd, TCHAR* szName, 
								COLORREF clrFore, COLORREF clrBack,
								WORD wID,SIZE* pszClient,DWORD dwStyle)
		{
      REBARBANDINFO rbBand={0};
			rbBand.cbSize = sizeof(REBARBANDINFO);  // Required
			rbBand.fMask = RBBIM_STYLE|RBBIM_CHILD|RBBIM_CHILDSIZE|RBBIM_SIZE|RBBIM_BACKGROUND;
			rbBand.fMask |=((rbBand.lpText=szName)!=NULL)?RBBIM_TEXT:0;
			rbBand.fMask |=((rbBand.wID=wID)!=NULL)?RBBIM_ID:0;
			rbBand.fMask |=((rbBand.clrFore=clrFore)!=NULL)?RBBIM_COLORS:0;
			rbBand.fMask |=((rbBand.clrBack=clrBack)!=NULL)?RBBIM_COLORS:0;
			rbBand.fStyle =dwStyle;
			RECT rect;
			if(pszClient==NULL)
				::GetWindowRect(hClientWnd,&rect);
			else
				::SetRect(&rect,0,0,pszClient->cx,pszClient->cy);
			rbBand.hwndChild  = hClientWnd;
			if((m_afFlag==afTop)||(m_afFlag==afBottom))
			{
				rbBand.cxMinChild = rect.right-rect.left+2*::GetSystemMetrics(SM_CXEDGE);
				rbBand.cyMinChild = rect.bottom-rect.top+2*::GetSystemMetrics(SM_CYEDGE);
			}
			else
			{
				rbBand.cxMinChild = rect.bottom-rect.top+2*::GetSystemMetrics(SM_CYEDGE);
				rbBand.cyMinChild = rect.right-rect.left+2*::GetSystemMetrics(SM_CXEDGE);
			}
			return (SendMessage(RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand)!=NULL);
		}

		BOOL CULRebar::DeleteBand(int numBand)
		{
			return (0!=SendMessage((UINT) RB_DELETEBAND,WPARAM(numBand),0)); 
		}

		void CULRebar::AutoSize()
		{
		/* 	SendMessage((HWND) m_hWnd,      
				(UINT) RB_SHOWBAND,    
				(WPARAM) 0,
				(LPARAM) TRUE);  
		*/
			SendMessage(WM_SIZE,0,0);
		//	InvalidateRect(NULL,TRUE);

			 
		};
	}
}