// ??0TeamPrototype@@QAE@PAVTeamFactory@@ABVAsciiString@@1PAVPlayer@@_NPAVDict@@H@Z
// partial score=0.25 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1TeamFactory@@UAE@XZ: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?clear@TeamFactory@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamFactory's default constructor, lifted from its MASM dump to C++.
//
// Retail body @ 0x000F2250 (130B):
//   - calls SubsystemInterface::SubsystemInterface() (0x009A1A30, already
//     matched in Code/GameEngine/Source/Common/System/SubsystemInterface.cpp)
//     to build the first base (vptr + AsciiString m_name, 8 bytes @ +0x00).
//   - inlines a second, trivial base ctor (no call reaches the bytes) that
//     just stores its own identity vptr @ +0x08 -- this is Snapshot, whose
//     real ctor (Common/System/Snapshot.cpp) is an empty {} body, so the
//     compiler folds it away and only its vptr store survives.
//   - stores TeamFactory's own vtables over both subobjects (+0x00, +0x08),
//     which only happens because TeamFactory overrides virtuals from each
//     base -- forcing a distinct combined vtable per polymorphic subobject.
//   - default-constructs an STLport std::map member @ +0x0c: allocates a
//     0x1c-byte header node (color + parent/left/right + a 12-byte unused
//     value slot), then links left/right back to itself for an empty tree.
//     The 0x1c node size keys the map by a 2-word (8-byte) type, matching
//     TeamFactoryList.cpp's independently-established finding that BFME's
//     m_prototypes is keyed by pair<NameKeyType,NameKeyType> (not the single
//     NameKeyType key ZH's Team.h declares). The exact key/value C++ types
//     don't affect this constructor's bytes (default ctor never compares
//     keys), only their combined size, so plain ints stand in here.
//   - zero-initializes two trailing Int members @ +0x18 / +0x1c
//     (m_uniqueTeamPrototypeID, m_uniqueTeamID). The map's own third
//     (empty, comparator) word @ +0x14 is a real member but is never
//     written -- an empty functor has no state to store.
//
// Object layout: SubsystemInterface(0x08) + Snapshot(0x04) + map(0x0c) +
// 2 Ints(0x08) = 0x20 total.
//
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>		// before PreRTS.h so STLport node_alloc is used (not NEWALLOC)

// Modelled first base: only its ABI shape (vptr + one pointer-sized data
// member) and its ctor's mangled name matter here -- the real body lives in
// Code/GameEngine/Source/Common/System/SubsystemInterface.cpp (already
// matched), so the ctor below is declared, never defined, and resolves
// there as an external call.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

private:
	void *m_name;
};

// Modelled second base: matches Snapshot's shape. Its ctor is trivial and
// defined right here (inline) so the compiler folds the call away, exactly
// as retail's bytes show -- only the resulting vptr store reaches the
// target function.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	// Defined inline for the same reason the constructor is: retail's
	// ~TeamFactory @0x000F7512 restores this subobject's vtable and then calls
	// only ~SubsystemInterface, so Snapshot's destructor is folded away too.
	virtual ~Snapshot() {}

	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);
};

// The map's value is anonymous in retail; the ledger already carries its
// _Rb_tree instantiation under the generated payload name gen_dump.py minted
// for it, so use that name and the destructor resolves to the matched row.
// The map is keyed by a two-word key with a plain pointer value, not by an int
// with an eight-byte value: addTeamPrototypeToList @0x000F3DA0 builds the key
// from two NAMEKEY calls before looking it up. Both shapes give the same 0x1C
// node, which is why the constructor, destructor and clear all match either
// way - only a body that uses the key can tell them apart.
// Enough of BFME's StringBase/AsciiString pair to reproduce the two member
// copies. The copy constructor is declaration-only: the matched StringBase
// body is the retail 0x00887B60 implementation, while the layout below keeps
// this TU independent of the shared header's other inline methods.
template <typename T> class StringBase
{
public:
	const T *str(void) const
	{
		return m_data ? ((const T *)m_data + 8) : (const T *)"";
	}

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);

private:
	void *m_data;
};

extern void j_0000d828(void);

