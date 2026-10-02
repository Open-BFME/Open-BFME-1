// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the report submit at retail 0x0042B3D0, 71 bytes.  Its own
// parameters are unused: everything submitted comes from the object, and the
// name goes by value.

#include "ascii_string.h"

// The sink at 0x0044A240 names its four-byte string parameter AsciiStringBL.
// Use the canonical string implementation for its copy and release operations.
class AsciiStringBL
{
public:
	AsciiStringBL(const AsciiStringBL &other) throw()
		: m_bfmeNarrowBL(other.m_bfmeNarrowBL)
	{
	}

	~AsciiStringBL(void) throw()
	{
	}

private:
	AsciiString m_bfmeNarrowBL;
};

class BfmeBlobBL
{
public:
	char m_bfmePadBBM[12];
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

class BfmeReportBM
{
public:
	void bfmeSendBM(int unusedA, int unusedB);

	char m_bfmePadABM[0xb4];
	AsciiStringBL m_bfmeNameBM;
	int m_bfmeCountBM;
	BfmeBlobBL m_bfmeFirstBM;
	BfmeBlobBL m_bfmeSecondBM;
	BfmeBlobBL m_bfmeThirdBM;
	BfmeBlobBL m_bfmeFourthBM;
};

void BfmeReportBM::bfmeSendBM(int unusedA, int unusedB)
{
	((BfmeSinkBL *)TheInGameUI)->bfmeSubmitBL(m_bfmeNameBM, m_bfmeCountBM,
			&m_bfmeFirstBM, &m_bfmeSecondBM, &m_bfmeThirdBM,
			&m_bfmeFourthBM);
}
