// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: UnitCrateCollideModuleData's constructor, retail 0x002F1B10, 87
// bytes, from the zh_sweep packet for that address.
//
// The GenBase009A1A30 base runs, the derived vtable goes over it, the byte at +0x08 is
// cleared and the AsciiString at +0x0C -- nulled by its own constructor first --
// is assigned from a global. That global is pinned with this row; the packet
// left it unresolved because the sweep blanks relocation slots before comparing.
//
// The unwind slot is written twice, 0 for the base and 1 once the string is
// standing, because the assignment is a call that can throw.

#include "ascii_string.h"

extern AsciiString TheBfmeCrateNameDefault;			// 0x01336E50

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x009A1A30 here (vptr
// 0x01141640 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. GenBase009A1A30 is the neutral,
// address-derived spelling symbols.csv already pins at that body.
class GenBase009A1A30
{
public:
	GenBase009A1A30();						// retail 0x009A1A30
	~GenBase009A1A30();

	virtual void bfmeSlot0(void);

private:
	char m_bfmePad[0x08 - 0x04];
};

class Gen_002F1B10 : public GenBase009A1A30
{
public:
	Gen_002F1B10();

	virtual void bfmeSlot0(void);

private:
	bool m_bfme08;						// +0x08
	char m_bfmePad09[3];
	AsciiString m_bfmeName;					// +0x0C
};

// ??0Gen_002F1B10@@QAE@XZ present-unmatched
Gen_002F1B10::Gen_002F1B10()
{
	m_bfme08 = false;

	m_bfmeName = TheBfmeCrateNameDefault;
}
