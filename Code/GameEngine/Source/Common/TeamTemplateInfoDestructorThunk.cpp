// cl: /DNDEBUG /MD /EHsc

// Twelve destructible members, destroyed in reverse declaration order with the
// unwind state counting down from 0xB.
//
// Two arrays, both spelled out by ??_M, whose arguments are pushed destructor,
// COUNT, size, base -- in that order, which is worth stating because reading the
// middle two the other way round gives four elements of thirty-two bytes rather
// than thirty-two of four. Both spans end in the same place either way, so the
// arithmetic does not catch it: seven twelve-byte elements at +4 ending on +0x58,
// and thirty-two four-byte elements at +0xC4 ending on +0x144.
//
// The name is QAE, so this destructor is not virtual, and the single vptr store
// falls at the very end rather than at entry. Deriving from the polymorphic type
// would put a store at entry too, since a derived class gets its own table. A
// Snapshot MEMBER at offset zero gives one store in the right place: members are
// destroyed in reverse declaration order, so the first-declared one goes last.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class TeamGenericEntry
{
public:
	~TeamGenericEntry();

private:
	unsigned char m_body[0x0C];
};

class TeamWideEntry
{
public:
	~TeamWideEntry();

private:
	unsigned char m_body[0x04];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual void unknownVirtual(void);

	// Declared and empty rather than implicit. An implicit destructor on a
	// polymorphic class is trivial and emits nothing, which loses the vptr
	// store entirely; declaring it makes the member destructible, which is
	// also the twelfth unwind state.
	~Snapshot() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamTemplateInfo
{
public:
	~TeamTemplateInfo();

private:
	Snapshot m_snapshot;
	TeamGenericEntry m_generic[7];
	unsigned char m_gap0[0x14];
	BFMERetailAsciiString m_6c;
	BFMERetailAsciiString m_70;
	BFMERetailAsciiString m_74;
	unsigned char m_gap1[0x04];
	BFMERetailAsciiString m_7c;
	BFMERetailAsciiString m_80;
	BFMERetailAsciiString m_84;
	BFMERetailAsciiString m_88;
	unsigned char m_gap2[0x20];
	BFMERetailAsciiString m_ac;
	BFMERetailAsciiString m_b0;
	unsigned char m_gap3[0x08];
	BFMERetailAsciiString m_bc;
	unsigned char m_gap4[0x04];
	TeamWideEntry m_wide[0x20];
};

// ??1TeamTemplateInfo@@QAE@XZ
TeamTemplateInfo::~TeamTemplateInfo()
{
}
