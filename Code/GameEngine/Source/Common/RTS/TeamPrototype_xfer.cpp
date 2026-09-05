// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TeamPrototype::xfer, retail 0x000F7FA0, 368 bytes.
//
// ZH TeamPrototype::xfer with BFME's two-byte XferVersion (1,1), instance
// list at +0x274, attack-priority string at +0x270, production-condition
// bool at +0x1c, TeamTemplateInfo snapshot at +0x12c. Slot +8 true is the
// SAVE path (copies Player+0x24 into the xfer int). Slot +0x10 true is CRC
// and skips the body. Globals ThePlayerList @ 0x012ED748 and TheTeamFactory
// @ 0x012ED810.

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class Snapshot
{
public:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);
};

class AsciiString
{
	void *m_data;
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isSaving();
	virtual void slot03();
	virtual Bool isDoingCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *);
	virtual void slot27();
	virtual void slot28();
	virtual void xferTeamID(UnsignedInt *);
	virtual void xferInt(Int *);
	virtual void xferUnsignedShort(UnsignedShort *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *);
};

class Player
{
public:
	Int m_pad[9];
	Int m_playerIndex;					// +0x24
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
};

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	UnsignedInt m_id;					// +0x08
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class TeamPrototype;

// Pin ?find@Rva002BD630TeamFactory@@QAEPAXH@Z @ 0x00044C2E
class Rva002BD630TeamFactory
{
public:
	void *find(Int teamID);
};

class TeamFactory
{
public:
	Team *createTeamOnPrototype(TeamPrototype *proto);
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head) {}

	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (Team *)((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

struct BfmeTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;

	BfmeTeamInstanceIterator iterate() const
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}
};

class TeamTemplateInfo
{
public:
	unsigned char m_body[0x144];
};

extern PlayerList *ThePlayerList;
extern TeamFactory *TheTeamFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	virtual void xfer(Xfer *xfer);

	void *m_factory;					// +0x04
	Player *m_owningPlayer;				// +0x08
	unsigned char m_mid_00c[0x1c - 0x0c];
	Bool m_productionConditionAlwaysFalse;	// +0x1c
	unsigned char m_mid_01d[0x12c - 0x1d];
	TeamTemplateInfo m_teamTemplate;	// +0x12c
	AsciiString m_attackPriorityName;	// +0x270
	Team *m_teamInstanceList;			// +0x274
};

// ?xfer@TeamPrototype@@UAEXPAVXfer@@@Z
void TeamPrototype::xfer(Xfer *xfer)
{
	if (xfer->isDoingCRC())
		return;

	// Retail frame is 0xC: teamID @ +0, version @ +4, owningPlayerIndex @ +8.
	// Count lives in the dead xfer* argument slot.
	struct Frame
	{
		UnsignedInt teamID;
		XferVersion version;
		Int owningPlayerIndex;
	};
	Frame frame;
	UnsignedShort teamInstanceCount;

	frame.version.m_version = 1;
	frame.version.m_currentVersion = 1;
	xfer->xferVersion(&frame.version);

	if (xfer->isSaving())
		frame.owningPlayerIndex = m_owningPlayer->m_playerIndex;
	xfer->xferInt(&frame.owningPlayerIndex);
	m_owningPlayer = ThePlayerList->getNthPlayer(frame.owningPlayerIndex);

	xfer->xferAsciiString(&m_attackPriorityName);
	xfer->xferBool(&m_productionConditionAlwaysFalse);
	xfer->xferSnapshot((Snapshot *)&m_teamTemplate);

	teamInstanceCount = 0;
	for (BfmeTeamInstanceIterator iter = ((const BfmeTeamPrototypeInstances *)this)->iterate();
		 !iter.done();
		 iter.advance())
		teamInstanceCount++;
	xfer->xferUnsignedShort(&teamInstanceCount);

	if (xfer->isSaving())
	{
		for (BfmeTeamInstanceIterator iter = ((const BfmeTeamPrototypeInstances *)this)->iterate();
			 !iter.done();
			 iter.advance())
		{
			frame.teamID = iter.cur()->m_id;
			xfer->xferTeamID(&frame.teamID);
			xfer->xferSnapshot((Snapshot *)iter.cur());
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < teamInstanceCount; ++i)
		{
			xfer->xferTeamID(&frame.teamID);
			Team *teamInstance = (Team *)((Rva002BD630TeamFactory *)TheTeamFactory)->find((Int)frame.teamID);
			if (teamInstance == 0)
			{
				teamInstance = TheTeamFactory->createTeamOnPrototype(this);
				if (teamInstance)
					teamInstance->m_id = frame.teamID;
			}
			xfer->xferSnapshot((Snapshot *)teamInstance);
		}
	}
}
