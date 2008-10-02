#pragma once
#ifndef _IFACES_H__
#define _IFACES_H__
#include <objbase.h>
//
// Iface.h - 
//    Declarations of interfaces, IIDs, and CLSID
//    shared by the client and the component.
//
interface IX : IUnknown
{
	virtual void pascal Fx() = 0 ;
};


interface IY : IUnknown
{
	virtual void pascal Fy() = 0 ;
};


interface IZ : IUnknown
{
	virtual void pascal Fz() = 0 ;
};

#endif //_IFACES_H__

//
// Declaration of GUIDs for interfaces and component.
//   These constants are defined in GUIDs.cpp.
//
/*
extern "C" const IID IID_IX ;
extern "C" const IID IID_IY ;
extern "C" const IID IID_IZ ;

extern "C" const CLSID CLSID_Component1 ;
*/

// {C845A164-5B29-4803-86E5-A38152FB71D0}
static const IID IID_IX = 
	{ 0xc845a164, 0x5b29, 0x4803, 
	{ 0x86, 0xe5, 0xa3, 0x81, 0x52, 0xfb, 0x71, 0xd0 } };

// {9153CCA7-7665-4ab4-ACD4-780D0C768F89}
static const IID IID_IY = 
	{ 0x9153cca7, 0x7665, 0x4ab4, 
	{ 0xac, 0xd4, 0x78, 0xd, 0xc, 0x76, 0x8f, 0x89 } };

// {D99DA902-38D1-48d9-82F0-655F206AEC7D}
static const IID IID_IZ = 
	{ 0xd99da902, 0x38d1, 0x48d9, 
	{ 0x82, 0xf0, 0x65, 0x5f, 0x20, 0x6a, 0xec, 0x7d } };

///\brief Идентификатор класса компонента
// {8601DD88-1DBC-412A-A30A-4744A9ff4B5D }
static const CLSID CLSIDComponent0={ 0x8601dd88, 0x1dbc, 0x412a, 
		{ 0xa3, 0xa, 0x47, 0x44, 0xa9, 0xff, 0x4b, 0x5d } };

///\brief Идентификатор класса компонента2
// {83EA9B79-D427-4a2b-A434-2C8EEE9457EF}
static const GUID CLSIDComponent2 = 
{ 0x83ea9b79, 0xd427, 0x4a2b, { 0xa4, 0x34, 0x2c, 0x8e, 0xee, 0x94, 0x57, 0xef } };
