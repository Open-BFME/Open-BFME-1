// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

//#include "StdAfx.H"
#pragma warning(disable : 4668)	// is not defined as a preprocessor macro, replacing with '0' for '#if/#elif
#pragma warning(disable : 4820)	// padding added after member
#pragma warning(disable : 4255)	// no function prototype given: converting '()' to '(void)'

#include <windows.h>

#pragma warning( disable: 4206 )

void DoInitialization();
void DoCleanup();

// Declare DllMain
BOOL WINAPI DllMain(HINSTANCE hDllHandle, DWORD dwReason, LPVOID lpReserved);

BOOL (WINAPI* _pRawDllMain)(HINSTANCE, DWORD, LPVOID);

BOOL WINAPI _DllMainCRTStartup(HINSTANCE hDllHandle, DWORD dwReason, LPVOID lpReserved)
{
	BOOL bResult = TRUE;

	if ((dwReason == DLL_PROCESS_ATTACH) || (dwReason == DLL_THREAD_ATTACH))
	{
		if (_pRawDllMain != NULL)
		{
			bResult = _pRawDllMain(hDllHandle, dwReason, lpReserved);
			if (!bResult)
				return FALSE;
		}
	}

	if (dwReason == DLL_PROCESS_ATTACH)
	{
			DoInitialization();
	}

	bResult = DllMain(hDllHandle, dwReason, lpReserved);

	if (dwReason == DLL_PROCESS_DETACH)
	{
			DoCleanup();
	}

	if ((dwReason == DLL_PROCESS_DETACH) || (dwReason == DLL_THREAD_DETACH))
	{
		if (bResult && (_pRawDllMain != NULL))
			bResult = _pRawDllMain(hDllHandle, dwReason, lpReserved);
	}

	return bResult;
}

