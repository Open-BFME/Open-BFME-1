// ?setTeam@Object@@UAEXPAVTeam@@@Z
// partial score=0.36 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Object::setTeam(Team *team), retail 0x001C6F10, size 346.
// Identity: Object's own vtable slot +0x50 dispatches here, and the
// constructor's caller at 0x001D29A0 names the setTeam call. Field offsets
// m_team (+0x23c), m_contain (+0x1fc) and m_partitionData (+0x3b0) are
// proven by reference/shims/bfmeobject/GameLogic/Object.h's accessor-body
// notes. The vtable slots dispatched here (+0x54 on `this`, +0x68/+0x140 on
// m_contain's interface, +0x28/+0x34 on `this` again) are not otherwise
// named, so they stay address-derived pad slots.

typedef bool Bool;
typedef int Int;

class Player
{
public:
	Bool isPlayerActive() const;			// pinned retail 0x000C9D10
};

class Team
{
public:
	Player *getControllingPlayer() const;		// pinned retail 0x000EC8F0
};

class ThePlayerListType
{
public:
	unsigned char m_pad[0x14];
	unsigned char *m_field14;
};
extern ThePlayerListType *ThePlayerList;		// VA 0x012ED748

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }
	void set(const BFMERetailAsciiString &other);		// retail 0x00887C90
	void concat(const char *text, int len);		// retail 0x00887D60

private:
	void releaseBuffer();					// retail 0x00887940
	void *m_data;
};

extern const char g_bfmeRva01336E50Str[];			// VA 0x01336E50
extern const char g_bfmeRva0107388BStr[];			// VA 0x0107388B

class PartitionData
{
public:
	void makeDirty();					// retail 0x008F7B30
};

class Rva009F2BA0
{
public:
	void init();						// retail 0x009F2BA0
};

class Rva009A2350
{
public:
	void init();						// retail 0x009A2350
};

class Radar;
extern Radar *TheRadar;					// VA 0x012EF0E4
void __cdecl Rva0011383RadarNotify(Radar *radar, void *object);	// pinned retail 0x00011383

class Rva0012F060COwner;
extern Rva0012F060COwner *g_bfmeOwnerBR;			// VA 0x012F060C
void __cdecl Rva00358ANotify(Rva0012F060COwner *owner, void *object);	// pinned retail 0x0000358A
void __cdecl Rva0143D0Notify(Rva0012F060COwner *owner, void *object);	// pinned retail 0x000143D0

// The object m_contain's slot 0x68 returns.
class Rva0140Interface
{
public:
	virtual void pad0();
	virtual void pad4();
	virtual void pad8();
	virtual void padC();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1C();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2C();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3C();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4C();
	virtual void pad50();
	virtual void pad54();
	virtual void pad58();
	virtual void pad5C();
	virtual void pad60();
	virtual void pad64();
	virtual void pad68();
	virtual void pad6C();
	virtual void pad70();
	virtual void pad74();
	virtual void pad78();
	virtual void pad7C();
	virtual void pad80();
	virtual void pad84();
	virtual void pad88();
	virtual void pad8C();
	virtual void pad90();
	virtual void pad94();
	virtual void pad98();
	virtual void pad9C();
	virtual void padA0();
	virtual void padA4();
	virtual void padA8();
	virtual void padAC();
	virtual void padB0();
	virtual void padB4();
	virtual void padB8();
	virtual void padBC();
	virtual void padC0();
	virtual void padC4();
	virtual void padC8();
	virtual void padCC();
	virtual void padD0();
	virtual void padD4();
	virtual void padD8();
	virtual void padDC();
	virtual void padE0();
	virtual void padE4();
	virtual void padE8();
	virtual void padEC();
	virtual void padF0();
	virtual void padF4();
	virtual void padF8();
	virtual void padFC();
	virtual void pad100();
	virtual void pad104();
	virtual void pad108();
	virtual void pad10C();
	virtual void pad110();
	virtual void pad114();
	virtual void pad118();
	virtual void pad11C();
	virtual void pad120();
	virtual void pad124();
	virtual void pad128();
	virtual void pad12C();
	virtual void pad130();
	virtual void pad134();
	virtual void pad138();
	virtual void pad13C();
	virtual void slot140(Team *team);
};

