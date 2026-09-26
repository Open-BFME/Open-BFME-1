// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "StdAfx.H"
#include "atlmincrt.h"

#pragma warning(disable : 4711)	// function selected for automatic inline expansion

static HANDLE g_hProcessHeap = NULL;

extern "C" _PVFV* __onexitbegin = NULL;
extern "C" _PVFV* __onexitend = NULL;

extern "C" _PVFV __xi_a[], __xi_z[];    /* C initializers */
extern "C" _PVFV __xc_a[], __xc_z[];    /* C++ initializers */
extern "C" _PVFV __xp_a[], __xp_z[];    /* C pre-terminators */
extern "C" _PVFV __xt_a[], __xt_z[];    /* C terminators */

// Critical section to protect initialization/exit code
static CRITICAL_SECTION g_csInit;

extern "C"
{
unsigned int _osplatform;
}

static 	OSVERSIONINFO osi;

extern "C" void DoInitialization()
{
	_PVFV* pf;

	memset(&osi, 0, sizeof(OSVERSIONINFO));
	osi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osi);
	_osplatform = osi.dwPlatformId;


	InitializeCriticalSection( &g_csInit );

	EnterCriticalSection( &g_csInit );

	__try
	{
		g_hProcessHeap = GetProcessHeap();

		// Call initialization routines (contructors for globals, etc.)
		for(pf = __xi_a; pf < __xi_z; pf++)
		{
			if(*pf != NULL)
			{
				(**pf)();
			}
		}

		for(pf = __xc_a; pf < __xc_z; pf++)
		{
			if(*pf != NULL)
			{
				(**pf)();
			}
		}
	}
	__finally
	{
		LeaveCriticalSection(&g_csInit);
	}
}

extern "C" void DoCleanup()
{
	_PVFV* pf;

	EnterCriticalSection(&g_csInit);  // Protect access to the atexit table

	__try
	{
		// Call routines registered with atexit() from most recently registered
		// to least recently registered
		if(__onexitbegin != NULL)
		{
			for(pf = __onexitend-1; pf >= __onexitbegin; pf--)
			{
				if (*pf != NULL)
					(**pf)();
			}
		}

		free(__onexitbegin);
		__onexitbegin = NULL;
		__onexitend = NULL;

		for(pf = __xp_a; pf < __xp_z; pf++)
		{
			if( *pf != NULL )
			{
				(**pf)();
			}
		}

		for(pf = __xt_a; pf < __xt_z; pf++)
		{
			if( *pf != NULL )
			{
				(**pf)();
			}
		}
	}
	__finally
	{
		LeaveCriticalSection(&g_csInit);
		DeleteCriticalSection(&g_csInit);		
	}
}

/////////////////////////////////////////////////////////////////////////////
// Heap Allocation

void* __cdecl malloc(size_t n)
{
	return (void*) HeapAlloc(g_hProcessHeap, 0, n);
}

void* __cdecl calloc(size_t n, size_t s)
{
	void* p;

	p = malloc(n*s);
	if(p != NULL)
		memset(p, 0, n*s);

	return p;
}

size_t __cdecl _msize(void*p)
{
	return HeapSize(g_hProcessHeap, 0, p);
}

void* __cdecl realloc(void* p, size_t n)
{
	if (p == NULL)
		return malloc(n);
	else if (n == 0)
	{
		free(p);
		return NULL;
	}
	else
		return HeapReAlloc(g_hProcessHeap, 0, p, n);
}

void __cdecl free(void* p)
{
	if (p != NULL)
		HeapFree(g_hProcessHeap, 0, p);
}

void* __cdecl operator new(size_t n)
{
	return malloc(n);
}

void* __cdecl operator new[](size_t n)
{
	return operator new(n);
}

void __cdecl operator delete(void* p)
{
	free(p);
}

void __cdecl operator delete[](void* p)
{
	operator delete(p);
}

int __cdecl atexit(_PVFV pf)
{
	size_t nCurrentSize;
	int nRet = 0;	

	EnterCriticalSection(&g_csInit);

	__try
	{
		if(__onexitbegin == NULL)
		{
			__onexitbegin = (_PVFV*)malloc(16*sizeof(_PVFV));
			if(__onexitbegin == NULL)
			{
				LeaveCriticalSection(&g_csInit);
				return(-1);
			}
			__onexitend = __onexitbegin;
		}

		nCurrentSize = _msize(__onexitbegin);
		if((nCurrentSize+sizeof(_PVFV)) < ULONG(((const BYTE*)__onexitend-
			(const BYTE*)__onexitbegin)))
		{
			_PVFV* pNew;

			pNew = (_PVFV*)realloc(__onexitbegin, 2*nCurrentSize);
			if(pNew == NULL)
			{
				LeaveCriticalSection(&g_csInit);	  
				return(-1);
			}
		}

		*__onexitend = pf;
		__onexitend++;
	}
	__except (1)
	{
		nRet = -1;
	}

	LeaveCriticalSection(&g_csInit);	

	return(nRet);
}

int __cdecl _purecall()
{
	DebugBreak();
	return 0;
}

extern "C" const int _fltused=0;