// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the	
// Active Template Library product.

#include "stdafx.h"
#include "Common.h"
#include "AtlTraceModuleManager.h"

namespace ATL
{
void WINAPI NotifyTool();

static bool WINAPI SetSettings(CAtlTraceSettings *pTraceSettings, UINT nLevel, UINT nStatus)
{
	ATLASSERT(pTraceSettings);
	if(!pTraceSettings)
		return false;

	pTraceSettings->m_nLevel = nLevel;
	switch(nStatus)
	{
	case 0:
		pTraceSettings->m_eStatus = CAtlTraceSettings::Inherit;
		break;
	case 1:
		pTraceSettings->m_eStatus = CAtlTraceSettings::Enabled;
		break;
	case 2:
	default:
		pTraceSettings->m_eStatus = CAtlTraceSettings::Disabled;
		break;
	}
	return true;
}

static bool WINAPI GetSettings(const CAtlTraceSettings &rTraceSettings, UINT *pnStatus)
{
	ATLASSERT(pnStatus);
	if(!pnStatus)
		return false;

	switch(rTraceSettings.m_eStatus)
	{
	case CAtlTraceSettings::Inherit:
		*pnStatus = 0;
		break;
	case CAtlTraceSettings::Enabled:
		*pnStatus = 1;
		break;
	case CAtlTraceSettings::Disabled:
	default:
		*pnStatus = 2;
		break;
	}
	return true;
}

BOOL __stdcall AtlTraceLoadSettingsA(const CHAR *pszFileName, DWORD_PTR dwProcess /* = 0 */)
{
	CHAR szFileName[_MAX_PATH];
	if(!pszFileName)
	{
		CHAR szDrive[_MAX_DRIVE];
		CHAR szDir[_MAX_DIR];
		CHAR szFName[_MAX_FNAME];
		CHAR szExt[_MAX_EXT];

		DWORD dwret = ::GetModuleFileNameA(NULL, szFileName, MAX_PATH);
		if( dwret == 0 || dwret == MAX_PATH )
			return FALSE;
		_splitpath(szFileName, szDrive, szDir, szFName, szExt);
		strcpy(szExt, ".trc");
		_makepath(szFileName, szDrive, szDir, szFName, szExt);
		pszFileName = szFileName;
	}

	if(pszFileName)
	{
		if(-1 != GetFileAttributesA(pszFileName))
		{
			// file exists
			CHAR szSection[MAX_PATH], szKey[MAX_PATH], szValue[MAX_PATH];
			CHAR szName[MAX_PATH];
			UINT nModules, nCategories, nStatus, nLevel;
			UINT nModule;
			CAtlTraceProcess *pProcess;
			CAtlTraceModule *pModule;
			CAtlTraceCategory *pCategory;
			CHAR *pszProcess = "Process";
			CHAR cEnabled, cFuncAndCategoryNames, cFileNameAndLineInfo;
			CAtlAllocator *pAllocator = &g_Allocator;

			if (dwProcess)
				pAllocator = reinterpret_cast<CAtlAllocator*>(dwProcess);

			pProcess = pAllocator->GetProcess();
			ATLASSERT(pProcess);
			if(!pProcess)
				return FALSE;

			pProcess->m_bLoaded = true;

			::GetPrivateProfileStringA(pszProcess, "Info", "", szValue, MAX_PATH, pszFileName);
			szValue[MAX_PATH - 1] = 0;
			
			if(5 != sscanf(szValue, "ModuleCount:%u, Level:%u, Enabled:%c, "
				"FuncAndCategoryNames:%c, FileNameAndLineNo:%c", &nModules, &pProcess->m_nLevel, &cEnabled,
				&cFuncAndCategoryNames, &cFileNameAndLineInfo))
			{
				return FALSE;
			}
			pProcess->m_bEnabled = cEnabled != 'f';
			pProcess->m_bFuncAndCategoryNames = cFuncAndCategoryNames != 'f';
			pProcess->m_bFileNameAndLineNo = cFileNameAndLineInfo != 'f';

			USES_CONVERSION;
			for(UINT i = 0; i < nModules; i++)
			{
				sprintf(szKey, "Module%d", i+1);
				::GetPrivateProfileStringA(pszProcess, szKey, "", szSection, MAX_PATH, pszFileName);
				szSection[MAX_PATH -1] = 0;

				::GetPrivateProfileStringA(szSection, "Name", "", szName, MAX_PATH, pszFileName);
				szName[MAX_PATH -1] = 0;
				if(!pAllocator->FindModule(CA2W(szName), &nModule))
					continue;

				pModule = pAllocator->GetModule(nModule);
				ATLASSERT(pModule);
				if(!pModule)
					continue;

				::GetPrivateProfileStringA(szSection, "Settings", "", szValue, MAX_PATH, pszFileName);
				szValue[MAX_PATH -1] = 0;
				if(3 != sscanf(szValue, "CategoryCount:%u, Level:%u, Status:%u", &nCategories, &nLevel, &nStatus))
					continue;

				SetSettings(pModule, nLevel, nStatus);

				for(UINT j = 0; j < nCategories; j++)
				{
					sprintf(szKey, "Category%d", j+1);
					::GetPrivateProfileStringA(szSection, szKey, "", szValue, MAX_PATH, pszFileName);
					szValue[MAX_PATH -1] = 0;
					if(3 != sscanf(szValue, "Level:%u, Status:%u, Name:%s", &nLevel, &nStatus, szName))
						continue;

					UINT iCategory = pModule->m_iFirstCategory;
					while( iCategory != UINT( -1 ) )
					{
						pCategory = pAllocator->GetCategory(iCategory);

						if( lstrcmpA(CW2A(pCategory->Name()), szName) == 0 )
						{
							SetSettings(pCategory, nLevel, nStatus);
						}
						iCategory = pCategory->m_iNextCategory;
					}
				}
			}
			NotifyTool();
		}
	}
	return TRUE;
}

BOOL __stdcall AtlTraceSaveSettingsA(const CHAR *pszFileName, DWORD_PTR dwProcess /* = 0 */)
{
	ATLASSERT(pszFileName);
	if(!pszFileName)
		return FALSE;

	BOOL bRetVal = FALSE;

	CHAR szKey[MAX_PATH], szValue[MAX_PATH];
	UINT nCategories, nStatus;
	CAtlTraceProcess *pProcess;
	CAtlTraceModule *pModule;
	CAtlTraceCategory *pCategory;
	LPCSTR pszProcess = "Process";
	CAtlAllocator *pAllocator = &g_Allocator;

	if (dwProcess)
		pAllocator = reinterpret_cast<CAtlAllocator*>(dwProcess);

	pProcess = pAllocator->GetProcess();
	ATLASSERT(pProcess);
	if(!pProcess)
		return FALSE;

	bRetVal = TRUE;
	ATLTRACEPROCESSINFO info;
	AtlTraceGetProcessInfo(dwProcess, &info);

	sprintf(szValue, "ModuleCount:%u, Level:%u, Enabled:%c, "
		"FuncAndCategoryNames:%c, FileNameAndLineNo:%c", info.nModules, pProcess->m_nLevel,
		pProcess->m_bEnabled ? 't' : 'f', pProcess->m_bFuncAndCategoryNames ? 't' : 'f',
		pProcess->m_bFileNameAndLineNo ? 't' : 'f');
	if(::WritePrivateProfileStringA(pszProcess, "Info", szValue, pszFileName) == 0)
		return FALSE;

	for(int i = 0; i <  info.nModules; i++)
	{
		pModule = pAllocator->GetModule(i);
		ATLASSERT(pModule);
		if(!pModule)
			return FALSE;

		sprintf(szKey, "Module%d", i+1);
		if(::WritePrivateProfileStringA(pszProcess, szKey, CW2A(pModule->Name()), pszFileName) == 0)
			return FALSE;
		GetSettings(*pModule, &nStatus);

		nCategories = pAllocator->GetCategoryCount(i);

		if(::WritePrivateProfileStringA(CW2A(pModule->Name()), "Name", CW2A(pModule->Path()), pszFileName) == 0)
			return FALSE;
			
		sprintf(szValue, "CategoryCount:%u, Level:%u, Status:%u", nCategories, pModule->m_nLevel, nStatus);
		if(::WritePrivateProfileStringA(CW2A(pModule->Name()), "Settings", szValue, pszFileName) == 0)
			return FALSE;

		int j = 0;
		UINT nCategory = pModule->m_iFirstCategory;
		while( nCategory != UINT( -1 ) )
		{
			pCategory = pAllocator->GetCategory(nCategory);

			GetSettings(*pCategory, &nStatus);

			sprintf(szKey, "Category%d", j+1);
			j++;
			sprintf(szValue, "Level:%u, Status:%u, Name:%S",
				pCategory->m_nLevel, nStatus, pCategory->Name());
			if(::WritePrivateProfileStringA(CW2A(pModule->Name()), szKey, szValue, pszFileName) == 0)
				return FALSE;

			nCategory = pCategory->m_iNextCategory;
		}
	}
	return bRetVal;
}

BOOL __stdcall AtlTraceLoadSettingsU(const WCHAR *pszFileName, DWORD_PTR dwProcess /* = 0 */)
{
	WCHAR szFileName[MAX_PATH];
	if(!pszFileName)
	{
		WCHAR szDrive[_MAX_DRIVE];
		WCHAR szDir[_MAX_DIR];
		WCHAR szFName[_MAX_FNAME];
		WCHAR szExt[_MAX_EXT];

		DWORD dwret = ::GetModuleFileNameW(NULL, szFileName, MAX_PATH);
		if( dwret == 0 || dwret == MAX_PATH )
			return FALSE;
		_wsplitpath(szFileName, szDrive, szDir, szFName, szExt);
		wcscpy(szExt, L".trc");
		_wmakepath(szFileName, szDrive, szDir, szFName, szExt);
		pszFileName = szFileName;
	}

	if(pszFileName)
	{
		if(-1 != GetFileAttributesW(pszFileName))
		{
			// file exists
			WCHAR szSection[MAX_PATH], szKey[MAX_PATH], szValue[MAX_PATH];
			WCHAR szName[MAX_PATH];
			UINT nModules, nCategories, nStatus, nLevel;
			UINT nModule;
			CAtlTraceProcess *pProcess;
			CAtlTraceModule *pModule;
			CAtlTraceCategory *pCategory;
			LPCWSTR pszProcess = L"Process";
			WCHAR cEnabled, cFuncAndCategoryNames, cFileNameAndLineInfo;
			CAtlAllocator *pAllocator = &g_Allocator;

			if (dwProcess)
				pAllocator = reinterpret_cast<CAtlAllocator*>(dwProcess);

			pProcess = pAllocator->GetProcess();
			ATLASSERT(pProcess);
			if(!pProcess)
				return FALSE;

			pProcess->m_bLoaded = true;

			::GetPrivateProfileStringW(pszProcess, L"Info", L"", szValue, MAX_PATH, pszFileName);
			szValue[MAX_PATH -1] = 0;
			if(5 != swscanf(szValue, L"ModuleCount:%u, Level:%u, Enabled:%c, "
				L"FuncAndCategoryNames:%c, FileNameAndLineNo:%c", &nModules, &pProcess->m_nLevel, &cEnabled,
				&cFuncAndCategoryNames, &cFileNameAndLineInfo))
			{
				return FALSE;
			}
			pProcess->m_bEnabled = cEnabled != L'f';
			pProcess->m_bFuncAndCategoryNames = cFuncAndCategoryNames != L'f';
			pProcess->m_bFileNameAndLineNo = cFileNameAndLineInfo != L'f';

			for(UINT i = 0; i < nModules; i++)
			{
				swprintf(szKey, L"Module%d", i+1);
				::GetPrivateProfileStringW(pszProcess, szKey, L"", szSection, MAX_PATH, pszFileName);
				szSection[MAX_PATH -1] = 0;
				::GetPrivateProfileStringW(szSection, L"Name", L"", szName, MAX_PATH, pszFileName);
				szName[MAX_PATH -1] = 0;
				if(!pAllocator->FindModule(szName, &nModule))
					continue;

				pModule = pAllocator->GetModule(nModule);
				ATLASSERT(pModule);
				if(!pModule)
					continue;

				::GetPrivateProfileStringW(szSection, L"Settings", L"", szValue, MAX_PATH, pszFileName);
				szValue[MAX_PATH -1] = 0;
				if(3 != swscanf(szValue, L"CategoryCount:%u, Level:%u, Status:%u", &nCategories, &nLevel, &nStatus))
					continue;

				SetSettings(pModule, nLevel, nStatus);

				for(UINT j = 0; j < nCategories; j++)
				{
					swprintf(szKey, L"Category%d", j+1);
					::GetPrivateProfileStringW(szSection, szKey, L"", szValue, MAX_PATH, pszFileName);
					szValue[MAX_PATH -1] = 0;
					if(3 != swscanf(szValue, L"Level:%u, Status:%u, Name:%s", &nLevel, &nStatus, szName))
						continue;

					UINT iCategory = pModule->m_iFirstCategory;
					while( iCategory != UINT( -1 ) )
					{
						pCategory = pAllocator->GetCategory(iCategory);

						if( lstrcmpW(pCategory->Name(), szName) == 0 )
						{
							SetSettings(pCategory, nLevel, nStatus);
						}
						iCategory = pCategory->m_iNextCategory;
					}
				}
			}
			NotifyTool();
		}
	}
	return TRUE;
}

BOOL __stdcall AtlTraceSaveSettingsU(const WCHAR *pszFileName, DWORD_PTR dwProcess /* = 0 */)
{
	ATLASSERT(pszFileName);
	if(!pszFileName)
		return FALSE;

	BOOL bRetVal = FALSE;

	WCHAR szKey[MAX_PATH], szValue[MAX_PATH];
	UINT nCategories, nStatus;
	CAtlTraceProcess *pProcess;
	CAtlTraceModule *pModule;
	CAtlTraceCategory *pCategory;
	LPCWSTR pszProcess = L"Process";
	CAtlAllocator *pAllocator = &g_Allocator;

	if (dwProcess)
		pAllocator = reinterpret_cast<CAtlAllocator*>(dwProcess);

	pProcess = pAllocator->GetProcess();
	ATLASSERT(pProcess);
	if(!pProcess)
		return FALSE;

	bRetVal = TRUE;
	ATLTRACEPROCESSINFO info;
	AtlTraceGetProcessInfo(dwProcess, &info);

	swprintf(szValue, L"ModuleCount:%u, Level:%u, Enabled:%c, "
		L"FuncAndCategoryNames:%c, FileNameAndLineNo:%c", info.nModules, pProcess->m_nLevel,
		pProcess->m_bEnabled ? L't' : L'f', pProcess->m_bFuncAndCategoryNames ? L't' : L'f',
		pProcess->m_bFileNameAndLineNo ? L't' : L'f');
	if(::WritePrivateProfileStringW(pszProcess, L"Info", szValue, pszFileName) == 0)
		return FALSE;

	for(int i = 0; i <  info.nModules; i++)
	{
		pModule = pAllocator->GetModule(i);
		ATLASSERT(pModule);
		if(!pModule)
			return FALSE;

		swprintf(szKey, L"Module%d", i+1);
		if(::WritePrivateProfileStringW(pszProcess, szKey, pModule->Name(), pszFileName) == 0)
			return FALSE;
		GetSettings(*pModule, &nStatus);

		nCategories = pAllocator->GetCategoryCount(i);

		if(::WritePrivateProfileStringW(pModule->Name(), L"Name", pModule->Path(), pszFileName) == 0)
			return FALSE;
		swprintf(szValue, L"CategoryCount:%u, Level:%u, Status:%u", nCategories, pModule->m_nLevel, nStatus);
		if(::WritePrivateProfileStringW(pModule->Name(), L"Settings", szValue, pszFileName) == 0)
			return FALSE;

		int j = 0;
		UINT nCategory = pModule->m_iFirstCategory;
		while( nCategory != UINT( -1 ) )
		{
			pCategory = pAllocator->GetCategory(nCategory);

			GetSettings(*pCategory, &nStatus);

			swprintf(szKey, L"Category%d", j+1);
			j++;
			swprintf(szValue, L"Level:%u, Status:%u, Name:%s",
				pCategory->m_nLevel, nStatus, pCategory->Name());
			if(::WritePrivateProfileStringW(pModule->Name(), szKey, szValue, pszFileName) == 0)
				return FALSE;

			nCategory = pCategory->m_iNextCategory;
		}
	}
	return bRetVal;
}

}; // namespace ATL
