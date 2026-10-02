// Open-BFME5 conversions.

#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeStrVTZ
{
public:
	char *m_bfme00;
};

class BfmeRecVTZ
{
public:
	BfmeRecVTZ(const BfmeStrVTZ &first, const BfmeStrVTZ &second, int third,
		int fourth, char fifth);
	AsciiString m_bfme00;
	AsciiString m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfme10;
	char m_bfme11;
};

BfmeRecVTZ::BfmeRecVTZ(const BfmeStrVTZ &first, const BfmeStrVTZ &second, int third,
	int fourth, char fifth)
	: m_bfme00(*(const AsciiString *)&first),
	  m_bfme04(*(const AsciiString *)&second),
	  m_bfme08(third), m_bfme0c(fourth),
	  m_bfme10(0), m_bfme11(fifth)
{
}