class ContainInterface
{
public:
	virtual void pad0();
	virtual void pad4();
	virtual void pad8();
	virtual void padC();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1C();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2C();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3C();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4C();
	virtual void pad50();
	virtual void pad54();
	virtual void pad58();
	virtual void pad5C();
	virtual void pad60();
	virtual void pad64();
	virtual Rva0140Interface *slot68();
};

// The object Object's own slot 0x28 returns.
class Rva34Interface
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14(); virtual void pad18(); virtual void pad1C();
	virtual void pad20(); virtual void pad24(); virtual void pad28(); virtual void pad2C();
	virtual void pad30();
	virtual void slot34();
};

class Object
{
public:
	virtual void pad0();
	virtual void pad4();
	virtual void pad8();
	virtual void padC();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1C();
	virtual void pad20();
	virtual void pad24();
	virtual Rva34Interface *pad28();
	virtual void pad2C();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3C();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4C();
	virtual void setTeam(Team *team);
	virtual void pad54(Team *team);
	void updateUpgradeModules();			// retail 0x00427FCF

private:
	unsigned char m_pad004[0x1fc - 4];
	ContainInterface *m_contain;			// +0x1fc
	unsigned char m_pad200[0x23c - 0x200];
	Team *m_team;					// +0x23c
	BFMERetailAsciiString m_originalTeamName;	// +0x240
	unsigned char m_pad244[0x3b0 - 0x244];
	PartitionData *m_partitionData;		// +0x3b0
	Rva009F2BA0 *m_field3b4;
	Rva009A2350 *m_field3b8;
};

void Object::setTeam(Team *team)
{
	if (team && !team->getControllingPlayer()->isPlayerActive())
		team = *(Team **)(ThePlayerList->m_field14 + 0x230);

	pad54(team);

	Team *newTeam = m_team;
	if (newTeam)
	{
		const char *namePtr = *(const char **)((unsigned char *)newTeam + 4);
		if (!namePtr)
			namePtr = g_bfmeRva01336E50Str;
		else
			namePtr += 0x10;

		m_originalTeamName.set(*(const BFMERetailAsciiString *)&namePtr);
		m_originalTeamName.concat("/", 1);

		const char *labelPtr = *(const char **)((unsigned char *)newTeam + 4);
		if (!labelPtr)
			labelPtr = g_bfmeRva01336E50Str;
		else
			labelPtr += 0x14;

		const char *header = *(const char **)labelPtr;
		if (header)
		{
			unsigned short len = *(const unsigned short *)(header + 4);
			m_originalTeamName.concat(header + 8, len);
		}
		else
		{
			m_originalTeamName.concat(g_bfmeRva0107388BStr, 0);
		}
	}
	else
	{
		m_originalTeamName.set(*(const BFMERetailAsciiString *)&g_bfmeRva01336E50Str);
	}

	if (m_partitionData)
		m_partitionData->makeDirty();
	if (m_field3b4)
		m_field3b4->init();
	if (m_field3b8)
		m_field3b8->init();

	if (g_bfmeOwnerBR)
	{
		Rva00358ANotify(g_bfmeOwnerBR, this);
		Rva0143D0Notify(g_bfmeOwnerBR, this);
	}

	if (team)
	{
		if (m_contain)
		{
			Rva0140Interface *interfacePtr = m_contain->slot68();
			if (interfacePtr)
				interfacePtr->slot140(team);
		}

		if (TheRadar)
			Rva0011383RadarNotify(TheRadar, this);
	}

	updateUpgradeModules();

	Rva34Interface *result = pad28();
	if (result)
		result->slot34();
}
