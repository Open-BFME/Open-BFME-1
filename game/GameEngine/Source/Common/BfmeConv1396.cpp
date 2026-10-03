// Open-BFME5 conversions.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

struct BfmeSrcVJZ
{
	char m_bfmePad[0x10];
	AsciiString m_bfme10;
};

struct BfmeYVJZ
{
	char m_bfmePad[8];
	int m_bfme08;
};

char __stdcall bfmeGoVJZ(BfmeSrcVJZ *a, BfmeYVJZ *b)
{
	AsciiString tmp(a->m_bfme10);
	char r = (b->m_bfme08 <= 0);
	return r;
}
