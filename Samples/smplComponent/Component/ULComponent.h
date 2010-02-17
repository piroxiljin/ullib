#pragma once
#ifndef _ULCOMPONENT_H__
#define _ULCOMPONENT_H__
#include <iostream>
#include "..\IFaces.h"
#include "..\\Unknown.h"
using namespace std;
class CULComponent:
	public CUnknown,
	public IX,public IY
{
public:
	CULComponent(void);
	virtual ~CULComponent(void);

//	DECLARE_IUNKNOWN

	virtual HRESULT __stdcall	                             
		QueryInterface(const IID& iid, void** ppv)           
	{	                                                     
		return GetOuterUnknown()->QueryInterface(iid,ppv) ;  
	} ;	                                                     
	virtual ULONG __stdcall AddRef()	                     
	{	                                                     
		return GetOuterUnknown()->AddRef() ;                 
	} ;	                                                     
	virtual ULONG __stdcall Release()	                     
	{	                                                     
		return GetOuterUnknown()->Release() ;                
	} ;


	// интерфейс IX 
	virtual void __stdcall Fx() { cout << "Fx" << endl; } 
	// интерфейс IY 
	virtual void __stdcall Fy() { cout << "Fy" << endl; }  

private: 
	//счётчик 
	long m_nRef; 
};
#endif//_ULCOMPONENT_H__
