///\file ULRegServ.cpp
///\brief cpp ���� ������ ����������� COM - �������
#include "ULRegServ.h"
#include <objbase.h>
#include <assert.h>
#include <tchar.h>
namespace ULCOMs
{
	CULRegServ::CULRegServ(void)
	{
	}

	CULRegServ::~CULRegServ(void)
	{
	}

	void CULRegServ::CLSIDtoTCHAR(const CLSID& clsid,
					 LPTSTR szCLSID,
					 int nLen)
	{
		assert(nLen >= CLSID_STRING_SIZE) ;
		//�������� CLSID
		LPOLESTR wszCLSID = NULL ;
		HRESULT hr = StringFromCLSID(clsid, &wszCLSID) ;
		assert(SUCCEEDED(hr)) ;	
	#ifndef UNICODE
		// ����������� �� ������� � ANSII
		size_t nConverted;
		wcstombs_s(&nConverted,szCLSID,nLen,wszCLSID, nLen) ;
	#else
		wcscpy_s(szCLSID,nLen,wszCLSID);
	#endif
		// ������������ ������
		CoTaskMemFree(wszCLSID) ;
	}

	BOOL CULRegServ::SetKeyAndValue(LPCTSTR szKey,
									LPCTSTR szSubkey,
									LPCTSTR szValue)
	{
		HKEY hKey;
		TCHAR szKeyBuf[1024] ;

		//�������� ���� � �����
		_tcscpy_s(szKeyBuf,1024,szKey) ;

		//��������� ��� �������� � �����
		if (szSubkey != NULL)
		{
			_tcscat_s(szKeyBuf,1024, _T("\\")) ;
			_tcscat_s(szKeyBuf,1024, szSubkey ) ;
		}

		//������ � ��������� �������
		long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT ,
									  szKeyBuf, 
									  0, NULL, REG_OPTION_NON_VOLATILE,
									  KEY_ALL_ACCESS, NULL, 
									  &hKey, NULL) ;
		if (lResult != ERROR_SUCCESS)
			return FALSE ;

		//������������� ��������
		if (szValue != NULL)
			RegSetValueEx(hKey, NULL, 0, REG_SZ, 
						  (BYTE *)szValue, 
						  static_cast<DWORD>(_tcslen(szValue))*sizeof(szValue[0])) ;

		RegCloseKey(hKey) ;
		return TRUE ;
	}

	LONG CULRegServ::RecursiveDeleteKey(HKEY hKeyParent,
										LPCTSTR lpszKeyChild)  
	{
		//��������� �������� ����
		HKEY hKeyChild ;
		LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
								 KEY_ALL_ACCESS, &hKeyChild) ;
		if (lRes != ERROR_SUCCESS)
		{
			return lRes ;
		}

		// ���������� ��� �������� ����� ����� �����
		FILETIME time ;
		TCHAR szBuffer[256] ;
		DWORD dwSize = 256 ;
		while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
							NULL, NULL, &time) == S_OK)
		{
			//������� ��������� ����� ������������ ������(��������)
			lRes = RecursiveDeleteKey(hKeyChild, szBuffer) ;
			if (lRes != ERROR_SUCCESS)
			{
				//��������� ���� ����� �������
				RegCloseKey(hKeyChild) ;
				return lRes;
			}
			dwSize = 256 ;
		}

		//��������� �������� ����
		RegCloseKey(hKeyChild) ;

		//������� ���� �������� ����
		return RegDeleteKey(hKeyParent, lpszKeyChild) ;
	}

	HRESULT CULRegServ::RegisterServer(HMODULE hModule,
									   const CLSID& clsid,
									   LPCTSTR szFriendlyName,
									   LPCTSTR szVerIndProgID,
									   LPCTSTR szProgID)
	{
		//�������� ��������������� �������
		TCHAR szModule[512]={0};
		DWORD dwResult =::GetModuleFileName(hModule, 
			szModule,
			sizeof(szModule)/sizeof(szModule[0])) ;
		assert(dwResult!= 0);

		//������������ CLSID � ������
		TCHAR szCLSID[CLSID_STRING_SIZE] ;
		CLSIDtoTCHAR(clsid, szCLSID, sizeof(szCLSID)/sizeof(szCLSID[0])) ;

		//������ ���� CLSID\\{...}
		TCHAR szKey[64] ;
		_tcscpy_s(szKey,64,_T("CLSID\\")) ;
		_tcscat_s(szKey,64,szCLSID) ;
	  
		//��������� CLSID � ������.
		SetKeyAndValue(szKey, NULL, szFriendlyName) ;

		// ��������� � CLSID ������� � ������ ����� �������.
		SetKeyAndValue(szKey, _T("InprocServer32"), szModule) ;

		// ��������� � CLSID ������� � ProgID
		SetKeyAndValue(szKey, _T("ProgID"), szProgID) ;
		
		// ��������� � CLSID ������� � ����������� �� ������ ProgID
		SetKeyAndValue(szKey, _T("VersionIndependentProgID"),
					   szVerIndProgID) ;

		// ��������� � HKEY_CLASSES_ROOT ������� � ����������� �� ������ ProgID
		SetKeyAndValue(szVerIndProgID, NULL, szFriendlyName) ; 
		SetKeyAndValue(szVerIndProgID, _T("CLSID"), szCLSID) ;
		SetKeyAndValue(szVerIndProgID, _T("CurVer"), szProgID) ;

		// ��������� � HKEY_CLASSES_ROOT ������� � ProgID
		SetKeyAndValue(szProgID, NULL, szFriendlyName) ; 
		SetKeyAndValue(szProgID, _T("CLSID"), szCLSID) ;

		return S_OK ;
	}

	LONG CULRegServ::UnregisterServer(const CLSID& clsid,         
									  LPCTSTR szVerIndProgID, 
									  LPCTSTR szProgID)       
	{
		// ����������� CLSID � ������.
		TCHAR szCLSID[CLSID_STRING_SIZE] ;
		CLSIDtoTCHAR(clsid, szCLSID, sizeof(szCLSID)/sizeof(szCLSID[0])) ;
		// ��������� ���� CLSID\\{...}
		TCHAR szKey[64] ;
		_tcscpy_s(szKey,sizeof(szKey)/sizeof(szKey[0]),_T("CLSID\\")) ;
		_tcscat_s(szKey,sizeof(szKey)/sizeof(szKey[0]),szCLSID) ;

		// ������� ���� CLSID - CLSID\{...}
		LONG lResult = RecursiveDeleteKey(HKEY_CLASSES_ROOT, szKey) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // �������� ����� �� ����.

		// ������� ���������� �� ������ ProgID ����.
		lResult = RecursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // �������� ����� �� ����

		// ������� ProgID ����.
		lResult = RecursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // �������� ����� �� ����

		return S_OK ;
	}
}