// _UCS2CharToUTF8String
// GameSpy string helper (gap at 0x0085C1A0) ported as a C++ ABI slice.
extern "C" int UCS2CharToUTF8String(unsigned short theUCS2Char, char *theUTF8String)
{
	if (theUCS2Char <= 0x7F)
	{
		theUTF8String[0] = (char)theUCS2Char;
		return 1;
	}
	else if (theUCS2Char <= 0x7FF)
	{
		theUTF8String[0] = (char)(0xC0 | (theUCS2Char >> 6));
		theUTF8String[1] = (char)(0x80 | (theUCS2Char & 0x3F));
		return 2;
	}
	else
	{
		theUTF8String[0] = (char)(0xE0 | (theUCS2Char >> 12));
		theUTF8String[1] = (char)(0x80 | ((theUCS2Char >> 6) & 0x3F));
		theUTF8String[2] = (char)(0x80 | (theUCS2Char & 0x3F));
		return 3;
	}
}
