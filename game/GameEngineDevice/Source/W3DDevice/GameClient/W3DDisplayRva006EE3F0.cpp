// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Retail slot 23 reads descriptor and product fields at +0x184 and +0x188.
// Evidence: targets/game/reverse/identity_evidence/006ee3f0-descriptor-reset.md

#include "../../../../GameEngine/Include/Common/ScalarTypes/Int.h"
#include "../../../../GameEngine/Include/Common/ScalarTypes/Real.h"
typedef unsigned char Bool;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GameFont;

#include "ascii_string.h"

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern FontLibrary *TheFontLibrary;

class Gen0000D33C
{
public:
	Gen0000D33C(GameFont *font, Real arg2, Real arg3, Int arg4,
		Int arg5, Int arg6, Int arg7);
	~Gen0000D33C(void);

private:
	unsigned char m_unreconstructed[0x6c];
};

// The product calls retain the independently decoded retail ILT routes.

struct Rva006EE3F0Entry
{
	unsigned char m_unreconstructed[0x20];
	bool m_displayed;
};

struct Rva006EE3F0Descriptor
{
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	Int m_pointSize;
	Rva006EE3F0Entry **m_begin;
	Rva006EE3F0Entry **m_end;

	// ?Count@Rva006EE3F0Descriptor@@QBEHXZ absent-from-retail
	Int Count(void) const
	{
		return (Int)(m_end - m_begin);
	}

	// ??ARva006EE3F0Descriptor@@QBEPAURva006EE3F0Entry@@H@Z absent-from-retail
	Rva006EE3F0Entry *operator[](Int index) const
	{
		return m_begin[index];
	}
	// ?resetDisplayed006EE3F0@Rva006EE3F0Descriptor@@QAEXXZ absent-from-retail
	void resetDisplayed006EE3F0()
	{
		for (Int index = 0; index < Count(); ++index)
		{
			// Keep each iteration's storage and bounds loads separate.
			_ReadWriteBarrier();
			Rva006EE3F0Entry *entry = (*this)[index];
			entry->m_displayed = 0;
		}
	}
};

class W3DDisplay
{
public:
	virtual Bool rva006EE3F0(Rva006EE3F0Descriptor *descriptor, Real arg2, Real arg3, Int arg4,
		Int arg5, Int arg6, Int arg7);

private:
	unsigned char m_padding04[0x184 - 4];
	Rva006EE3F0Descriptor *m_descriptor;
	Gen0000D33C *m_product;
};

// ?rva006EE3F0@W3DDisplay@@UAEEPAURva006EE3F0Descriptor@@MMHHHH@Z
Bool W3DDisplay::rva006EE3F0(Rva006EE3F0Descriptor *descriptor, Real arg2, Real arg3, Int arg4,
	Int arg5, Int arg6, Int arg7)
{
	if (m_product != 0)
	{
		delete m_product;
		m_product = 0;
	}

	m_descriptor = descriptor;
	Int pointSize = descriptor->m_pointSize;
	GameFont *font = TheFontLibrary->getFont(&descriptor->m_name,
		(Real)pointSize, 0);
	m_product = new Gen0000D33C(font, arg2, arg3, arg4, arg5, arg6,
		arg7);
	// Preserve product assignment before the descriptor reload.
	_ReadWriteBarrier();

	m_descriptor->resetDisplayed006EE3F0();

	return 1;
}
