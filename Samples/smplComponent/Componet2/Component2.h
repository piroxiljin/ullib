#pragma once
#ifndef _ULCOMPONENT2_H__
#define _ULCOMPONENT2_H__
#include "..\IFaces.h"
#include <objbase.h>
#include <iostream>
using namespace std;
class CComponent2:
	public IZ
{
public:
	CComponent2(void);
	virtual ~CComponent2(void);
	// IUnknown
	virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppvObject);
	virtual ULONG __stdcall AddRef(); 
	virtual ULONG __stdcall Release(); 



	// интерфейс IZ 
	virtual void __stdcall Fz() { cout << "Fz" << endl; }  

private: 
	//счётчик 
	long m_nRef; 
};
#endif//_ULCOMPONENT2_H__
