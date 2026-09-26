// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2
// TeamPrototype::~TeamPrototype at retail RVA 0x000F6E40.
// The BFME object layout is established by the matched TeamPrototype walks,
// TeamFactory list erase, and the sibling constructor at 0x000F3E40.

class TeamPrototype;
class Team;

extern void deleteTeamCallback(Team *team);

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class Player
{
};

class TeamFactory
{
public:
	void removeTeamPrototypeFromList(TeamPrototype *team);
};

class Script
{
public:
	virtual ~Script() { }
};

class TeamTemplateInfo
{
public:
	~TeamTemplateInfo();

private:
	unsigned char m_body[0x144];
};

extern void j_0004b367();

// The retail thunk is the named Player::removeTeamFromList call target, but
// its old neutral thunk spelling is already owned by the matched import row.
// Keep the canonical Player receiver/argument types local while routing the
// call through that existing thiscall thunk without adding a competing pin.
static __forceinline void playerRemoveTeamFromList(Player *player, TeamPrototype *team)
{
	typedef void (Player::*MemberThunk)(TeamPrototype *);
	union
	{
		void (*function)(void);
		MemberThunk member;
	} thunk;
	thunk.function = j_0004b367;
	(player->*thunk.member)(team);
}
#pragma comment(linker, "/alternatename:?removeTeamPrototypeFromList@TeamFactory@@QAEXPAVTeamPrototype@@@Z=?j_00038677@@YAXXZ")
#pragma comment(linker, "/alternatename:??1TeamTemplateInfo@@QAE@XZ=?j_00022b97@@YAXXZ")
#pragma comment(linker, "/alternatename:?removeAll_TeamInstanceList@TeamPrototype@@QAEXP6AXPAVTeam@@@Z@Z=?j_00040714@@YAXXZ")

// TeamPrototype is a memory-pool object in the shipped Team.h.  Its protected
// virtual base destructor is also what makes the retail body restore the
// MemoryPoolObject vtable at the end of this destructor.
class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject() { }
};

class TeamPrototype : public MemoryPoolObject
{
	// MEMORY_POOL_GLUE makes the virtual destructor protected in the retail
	// declaration; the out-of-class definition below remains well-formed.
	protected:
	virtual ~TeamPrototype();

	public:
	virtual void bfmeUnusedVirtual();
	virtual const char *getName() const;
	virtual void xfer(void *xfer);

private:
	void *m_factory;                                  // +0x04
	Player *m_owningPlayer;                           // +0x08
	unsigned int m_id;                                // +0x0c
	BFMERetailAsciiString m_name;                     // +0x10
	BFMERetailAsciiString m_ownerName;                // +0x14
	unsigned int m_flags;                             // +0x18
	unsigned char m_productionConditionAlwaysFalse;   // +0x1c
	unsigned char m_pad20[3];                         // +0x1d
	BFMERetailAsciiString m_productionConditionName;  // +0x20
	Script *m_productionConditionScript;              // +0x24
	unsigned char m_retrievedGenericScripts;          // +0x28
	Script *m_genericScriptsToRun[0x20];               // +0x2c
	BFMERetailAsciiString m_genericScriptNames[0x20]; // +0xac
	TeamTemplateInfo m_teamTemplate;                  // +0x12c
	BFMERetailAsciiString m_attackPriorityName;       // +0x270
	void *m_teamInstanceList;                          // +0x274

public:
	void removeAll_TeamInstanceList(void (*callback)(Team *));
};

// ??1TeamPrototype@@MAE@XZ
TeamPrototype::~TeamPrototype()
{
	removeAll_TeamInstanceList(deleteTeamCallback);

	if (m_owningPlayer)
		playerRemoveTeamFromList(m_owningPlayer, this);

	if (m_factory)
		reinterpret_cast<TeamFactory *>(m_factory)->removeTeamPrototypeFromList(this);

	if (m_productionConditionScript)
	{
		delete m_productionConditionScript;
	}
	m_productionConditionScript = 0;

	for (int i = 0; i < 0x20; ++i)
	{
		if (m_genericScriptsToRun[i])
		{
			delete m_genericScriptsToRun[i];
			m_genericScriptsToRun[i] = 0;
		}
	}
}
