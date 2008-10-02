///\file ULGObjs.cpp
///\brief cpp файл графических объектов(08.10.2007)
#include "..\..\ULLib\Include\ULGObjs.h"
#include "..\..\ULLib\Include\ULOther.h"
#include <olectl.h>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include <tchar.h>

namespace ULGDI
{
	namespace ULGObjs
	{
		BOOL CULRgn::CreateBitmapRgn(CULBitmap RgnBitmap)
		{
			//создание региона по маске
			if(RgnBitmap.m_hBitmap==NULL)
				return FALSE;	
			BITMAP bmp; 
			RgnBitmap.GetBitmap(&bmp);
			int bpp = bmp.bmBitsPixel >> 3;
			ULOther::CULArr<BYTE> pBits(bmp.bmWidth*bmp.bmHeight*bpp);
			RgnBitmap.GetBitmapBits(bmp.bmWidth*bmp.bmHeight*bpp,(BYTE*)pBits);
			DWORD dwTransPixel=*(DWORD*)(BYTE*)pBits;
			//узнаем цвет прозрачности
			dwTransPixel <<= 32 - bmp.bmBitsPixel;
			CreateRectRgn(0,0,0,0);
			//определение непрозрачных точек
			for (int i = 0; i < bmp.bmHeight; i++)
			{
				int nStartX=-1;
				for (int j = 0; j < bmp.bmWidth; j++)
				{
					DWORD dwPixel = *(DWORD*)(pBits + (i * bmp.bmWidth + j) * bpp) << (32 - bmp.bmBitsPixel);
					if (dwPixel!=dwTransPixel)
					{
						if (nStartX<0)
						{
							nStartX = j;
						} 
						else 
							if (j == (bmp.bmWidth - 1))
							{
								CULRgn Rgn;
								Rgn.CreateRectRgn( nStartX, i, j, i + 1 );
								CombineRgn(Rgn, RGN_OR);
								nStartX=-1;
							}
					}
					else 
						if (nStartX>=0)
						{
							CULRgn Rgn;
							Rgn.CreateRectRgn( nStartX, i, j, i + 1 );
							CombineRgn(Rgn, RGN_OR);
							nStartX=-1;
						}
				}
			}
			return TRUE;
		};
	}
}



HBITMAP ULGDI::ULLoadImage(LPCTSTR szResource,LPCTSTR szResourceType,HINSTANCE hMod)
{
	class CULLoadImageErr
	{
	public:
		enum enErr
		{
			eFindResource			=-1,
			eLoadResource			=-2,
			eLockResource			=-3,
			eCreateStreamOnHGlobal	=-4,
			eOleLoadPicture			=-5,
			eGetObject				=-6
		};
	protected:
		enErr m_nErr;
	public:	
		CULLoadImageErr(enErr nErr):m_nErr(nErr){};
		enErr GetError()
			{return m_nErr;}
	};
	HRESULT hr;
	IStream* pStream=NULL;
	IPicture* m_pPicture=NULL;
	HRSRC rc=NULL;			
	LPVOID lpImage=NULL;
	HGLOBAL hgl=NULL;
	DWORD dwSize=0;
	LPVOID pNewMem=NULL;
	HBITMAP hBitmapRet=NULL;
	try
	{
		if(IS_INTRESOURCE(szResource))
		{//вариант загрузки из ресурсов
			//ищем ресурс
			rc=::FindResource(hMod,szResource,szResourceType);
			if(rc==NULL)
				throw CULLoadImageErr(CULLoadImageErr::eFindResource);
			//определяем размер ресурса
			dwSize = ::SizeofResource(hMod, rc);	
			// читаем ресурс
			hgl=::LoadResource(hMod,rc);	
			if(hgl==NULL)
				throw CULLoadImageErr(CULLoadImageErr::eLoadResource);
			lpImage=LockResource(hgl);
			if(lpImage==NULL)
				throw CULLoadImageErr(CULLoadImageErr::eLockResource);
			//копируем ресурс в отдельный блок памяти для создания потока
			pNewMem = (LPVOID)::GlobalAlloc(GMEM_FIXED,dwSize);
			if(pNewMem==NULL)
				throw CULLoadImageErr(CULLoadImageErr::eLockResource);
			::CopyMemory(pNewMem,lpImage,dwSize);
			//создаём поток
			hr=::CreateStreamOnHGlobal((HGLOBAL)pNewMem,TRUE,&pStream);
			if(hr!=S_OK)
				throw CULLoadImageErr(CULLoadImageErr::eLockResource);
		}
		else
		{
			//создаём поток из фаила
			hr=::SHCreateStreamOnFile(szResource,STGM_SHARE_EXCLUSIVE,&pStream);
			if(hr!=S_OK)
				throw CULLoadImageErr(CULLoadImageErr::eCreateStreamOnHGlobal);
		}
		//загружаем картинку из потока
		hr = ::OleLoadPicture(pStream,0,true,IID_IPicture,(void**)&m_pPicture);
		if((hr!=S_OK)||(m_pPicture==NULL))
			throw CULLoadImageErr(CULLoadImageErr::eOleLoadPicture);
		HBITMAP hBitmap=NULL;
		//получаем хендл битмапа
		m_pPicture->get_Handle((OLE_HANDLE*)(UINT*)&hBitmap);
		//получаем размер битмапа
		BITMAP bmp;
		if(GetObject(hBitmap,sizeof(BITMAP),&bmp)==0)
			throw CULLoadImageErr(CULLoadImageErr::eGetObject);
		//копируем битмап
		HDC hDTDC=::GetDC(NULL);
		HDC hSrcDC=::CreateCompatibleDC(hDTDC);
		hBitmap=(HBITMAP)::SelectObject(hSrcDC,hBitmap);
		HDC hDestDC=::CreateCompatibleDC(hDTDC);
		hBitmapRet=::CreateCompatibleBitmap(hDTDC,bmp.bmWidth,bmp.bmHeight);
		hBitmapRet=(HBITMAP)::SelectObject(hDestDC,hBitmapRet);
		::BitBlt(hDestDC,0,0,bmp.bmWidth,bmp.bmHeight,hSrcDC,0,0,SRCCOPY);
		::SelectObject(hSrcDC,hBitmap);
		hBitmapRet=(HBITMAP)::SelectObject(hDestDC,hBitmapRet);
		//освобождаем GDI ресурсы
		::DeleteDC(hSrcDC);
		::DeleteDC(hDestDC);	
		::ReleaseDC(NULL,hDTDC);
	}
	catch(CULLoadImageErr& /*e*/)
	{
		/*тут по желанию :-) */
	}
	//освобождаем ресурсы
	if(hgl!=NULL)
	{
		UnlockResource(hgl);
		::FreeResource(hgl);
	}
	if(pNewMem!=NULL)
		::GlobalFree(pNewMem);
	if(m_pPicture)
		m_pPicture->Release();
	return hBitmapRet;
}