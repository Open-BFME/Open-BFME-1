// cl: /Od /GZ /GS /MT /DNDEBUG
/* THIS IS A SEPARATE TRANSLATION UNIT FROM Y4DirtySockSocket.c FOR ONE REASON:
 * /GS.  The body here ends with the MSVC 7.1 cookie epilogue -- the module
 * cookie loaded into ecx and passed to __security_check_cookie -- and the
 * bodies in the socket file do not.  /GS is a WHOLE-FILE switch, so adding it
 * to that file would change every body already matched there.  A new file is
 * the cheap move; splitting an already-green TU is not.
 */
#include <stdarg.h>
#include <stdio.h>

/* NOT an import -- there is no IAT entry at this address.  It is an ordinary
 * function pointer in .data, i.e. the sink is HOOKABLE at run time, which is
 * the usual shape for this library's diagnostic output.  The call takes one
 * argument and is followed by no stack cleanup at the call site, so the
 * pointer is __stdcall.
 */
extern void ( __stdcall *g_Rva01358EA8Print )( const char *pText );

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

	g_Rva01358EA8Print( pText );

	/* THE RETURN VALUE IS NOT COSMETIC AND IS NOT A GUESS.  Retail zeroes
	 * eax immediately before the /GZ frame-variable check, and that xor is
	 * the ONLY difference between this body and a void one -- so the
	 * function returns int, and the constant it returns is 0.
	 */
	return 0;
}
