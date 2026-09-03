// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00538690, 80 bytes. Stdcall by-value wrapper around the cdecl
// setConnectingPlayerName helper: forwards index plus UnicodeString then
// destroys the by-value argument.

#include "../../../../../reference/shims/stringinline/StringInline.h"

void setConnectingPlayerName( int index, const UnicodeString &text );

void __stdcall setConnectingPlayerNameOwned( int index, UnicodeString text )
{
	setConnectingPlayerName( index, text );
}
