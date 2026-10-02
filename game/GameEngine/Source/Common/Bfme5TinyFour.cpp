// Four more tiny ones: a field address with a shared default, a stamp and a
// flag cleared together, an emptiness test that answers through the carry, and
// a flag written into a singleton.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The shared default this body falls back on is retail's 0x01336E50, which
// WWLib's ascii_string.h records as `AsciiString::TheEmptyString` (exported as
// ?TheEmptyString@AsciiString@@2V1@B, RVA 0x00F36E50) and which
// dir32_addresses.csv and symbols.csv both place at 0x01336E50.  The
// address-derived g_bfmeDefaultBP that stood here resolved nothing; the header
// included above already declares the real one, and this body only returns its
// address, through void * because the member is const.
class BfmeThingBP
{
public:
	char m_bfmeHead[0x54];					// +0x00
	int m_bfmeField;					// +0x54
};

class Gen_003C63A0
{
public:
	int *bfmeField(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeThingBP *m_bfmeThing;				// +0x04
};

// ?bfmeField@Gen_003C63A0@@QBEPAHXZ
int *Gen_003C63A0::bfmeField(void) const
{
	BfmeThingBP *thing = m_bfmeThing;

	if (thing)
		return &thing->m_bfmeField;

	// retail 0x01336E50: AsciiString::TheEmptyString, the shared default the
	// field address falls back on.
	const void *sharedDefault = &AsciiString::TheEmptyString;

	return (int *)sharedDefault;
}

class BfmeClockBP
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeStamp;					// +0x3C
};

// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;				// retail 0x012F0898

class Gen_002B6330
{
public:
	int bfmeReset(void);

private:
	int m_bfmeHead[9];					// +0x00
	int m_bfmeWhen;						// +0x24
	int m_bfmeGap;						// +0x28
	unsigned char m_bfmeFlag;				// +0x2C
};

// ?bfmeReset@Gen_002B6330@@QAEHXZ
int Gen_002B6330::bfmeReset(void)
{
	m_bfmeWhen = ((BfmeClockBP *)TheGameLogic)->m_bfmeStamp;

	m_bfmeFlag = 0;

	return 0;
}

class Gen_003BD6A0
{
public:
	int bfmeHasAny(void) const;

private:
	int m_bfmeHead[5];					// +0x00
	int *m_bfmeStart;					// +0x14
	int *m_bfmeFinish;					// +0x18
};

// ?bfmeHasAny@Gen_003BD6A0@@QBEHXZ
int Gen_003BD6A0::bfmeHasAny(void) const
{
	return 0 < (unsigned int)(m_bfmeFinish - m_bfmeStart);
}

class BfmeHolderBP
{
public:
	char m_bfmeHead[0xBC];					// +0x00
	unsigned char m_bfmeFlag;				// +0xBC
};

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's flag view is applied at the use.
class GameClient;
extern GameClient *TheGameClient;

// ?bfmeSetFlag@@YGXE@Z
void __stdcall bfmeSetFlag(unsigned char value)
{
	((BfmeHolderBP *)TheGameClient)->m_bfmeFlag = value;
}
