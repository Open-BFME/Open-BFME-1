/*
**  EABrowserDispatch/BrowserDispatch.h shim — minimal declarations for sweep compilation
*/

#pragma once

#ifndef __BROWSERDISPATCH_H__
#define __BROWSERDISPATCH_H__

#include <objbase.h>

// {BC834510-C5BC-4B90-8C9A-0E4B1998796F}
extern "C" const GUID IID_IBrowserDispatch;

struct IBrowserDispatch : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE TestMethod(Int num1) = 0;
};

#endif
