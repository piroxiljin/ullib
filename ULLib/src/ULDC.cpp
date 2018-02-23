///\file ULDC.cpp
///\brief cpp ���� ������� ����������(08.10.2007)
#include "ULGDI.h"

namespace ULGDI
{
	namespace ULDC
	{
		BOOL ULGDI::ULDC::CULDC::CreateBMPFile(LPCTSTR pszFile,RECT rcSize, DWORD dwComp, WORD wBitCount) 
		{	
			typedef struct
			{
				BITMAPINFOHEADER bmiHeader;
				RGBQUAD bmiColors[259];
			} DIBINFO;
				HANDLE hf;                 
				BITMAPFILEHEADER hdr;       
				LPBYTE lpBits;             
				DWORD dwTmp; 

				BITMAP ddbinfo = {0};
				DIBINFO bInfo = {0};

			ULGDI::ULGObjs::CULBitmap Bmp;
			Bmp.CreateCompatibleBitmap(*this,rcSize.right-rcSize.left,rcSize.bottom-rcSize.top);

			//������ ������� � ������
			ULGDI::ULDC::CULDC MemDC;
			MemDC.CreateCompatibleDC(m_hDC);
			HGDIOBJ hOld = MemDC.SelectObject((HBITMAP)Bmp);
			MemDC.BitBlt(0,0,rcSize.right-rcSize.left,rcSize.bottom-rcSize.top,m_hDC,0,0,SRCCOPY);
			MemDC.SelectObject(hOld);
			//��������� ������ �� �����������
			if (!Bmp.GetBitmap(&ddbinfo))
				return FALSE;
			bInfo.bmiHeader.biSize  = sizeof(BITMAPINFOHEADER);
			bInfo.bmiHeader.biWidth = ddbinfo.bmWidth;
			bInfo.bmiHeader.biHeight = ddbinfo.bmHeight;

			bInfo.bmiHeader.biBitCount = wBitCount;
			bInfo.bmiHeader.biCompression = dwComp;

			//������������ ������ - ����� �� ������  
			bInfo.bmiHeader.biPlanes = 1;
			bInfo.bmiHeader.biBitCount = wBitCount;
			bInfo.bmiHeader.biCompression = dwComp;//BI_RLE8, BI_RLE4...

			//��������� ������� ��� ������� ������� �� ���������
			if (!GetDIBits(Bmp, 0, ddbinfo.bmHeight, NULL, (BITMAPINFO*)&bInfo , DIB_RGB_COLORS))
				return FALSE;
			//������ ��������� ������
			DWORD dwInfSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*259;
			//���� �����
			DWORD dwTotalSize = dwInfSize + bInfo.bmiHeader.biSizeImage;
			lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, dwTotalSize);
			if (!lpBits)
				return FALSE;
			memset(lpBits,0,dwTotalSize);
			memcpy(lpBits,&bInfo,dwInfSize);

			//�������������� DDB � DIB
			if (!GetDIBits(Bmp, 0, ddbinfo.bmHeight, lpBits+dwInfSize, (BITMAPINFO*)lpBits , DIB_RGB_COLORS)) 
			{
				GlobalFree((HGLOBAL)lpBits);
				return FALSE;
			}
			//�������� ����� ��� �������
			hf = CreateFile(pszFile, 
				GENERIC_READ | GENERIC_WRITE, 
				(DWORD) 0, 
				NULL, 
				CREATE_ALWAYS, 
				FILE_ATTRIBUTE_NORMAL, 
				(HANDLE) NULL); 
		        
			if (hf == INVALID_HANDLE_VALUE) 
			{
				GlobalFree((HGLOBAL)lpBits);
				return FALSE;
			}
			//��������� ��������� �����
			hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
			hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + dwTotalSize);
			hdr.bfReserved1 = 0; 
			hdr.bfReserved2 = 0; 
			hdr.bfOffBits = (DWORD) (sizeof(BITMAPFILEHEADER) + dwInfSize);  

			//������ ���������
			if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
				(LPDWORD) &dwTmp,  NULL))
			{
				GlobalFree((HGLOBAL)lpBits);
				CloseHandle(hf);
				return FALSE;
			}
			//������ �������� ������
			if (!WriteFile(hf, (BITMAPINFO*)& bInfo, dwInfSize, (LPDWORD) &dwTmp,  NULL))
			{
				GlobalFree((HGLOBAL)lpBits);
				CloseHandle(hf);
				return FALSE;
			}
			//������ ������� �����
			if (!WriteFile(hf, (BYTE*)lpBits+dwInfSize, dwTotalSize-dwInfSize, (LPDWORD) &dwTmp,NULL)) 
			{
				GlobalFree((HGLOBAL)lpBits);
				CloseHandle(hf);
				return FALSE;
			}
			GlobalFree((HGLOBAL)lpBits);
			CloseHandle(hf);
			return TRUE;
		}

		BOOL CULDC::SaveDC()
		{
			return (::SaveDC(m_hDC)!=0);
		}

		BOOL CULDC::RestoreDC(int nSavedDC)
		{
			return (::RestoreDC(m_hDC,nSavedDC)!=0);
		}
		BOOL CULDC::Polygon(CONST POINT *lpPoints,int nCount)
		{
			return ::Polygon(m_hDC,lpPoints,nCount);
		}
		COLORREF CULDC::GetPixel(int nXPos,int nYPos)
		{
			return ::GetPixel(m_hDC,nXPos,nYPos);
		}
		BOOL CULDC::SetPixel(int nXPos,int nYPos,COLORREF crColor)
		{
			return (::SetPixel(m_hDC,nXPos,nYPos,crColor)!=CLR_INVALID);
		}
		BOOL CULDC::DrawIcon(int X,int Y,HICON hIcon)
		{
			return ::DrawIcon(*this,X,Y,hIcon);
		}
		BOOL CULDC::DrawIconEx(int xLeft,int yTop,HICON hIcon,int cxWidth,int cyWidth,
			UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw,UINT diFlags)
		{
			return ::DrawIconEx(*this,xLeft,yTop,hIcon,cxWidth,cyWidth,
			istepIfAniCur,hbrFlickerFreeDraw,diFlags);
		}
		int CULDC::SetROP2(int fnDrawMode)
		{
			return ::SetROP2(m_hDC,fnDrawMode);
		}
	}
}