// The constructor's generic-script array is initialized by the retail vector
// helper with these exact ILT arguments. Keep the element ABI declaration-only
// and route it to the existing thunks; no lifted body is introduced here.
class TeamPrototypeArrayString
{
public:
	TeamPrototypeArrayString();
	~TeamPrototypeArrayString();

private:
	void *m_data;
};
#pragma comment(linker, "/alternatename:??0TeamPrototypeArrayString@@QAE@XZ=?j_00017bd9@@YAXXZ")
#pragma comment(linker, "/alternatename:??1TeamPrototypeArrayString@@QAE@XZ=?j_0000d828@@YAXXZ")

// Enough of AsciiString to reproduce str(): retail inlines it as
// `p ? p + 8 : ""` at 0x000F3DAA and 0x000F3DCA.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_base() {}
	AsciiString(const AsciiString &other)
		: m_base(*(const StringBase<char> *)&other) {}
	~AsciiString()
	{
		typedef void (AsciiString::*Destroy)(void);
		union { void (*raw)(void); Destroy member; } target;
		target.raw = j_0000d828;
		(this->*target.member)();
	}
	const char *str(void) const { return m_base.str(); }

private:
	StringBase<char> m_base;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Dict;
class TeamPrototype;
class Player
{
public:
};
class Team;
class TeamFactory;

// TeamTemplateInfo is laid out at TeamPrototype+0x12c in the BFME build.  Its
// real constructor is the existing matched retail thunk; this TU only needs
// its size and ABI so the TeamPrototype constructor can call it normally.
class TeamTemplateInfoLayout
{
public:
private:
	char m_body[0x144];
};

// getNeutralPlayer is inlined at 0x000F81D3 as a read of this+0x14.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType nk);
	Player *m_pad[5];
	Player *m_neutral;	// +0x14
};
extern PlayerList *ThePlayerList;

// The two AsciiStrings the key is built from sit at +0x10 and +0x14.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	virtual ~TeamPrototype();
	// Seven parameters: 0x000F81FB-0x000F8210 pushes owner and name as two
	// separate strings, in that order, exactly like findTeamPrototype.
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
				Player *pOwner, bool isSingleton, Dict *d, int id);

	TeamFactory *m_factory;                           // +0x04
	Player *m_owningPlayer;                           // +0x08
	unsigned int m_id;                                // +0x0c
	AsciiString m_first;                              // +0x10
	AsciiString m_second;                             // +0x14
	unsigned int m_flags;                             // +0x18
	unsigned char m_productionConditionAlwaysFalse;   // +0x1c
	unsigned char m_pad20[3];                         // +0x1d
	void *m_productionConditionName;                  // +0x20 (null in ctor)
	void *m_productionConditionScript;                // +0x24
	unsigned char m_retrievedGenericScripts;          // +0x28
	void *m_genericScriptsToRun[0x20];                // +0x2c
	TeamPrototypeArrayString m_genericScriptNames[0x20]; // +0xac
	TeamTemplateInfoLayout m_teamTemplate;             // +0x12c
	void *m_attackPriorityName;                        // +0x270 (null in ctor)
	void *m_teamInstanceList;                         // +0x274
};
typedef std::pair<int, int> BfmeTeamPrototypeKey;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

	void clear(void);
	void addTeamPrototypeToList(TeamPrototype *team);
	// Two parameters, not one: 0x000F8191 pushes both `name` and `owner`
	// before the call, matching the pair-keyed m_prototypes map.
	TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
	void initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d);

protected:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);

private:
	// Keyed by int with an eight-byte value, not by a two-word key: the
	// destructor at 0x000F750B calls
	// _Rb_tree<H, pair<$$CBH, <8 bytes>>>::~_Rb_tree, which names the key type
	// directly. The node is 0x1C either way - 0x10 of links plus a 0xC value -
	// so the constructor's bytes are unchanged.
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > m_prototypes;
	int m_uniqueTeamPrototypeID;
	int m_uniqueTeamID;
};

extern void j_000498ff(void);
extern void j_0002c1ce(void);
extern void j_0003d703(void);

// These wrappers only express the existing ILT call ABI. The target member
// functions are declaration-only and their raw addresses are the matched
// thunks, following the established SoundKeyPair/TeamPrototype destructor
// pattern in this source family.
static __forceinline void constructTeamTemplateInfo(TeamTemplateInfoLayout *self, Dict *dict)
{
	typedef void (TeamTemplateInfoLayout::*Ctor)(Dict *);
	union { void (*raw)(void); Ctor member; } target;
	target.raw = j_000498ff;
	(self->*target.member)(dict);
}

