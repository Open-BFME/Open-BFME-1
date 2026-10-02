// Open-BFME5 conversions: a panel teardown.

struct Bfme5UniHeader
{
	int m_bfmeRefCount;
	unsigned short m_bfmeLength;
	unsigned short m_bfmeAllocated;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	void set(const UnicodeString &s);

	Bfme5UniHeader *m_bfmeData;
};

// Retail's pushed object at 0x01336E50 is WWLib's exported
// ?TheEmptyString@AsciiString@@2V1@B (ascii_string.h:18), whose one definition
// is the const out-of-line copy in
// game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_initTimes.cpp.
// The name here was address-derived; the local view is the TU's UnicodeString.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Bfme5PanelOwner
{
public:
	virtual void bfmeVM0();
	virtual void bfmeVM1();
	virtual void bfmeVM2();
	virtual void bfmeVM3();
	virtual void bfmeVM4();
	virtual void bfmeVM5();
	virtual void bfmeVM6();
	virtual void bfmeDetach();
};

class Bfme5Panel
{
public:
	void bfmeClear(void);

	char m_bfmePad0[0x14];
	UnicodeString m_bfmeText;
	char m_bfmePad1[0x548];
	Bfme5PanelOwner *m_bfmeOwner;
};

void Bfme5Panel::bfmeClear(void)
{
	if (m_bfmeOwner) {
		m_bfmeOwner->bfmeDetach();
		m_bfmeOwner = 0;
	}

	if (m_bfmeText.m_bfmeData && m_bfmeText.m_bfmeData->m_bfmeLength != 0)
		m_bfmeText.set((const UnicodeString &)AsciiString::TheEmptyString);
}
