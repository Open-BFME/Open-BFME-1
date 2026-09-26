// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the	
// Active Template Library product.

// atl.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "RegObj.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Registrar, CDLLRegObject)
	OBJECT_ENTRY_NON_CREATEABLE(CAxHostWindow)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		bAtlAxWinInitialized = false;
		OSVERSIONINFOA info;
		info.dwOSVersionInfoSize = sizeof(info);
		if (GetVersionExA(&info))
		{
#ifdef _UNICODE
			if (info.dwPlatformId != VER_PLATFORM_WIN32_NT)
			{
				MessageBoxA(NULL, "Can not run Unicode version of ATL71.DLL on Windows 95, Windows98 or Windows Me.\nPlease install the ANSI version.", "ATL", MB_ICONSTOP|MB_OK);
				return FALSE;
			}
#else
			if (info.dwPlatformId == VER_PLATFORM_WIN32_NT)
			{
				OutputDebugString(_T("Slight Performace loss due to running ANSI version of ATL71.DLL on Windows NT or Windows 2000\nPlease install the Unicode version.\n"));
			}
#endif
		}
#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
		int n = 0;
		_CrtSetBreakAlloc(n);
#endif
		_Module.Init(ObjectMap, hInstance, &LIBID_ATLLib);
#ifdef _ATL_DEBUG_INTERFACES
		int ni = 0;
		_Module.m_nIndexBreakAt = ni;
#endif // _ATL_DEBUG_INTERFACES
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
#ifdef _DEBUG
		::OutputDebugString(_T("ATL71.DLL exiting.\n"));
#endif
		_Module.Term();
		if (bAtlAxWinInitialized)
			AtlAxWinTerm();
#ifdef _DEBUG
		if (_CrtDumpMemoryLeaks())
			::MessageBeep(MB_ICONEXCLAMATION);
#endif
	}
	return TRUE;    // ok
}

namespace ATL
{
STDAPI AtlCreateRegistrar(IRegistrar** ppReg)
{
	if (ppReg == NULL)
		return E_POINTER;
	*ppReg = NULL;

	return( CDLLRegObject::_CreatorClass::CreateInstance(NULL, IID_IRegistrar, (void**)ppReg) );
}

STDAPI AtlUpdateRegistryFromResourceD(HINSTANCE hInst, LPCOLESTR lpszRes,
	BOOL bRegister, struct _ATL_REGMAP_ENTRY* pMapEntries, IRegistrar* pReg)
{
	ATLASSERT(hInst != NULL);
	if (hInst == NULL)
		return E_INVALIDARG;

	HRESULT hRes = S_OK;
	CComPtr<IRegistrar> p;

	if (pReg != NULL)
		p = pReg;
	else
	{
		hRes = AtlCreateRegistrar(&p);
	}
	if (NULL != pMapEntries)
	{
		while (NULL != pMapEntries->szKey)
		{
			ATLASSERT(NULL != pMapEntries->szData);
			p->AddReplacement(pMapEntries->szKey, pMapEntries->szData);
			pMapEntries++;
		}
	}
	if (SUCCEEDED(hRes))
	{
		TCHAR szModule[_MAX_PATH];
		int nRet = GetModuleFileName(hInst, szModule, _MAX_PATH);
		if(nRet == _MAX_PATH)
			return AtlHresultFromWin32(ERROR_BUFFER_OVERFLOW);
		
		if(nRet == 0)
			return AtlHresultFromLastError();

		USES_CONVERSION_EX;
		LPOLESTR pszModule = T2OLE_EX(szModule, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
		if(pszModule == NULL) 
			return E_OUTOFMEMORY;
#endif
		
		// Buffer Size is Multiplied by 2 because we are calling ReplaceSingleQuote
		OLECHAR pszModuleUnquoted[_MAX_PATH * 2];
		CAtlModule::EscapeSingleQuote(pszModuleUnquoted, pszModule);
		if (hInst == GetModuleHandle(NULL)) // register as EXE
		{
			// If Registering as an EXE, then we quote the resultant path.
			// We don't do it for a DLL, because LoadLibrary fails if the path is
			// quoted
			OLECHAR pszModuleQuote[(_MAX_PATH + _ATL_QUOTES_SPACE)*2];
			pszModuleQuote[0] = OLESTR('\"');			
			ocscpy(pszModuleQuote + 1, pszModuleUnquoted);
			int nLen = ocslen(pszModuleQuote);
			pszModuleQuote[nLen] = OLESTR('\"');
			pszModuleQuote[nLen + 1] = 0;
			
			hRes = p->AddReplacement(OLESTR("Module"), pszModuleQuote);			
		}
		else
		{
			hRes = p->AddReplacement(OLESTR("Module"), pszModuleUnquoted);
		}
		
		if(FAILED(hRes))
			return hRes;
	
		hRes = p->AddReplacement(OLESTR("Module_Raw"), pszModuleUnquoted);
		if(FAILED(hRes))
			return hRes;
	
		LPCOLESTR szType = OLESTR("REGISTRY");
		if (IS_INTRESOURCE(lpszRes))
		{
			if (bRegister)
				hRes = p->ResourceRegister(pszModule, ((UINT)LOWORD((DWORD_PTR)lpszRes)), szType);
			else
				hRes = p->ResourceUnregister(pszModule, ((UINT)LOWORD((DWORD_PTR)lpszRes)), szType);
		}
		else
		{
			if (bRegister)
				hRes = p->ResourceRegisterSz(pszModule, lpszRes, szType);
			else
				hRes = p->ResourceUnregisterSz(pszModule, lpszRes, szType);
		}

	}
	return hRes;
}

// Cannot pull these in from the static lib. The functions they reference are decorated
// with C++ calling convention. The functions are exported from the DLL with the 
// C calling convention
#ifdef _DEBUG
//CAtlWinModule _AtlWinModule;
CAtlComModule _AtlComModule;
#endif

}


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

/*
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	//No need to unregister typelib since ATL is a system component.
	return S_OK;
}
*/

#include <delayimp.h>

extern "C"
{
FARPROC
WINAPI
Downlevel_DelayLoadFailureHook(
	UINT unReason,
	PDelayLoadInfo pDelayInfo
	);

PfnDliHook __pfnDliFailureHook2 = Downlevel_DelayLoadFailureHook;

}
