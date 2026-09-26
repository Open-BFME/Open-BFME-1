// cl: /DNDEBUG /MD
// Retail 0x0048CE70 one-character MultiByteToWideChar helper.

extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
	unsigned int codePage, unsigned long flags, const char *source,
	int sourceBytes, unsigned short *destination, int destinationChars );
extern "C" unsigned int __cdecl strlen( const char *text );

union Rva0048CE70Packed
{
	unsigned int whole;
	char bytes[4];
};

unsigned short __stdcall decodeRva0048CE70( volatile Rva0048CE70Packed packed,
	unsigned int codePage )
{
	unsigned int value = packed.whole;
	if( value & 0xff00 ) {
		packed.bytes[0] = (char)(value >> 8);
		packed.bytes[1] = (char)value;
		packed.bytes[2] = 0;
	} else {
		unsigned char low = (unsigned char)value;
		packed.bytes[0] = (char)low;
		packed.bytes[1] = 0;
	}

	int length = strlen( (const char *)packed.bytes );
	unsigned int activeCodePage = codePage;
	if( MultiByteToWideChar( activeCodePage, 0, (const char *)packed.bytes, length,
		(unsigned short *)&codePage, 1 ) == 1 )
		return (unsigned short)codePage;
	return 0;
}
