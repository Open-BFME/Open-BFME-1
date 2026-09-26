/*
**  oleauto.h shim — minimal for sweep compilation
*/

#pragma once

#include <windows.h>
#include <objbase.h>

typedef struct tagVARIANT VARIANT;

typedef unsigned long DISPID;
typedef DISPID MEMBERID;

struct ITypeLib
{
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoOfGuid(REFGUID guid, struct ITypeInfo** pptinfo) = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;
};

struct ITypeInfo
{
	virtual HRESULT STDMETHODCALLTYPE GetTypeAttr(void** ppTypeAttr) = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;
};

HRESULT LoadTypeLib(const wchar_t* szFile, ITypeLib** pptlib);
HRESULT CreateStdDispatch(IUnknown* punkOuter, void* pvThis, ITypeInfo* ptinfo, IUnknown** ppunkStdDisp);

HRESULT OleInitialize(void* pvReserved);
void OleUninitialize(void);
