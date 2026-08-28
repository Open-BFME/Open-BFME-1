// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: UnitCrateCollideModuleData's constructor, retail 0x002F1B10, 87
// bytes, from the zh_sweep packet for that address.
//
// The Snapshot base runs, the derived vtable goes over it, the byte at +0x08 is
// cleared and the AsciiString at +0x0C -- nulled by its own constructor first --
// is assigned from a global. That global is pinned with this row; the packet
// left it unresolved because the sweep blanks relocation slots before comparing.
//
// The unwind slot is written twice, 0 for the base and 1 once the string is
// standing, because the assignment is a call that can throw.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_bfmeData = 0; }
	~AsciiString();

	AsciiString &operator=(const AsciiString &other);	// retail 0x00887C90

private:
	char *m_bfmeData;
};

extern AsciiString TheBfmeCrateNameDefault;			// 0x01336E50

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();						// retail 0x009A1A30
	~Snapshot();

	virtual void bfmeSlot0(void);

private:
	char m_bfmePad[0x08 - 0x04];
};

class Gen_002F1B10 : public Snapshot
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
