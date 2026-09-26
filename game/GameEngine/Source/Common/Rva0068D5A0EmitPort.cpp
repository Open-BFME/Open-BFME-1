// ?Rva0068D5A0EmitPort@@YAPAGPAGHPAG@Z
// cl: /DNDEBUG /MD /EHsc
// Writes one network-order 16-bit value into a bounded buffer. The retail
// body calls the WSOCK32 ntohs import indirectly (slot 0x0135972C) and keeps
// the full return dword in a stack local, reading back only its low word.

__declspec(dllimport) int __stdcall ntohs( int netshort );

union Rva0068D5A0Converted
{
	volatile unsigned int storage;
	unsigned short narrow;
};

unsigned short *Rva0068D5A0EmitPort( unsigned short *dst, int value, unsigned short *limit )
{
	Rva0068D5A0Converted converted;
	converted.storage = (unsigned int)ntohs( value );

	if( limit != 0 )
	{
		if( dst > limit )
			return dst;

		if( dst + 1 > limit )
			return dst;
	}

	*dst = converted.narrow;

	return dst + 1;
}
