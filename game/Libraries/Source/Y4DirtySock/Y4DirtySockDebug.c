// cl: /Od /GZ /GS /MT /DNDEBUG -Iinputs/reference/shims/gamespy
/* THIS IS A SEPARATE TRANSLATION UNIT FROM Y4DirtySockSocket.c FOR ONE REASON:
 * /GS.  The body here ends with the MSVC 7.1 cookie epilogue -- the module
 * cookie loaded into ecx and passed to __security_check_cookie -- and the
 * bodies in the socket file do not.  /GS is a WHOLE-FILE switch, so adding it
 * to that file would change every body already matched there.  A new file is
 * the cheap move; splitting an already-green TU is not.
 */
#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

/* Retail's PE import directory identifies slot 0x01358EA8 as
 * KERNEL32.dll!OutputDebugStringA. The C shim supplies its native ABI types;
 * this missing declaration mirrors the existing WWLib/win.h prototype. */
__declspec(dllimport) void WINAPI OutputDebugStringA( LPCSTR pText );

int Rva007FE780( const char *pFormat, ... )
{
	va_list pArgs;
	char strText[ 0x1000 ];
	const char *pText;

	pText = strText;
	va_start( pArgs, pFormat );

	/* THE FAST PATH IS AN EXACT MATCH ON THE WHOLE FORMAT STRING, not a
	 * search for a conversion.  The three character tests are '%', then 's',
	 * then NUL, so only the format "%s" and nothing else takes it: the single
	 * argument is used directly and the formatter is skipped entirely.
	 */
	if ( pFormat[ 0 ] == '%' && pFormat[ 1 ] == 's' && pFormat[ 2 ] == 0 )
	{
		pText = va_arg( pArgs, const char * );
	}
	else
	{
		vsprintf( strText, pFormat, pArgs );
	}
	va_end( pArgs );

	OutputDebugStringA( pText );

	/* THE RETURN VALUE IS NOT COSMETIC AND IS NOT A GUESS.  Retail zeroes
	 * eax immediately before the /GZ frame-variable check, and that xor is
	 * the ONLY difference between this body and a void one -- so the
	 * function returns int, and the constant it returns is 0.
	 */
	return 0;
}
