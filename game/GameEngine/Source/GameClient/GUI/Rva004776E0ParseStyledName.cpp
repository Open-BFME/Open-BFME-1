// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: retail 0x004776E0 (512 bytes), a cdecl INI field-parse callback
// (its address sits in a field table at 0x00477A5D through ILT 0x0001EB4B).
// It reads two integers, then walks the rest of the line: "+bold" sets the
// style to 1, "-bold" to 2, "normal" to 0, any other token becomes the name.
// A named entry is appended to the 16-byte-element vector at `store`. No
// caller names the parser, so it keeps the address.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	AsciiString getNextAsciiString();
	static Int scanInt(const char *token);
};

// 16-byte element of the vector family anchored at 0x00477050.
struct Rva00477050Element
{
	Int m_value0;
	Int m_value1;
	Int m_style;
	AsciiString m_name;
};

// Retail inlines StringBase<char>::compareNoCase(const char *) here: a
// _memicmp over the shorter length, then the length difference.
static inline Int inlineCompareNoCase(const AsciiString &s, const char *text, Int textLen)
{
	const char *data = *reinterpret_cast<const char *const *>(&s);
	Int len;
	const char *chars;
	if (data)
	{
		len = *reinterpret_cast<const unsigned short *>(data + 4);
		chars = data + 8;
	}
	else
	{
		len = 0;
		chars = s.str();
	}
	Int r = _memicmp(chars, text, len < textLen ? len : textLen);
	if (r == 0)
		r = len - textLen;
	return r;
}

void Rva004776E0Parse(INI *ini, void *instance, void *store, const void *userData)
{
	Int value0 = INI::scanInt(ini->getNextToken());
	Int value1 = INI::scanInt(ini->getNextToken());
	Rva00477050Element entry;
	entry.m_value1 = value1;
	entry.m_value0 = value0;
	entry.m_style = 0;

	AsciiString token = ini->getNextAsciiString();
	while (token.StringBase<char>::getLength() != 0)
	{
		if (inlineCompareNoCase(token, "+bold", 5) == 0)
			entry.m_style = 1;
		else if (inlineCompareNoCase(token, "-bold", 5) == 0)
			entry.m_style = 2;
		else if (inlineCompareNoCase(token, "normal", 6) == 0)
			entry.m_style = 0;
		else
			entry.m_name = token;
		token = ini->getNextAsciiString();
	}

	_STL::vector<Rva00477050Element> *list = (_STL::vector<Rva00477050Element> *)store;
	if (entry.m_name.StringBase<char>::getLength() > 0)
		list->push_back(entry);
}
