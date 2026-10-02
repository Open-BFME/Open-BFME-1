// cl: /O2 /DNDEBUG /MD /EHsc
//
// 0x008C5470 (39 bytes) sat alone in an unclaimed gap: 16-byte-aligned start
// after an int3 pad run, ret followed by int3 padding, and no call, ILT stub,
// table slot, code immediate, pin or dir32 name at the address.  It writes its
// two char arguments and a terminator into a three-byte buffer (MSVC places it
// in the first argument's home slot) and returns strtoul(buffer, 0, 16): the
// value of a two-digit hex pair.  strtoul resolves through the existing
// _strtoul pin at 0x009F6DE8.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.

extern "C" unsigned long __cdecl strtoul( const char *text, char **end, int base );

unsigned long Rva008C5470HexPair( char high, char low )
{
	char text[ 3 ];
	text[ 0 ] = high;
	text[ 1 ] = low;
	text[ 2 ] = 0;
	return strtoul( text, 0, 16 );
}
