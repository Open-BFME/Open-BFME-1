/*
**  objbase.h shim — minimal COM declarations for sweep compilation
*/

#pragma once

#include <windows.h>

typedef GUID IID;
typedef GUID CLSID;
typedef const IID& REFIID;
typedef const GUID& REFGUID;

// {00000000-0000-0000-C000-000000000046}
extern "C" const IID IID_IUnknown;

#define E_NOINTERFACE ((HRESULT)0x80004002) // defined in UUID.LIB

#define STDMETHODCALLTYPE       __stdcall
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type, method) virtual type STDMETHODCALLTYPE method
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

struct IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) = 0;
	virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
	virtual ULONG STDMETHODCALLTYPE Release(void) = 0;
};
