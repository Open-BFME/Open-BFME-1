// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the report submit at retail 0x0042B370, 71 bytes.  Its own
// parameters are unused: everything submitted comes from the object, and the
// name goes by value.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class AsciiStringBL : public AsciiString
{
public:
	AsciiStringBL(const AsciiStringBL &other) throw() : AsciiString(other)
	{
	}

	~AsciiStringBL(void) throw()
	{
	}
};

class BfmeBlobBL
{
public:
	char m_bfmePadBBL[12];
};

class BfmeSinkBL
{
public:
	void bfmeSubmitBL(AsciiStringBL name, int count, BfmeBlobBL *first,
			BfmeBlobBL *second, BfmeBlobBL *third, BfmeBlobBL *fourth) throw();
};

// The global at retail 0x012F148C is InGameUI *TheInGameUI, defined once in
// game/GameEngine/Source/GameClient/InGameUI.cpp.  Only the linked name may be
// referenced here; BfmeSinkBL above stays as this TU's local view of the
// pointee, so the use casts.
class InGameUI;

extern InGameUI *TheInGameUI;			// retail 0x012F148C

class BfmeReportBL
{
public:
	void bfmeSendBL(int unusedA, int unusedB, int unusedC, int unusedD);

	char m_bfmePadABL[0xb4];
	AsciiStringBL m_bfmeNameBL;
	int m_bfmeCountBL;
	BfmeBlobBL m_bfmeFirstBL;
	BfmeBlobBL m_bfmeSecondBL;
	BfmeBlobBL m_bfmeThirdBL;
	BfmeBlobBL m_bfmeFourthBL;
};

void BfmeReportBL::bfmeSendBL(int unusedA, int unusedB, int unusedC, int unusedD)
{
	((BfmeSinkBL *)TheInGameUI)->bfmeSubmitBL(m_bfmeNameBL, m_bfmeCountBL,
			&m_bfmeFirstBL, &m_bfmeSecondBL, &m_bfmeThirdBL,
			&m_bfmeFourthBL);
}
