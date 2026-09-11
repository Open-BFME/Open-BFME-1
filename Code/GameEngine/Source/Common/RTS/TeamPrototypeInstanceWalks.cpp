// cl: /DNDEBUG /MD /EHsc

// Instance-list walks over TeamPrototype+0x274:
//   0x000F6FD0  hasAnyBuildings(Bool)                     59 bytes
//   0x000F7020  hasAnyBuildings(BitFlags<192>, Bool)     117 bytes
//   0x000F70C0  hasAnyObjects(ObjectFilter *, Bool) const 67 bytes
//   0x000F7170  hasAnyObjects(Bool)                       59 bytes
//   0x000ED6C0  findTeamByID(UnsignedInt)                 38 bytes
//   0x000F41A0  damageTeamMembers(Real)                   46 bytes
//   0x000F7FA0  xfer(Xfer *)                             368 bytes
//
// PlayerHasAny.cpp supplies the outer prototype queries. Team.cpp retains
// countTeamInstances and hasAnyUnits. The shared iterator advances through
// ILT 0x00022A70 -> 0x000C8A30; its null guard preserves retail's second test
// before the advance call. Team.cpp still uses the BfmeTeamInstanceLink spelling
// pinned to this same route, while these walks use Team::_bfme_nextInInstanceList.
//
// The TeamPrototype layout includes its vptr: xfer accesses the owning player
// at +0x08, production flag at +0x1C, template at +0x12C and priority string at
// +0x270. findTeamByID reads Team's id at +0x08, after its vptr and prototype.
//
// RefundDie::onDie at 0x00255BE0 settles the formerly unresolved 0x000F70C0
// signature.  It calls Player::hasAnyObjects(ObjectFilter const *, Bool), whose
// exact outer list walk forwards those same two arguments here through ILT
// 0x0002ACC5.  This body then forwards them to Team through ILT 0x0003CCD1.
// The downstream Team body treats the first word as an ObjectFilter receiver
// and the second word's low byte as a flag, independently agreeing with the
// matched caller.  The old BitFlags<116> label was impossible: that type needs
// four dwords, while every boundary in this chain returns with `ret 8`.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

class ObjectFilter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyBuildings(Bool bfmeFlag) const;			// ILT thunk at 0x00017652
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);	// ILT thunk at 0x0003B5B6
	Bool hasAnyObjects(const ObjectFilter *filter, Bool bfmeFlag) const;	// ILT thunk at 0x0003CCD1
	Bool hasAnyObjects(Bool bfmeFlag) const;			// ILT thunk at 0x0001478B
	Bool damageTeamMembers(Real amount);				// ILT 0x0000D148 -> 0x000F33F0

	UnsignedInt getID() const { return m_id; }

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();				// ILT thunk at 0x00022A70

	// Public because xfer both reads the id when saving and writes it into a
	// freshly created instance when loading.
	void *m_vptr;							// +0x00
	void *m_proto;							// +0x04
	UnsignedInt m_id;						// +0x08, BFME dropped ZH's second base vptr
};

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
	BfmeTeamInstanceIterator( Team *head )
		: m_cur( head )
	{
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	Team *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if( m_cur )
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
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
	Bool hasAnyBuildings( Bool bfmeFlag );
	Bool hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag );
	Bool hasAnyObjects( const ObjectFilter *filter, Bool bfmeFlag ) const;
	Bool hasAnyObjects( Bool bfmeFlag );
	Team *findTeamByID( UnsignedInt teamID );
	void damageTeamMembers( Real amount );
	virtual void xfer( Xfer *xfer );				// vptr at +0x00

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	void *m_factory;							// +0x04
	Player *m_owningPlayer;							// +0x08
	unsigned char m_mid_00c[0x1c - 0x0c];
	Bool m_productionConditionAlwaysFalse;					// +0x1C
	unsigned char m_mid_01d[0x12c - 0x1d];
	TeamTemplateInfo m_teamTemplate;					// +0x12C
	AsciiString m_attackPriorityName;					// +0x270
	Team *m_teamInstanceList;						// +0x274
};

// ?hasAnyBuildings@TeamPrototype@@QAE_N_N@Z
Bool TeamPrototype::hasAnyBuildings( Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildings( bfmeFlag ) )
			return true;
	}

	return false;
}

// ?hasAnyBuildings@TeamPrototype@@QAE_NV?$BitFlags@$0MA@@@_N@Z
//
// The mask is six dwords passed by value -- which the `ret 0x1C' accounts for
// together with the flag -- so most of the 117 bytes are the copy the compiler
// builds in the outgoing argument slots on every iteration.
Bool TeamPrototype::hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildings( kindOf, bfmeFlag ) )
			return true;
	}

	return false;
}

// ?hasAnyObjects@TeamPrototype@@QBE_NPBVObjectFilter@@_N@Z
Bool TeamPrototype::hasAnyObjects( const ObjectFilter *filter, Bool bfmeFlag ) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyObjects( filter, bfmeFlag ) )
			return true;
	}

	return false;
}

// ?hasAnyObjects@TeamPrototype@@QAE_N_N@Z
Bool TeamPrototype::hasAnyObjects( Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyObjects( bfmeFlag ) )
			return true;
	}

	return false;
}

// ?findTeamByID@TeamPrototype@@QAEPAVTeam@@I@Z
Team *TeamPrototype::findTeamByID( UnsignedInt teamID )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->getID() == teamID )
			return iter.cur();
	}
	return 0;
}

// ?damageTeamMembers@TeamPrototype@@QAEXM@Z
//
// Team::damageTeamMembers walks Team+0x0C members, skips effectively-dead and
// destroyed ones, and either kills or attempts damage from the amount.
void TeamPrototype::damageTeamMembers( Real amount )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		iter.cur()->damageTeamMembers( amount );
	}
}

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
	for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList();
		 !iter.done();
		 iter.advance())
		teamInstanceCount++;
	xfer->xferUnsignedShort(&teamInstanceCount);

	if (xfer->isSaving())
	{
		for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList();
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