static __forceinline void addTeamPrototypeViaRetailThunk(TeamFactory *self, TeamPrototype *team)
{
	typedef void (TeamFactory::*Action)(TeamPrototype *);
	union { void (*raw)(void); Action member; } target;
	target.raw = j_0003d703;
	(self->*target.member)(team);
}

static __forceinline void addPlayerTeamViaRetailThunk(Player *self, TeamPrototype *team)
{
	typedef void (Player::*Action)(TeamPrototype *);
	union { void (*raw)(void); Action member; } target;
	target.raw = j_0002c1ce;
	(self->*target.member)(team);
}

// ??0TeamPrototype@@QAE@PAVTeamFactory@@ABVAsciiString@@1PAVPlayer@@_NPAVDict@@H@Z
TeamPrototype::TeamPrototype(TeamFactory *tf, const AsciiString &owner,
	const AsciiString &name, Player *pOwner, bool isSingleton, Dict *d, int id)
	: m_factory(tf),
	  m_owningPlayer(pOwner),
	  m_id(id),
	  m_first(owner),
	  m_second(name),
	  m_flags(isSingleton ? 1u : 0u),
	  m_productionConditionAlwaysFalse(0),
	  m_pad20(),
	  m_productionConditionName(0),
	  m_productionConditionScript(0),
	  m_retrievedGenericScripts(0),
	  m_genericScriptsToRun(),
	  m_genericScriptNames(),
	  m_attackPriorityName(0),
	  m_teamInstanceList(0)
{
	constructTeamTemplateInfo(&m_teamTemplate, d);
	if (m_factory)
		addTeamPrototypeViaRetailThunk(m_factory, this);
	if (m_owningPlayer)
		addPlayerTeamViaRetailThunk(m_owningPlayer, this);
}

// ??0TeamFactory@@QAE@XZ
TeamFactory::TeamFactory()
	: m_uniqueTeamPrototypeID(0), m_uniqueTeamID(0)
{
}

// BFME nulls its singleton in the destructor; the store lands between clear()
// and the map teardown at 0x000F7500.
extern TeamFactory *TheTeamFactory;

// ??1TeamFactory@@UAE@XZ
TeamFactory::~TeamFactory()
{
	clear();
	TheTeamFactory = NULL;
}

// ?clear@TeamFactory@@QAEXXZ
void TeamFactory::clear()
{
	// must remove it from the map before deleting the TeamProto, since
	// the TeamProto will try to remove itself from the list when it goes away
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > tmp = m_prototypes;
	m_prototypes.clear();
	for (std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> >::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		delete it->second;
	}
}

// ?addTeamPrototypeToList@TeamFactory@@QAEXPAVTeamPrototype@@@Z
void TeamFactory::addTeamPrototypeToList(TeamPrototype *team)
{
	BfmeTeamPrototypeKey nk(TheNameKeyGenerator->nameToKey(team->m_first.str()),
									TheNameKeyGenerator->nameToKey(team->m_second.str()));
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> >::iterator it = m_prototypes.find(nk);
	if (it != m_prototypes.end())
		return;

	m_prototypes[nk] = team;
}

// ?initTeam@TeamFactory@@QAEXABVAsciiString@@0_NPAVDict@@@Z
void TeamFactory::initTeam(const AsciiString &name, const AsciiString &owner, bool isSingleton, Dict *d)
{
	// BFME returns early instead of asserting: 0x000F8195 calls
	// findTeamPrototype and jumps to the epilogue when it is non-null.
	if (findTeamPrototype(owner, name) != 0)
		return;

	Player *pOwner = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(owner.str()));
	if (!pOwner)
		pOwner = ThePlayerList->m_neutral;

	TeamPrototype *proto = new TeamPrototype(this, owner, name, pOwner, isSingleton, d,
												++m_uniqueTeamPrototypeID);

	// Retail re-reads the two strings off the prototype it just built
	// (proto+0x10 and proto+0x14) rather than reusing the parameters.
	if (isSingleton)
		createInactiveTeam(proto->m_first, proto->m_second);
}
