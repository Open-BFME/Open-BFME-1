// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

// Copied from CRT source file secinit.c
//

#pragma warning(disable : 4668)	// is not defined as a preprocessor macro, replacing with '0' for '#if/#elif
#pragma warning(disable : 4820)	// padding added after member
#pragma warning(disable : 4255)	// no function prototype given: converting '()' to '(void)'

#include <windows.h>
#include "atlmincrt.h"

/*
 * The global security cookie.  This name is known to the compiler.
 */
extern DWORD_PTR __security_cookie;

/*
 * Union to facilitate converting from FILETIME to unsigned __int64
 */
typedef union {
	unsigned __int64 ft_scalar;
	FILETIME ft_struct;
} FT;

/***
*__security_init_cookie(cookie) - init buffer overrun security cookie.
*
*Purpose:
*       Initialize the global buffer overrun security cookie which is used by
*       the /GS compile switch to detect overwrites to local array variables
*       the potentially corrupt the return address.  This routine is called
*       at EXE/DLL startup.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl __security_init_cookie(void)
{
	DWORD_PTR cookie;
	FT systime;
	LARGE_INTEGER perfctr;

	/*
     * Do nothing if the global cookie has already been initialized.
     */

    if (__security_cookie != 0 && __security_cookie != DEFAULT_SECURITY_COOKIE)
        return;

    /*
	 * Initialize the global cookie with an unpredictable value which is
	 * different for each module in a process.  Combine a number of sources
	 * of randomness.
	 */

	GetSystemTimeAsFileTime(&systime.ft_struct);
#if !defined (_WIN64)
	cookie = systime.ft_struct.dwLowDateTime;
	cookie ^= systime.ft_struct.dwHighDateTime;
#else  /* !defined (_WIN64) */
	cookie = systime.ft_scalar;
#endif  /* !defined (_WIN64) */

	cookie ^= GetCurrentProcessId();
	cookie ^= GetCurrentThreadId();
	cookie ^= GetTickCount();

	QueryPerformanceCounter(&perfctr);
#if !defined (_WIN64)
	cookie ^= perfctr.LowPart;
	cookie ^= perfctr.HighPart;
#else  /* !defined (_WIN64) */
	cookie ^= perfctr.QuadPart;
#endif  /* !defined (_WIN64) */

	/*
	 * Make sure the global cookie is never initialized to zero, since in that
	 * case an overrun which sets the local cookie and return address to the
	 * same value would go undetected.
	 */

    __security_cookie = cookie ? cookie : DEFAULT_SECURITY_COOKIE;
}
