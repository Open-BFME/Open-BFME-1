// Open-BFME5 conversions.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

class BfmeStrAVTW
{
public:
	char *m_bfme00;
};

class BfmeStrBVTW
{
public:
	char *m_bfme00;
};

struct BfmePairVTW
{
	int m_bfme00;
	BfmeStrBVTW m_bfme04;
};

class BfmeEntVTW
{
public:
	BfmeEntVTW(const BfmeStrAVTW &first, const BfmePairVTW &second);
	AsciiString m_bfme00;
	int m_bfme04;
	UnicodeString m_bfme08;
};

BfmeEntVTW::BfmeEntVTW(const BfmeStrAVTW &first, const BfmePairVTW &second)
	: m_bfme00(*(const AsciiString *)&first), m_bfme04(second.m_bfme00),
	  m_bfme08(*(const UnicodeString *)&second.m_bfme04)
{
}
