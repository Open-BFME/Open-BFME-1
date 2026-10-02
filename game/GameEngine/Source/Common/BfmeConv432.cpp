// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The empty-string arguments retail pushes here are the two exported WWLib
// statics: retail 0x00584DD0/0x00585530 push 0x01336E50 (AsciiString) and
// 0x01336E54 (UnicodeString), i.e. the two `TheEmptyString` data objects.
#include "unicode_string.h"

extern "C" unsigned char bfmeTextTwoAZB[];

void bfmeStopAZB(int what);
void bfmeSendAZB(int what, void *one, void *two);

class BfmeThingAZB
{
public:
	void bfmeGoAZB(void *what);
	void bfmeSetAZB(void *what);
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	bool m_bfmeReady;
	bool m_bfmeOn;
};

void BfmeThingAZB::bfmeGoAZB(void *what)
{
	if (m_bfmeWhat != 0 && m_bfmeOn)
	{
		bfmeStopAZB(0);
		bfmeSendAZB(0, (void *)&UnicodeString::TheEmptyString, bfmeTextTwoAZB);
		m_bfmeWhat = 0;
		m_bfmeReady = false;
		m_bfmeOn = false;
	}
}

// ?bfmeSetAZB@BfmeThingAZB@@QAEXPAX@Z
void BfmeThingAZB::bfmeSetAZB(void *what)
{
	if (m_bfmeWhat != 0)
	{
		m_bfmeOn = true;
		bfmeStopAZB(0);
		bfmeSendAZB(0, (void *)&UnicodeString::TheEmptyString, bfmeTextTwoAZB);
		m_bfmeWhat = 0;
		m_bfmeReady = false;
		m_bfmeOn = false;
	}

	m_bfmeReady = false;
	m_bfmeWhat = what;
}
