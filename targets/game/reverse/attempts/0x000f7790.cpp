// ??0Team@@QAE@PAVTeamPrototype@@I@Z
// partial score=1.0 date=2026-09-30
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME Team constructor at 0x000F7790. Matched TeamFactoryCreate.cpp callers
// establish identity; retail EH FuncInfo 0x00DE9494 establishes Snapshot and
// member lifetime order. Team.cpp uses the incompatible Zero Hour layout.
#include <list>
#include <set>
#include <hash_map>

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}
template<> inline void StringBase<char>::concat(const StringBase<char> &other)
{
	concat(other.str(), other.getLength());
}

// Retail's unwind map (FuncInfo 0x00DE9494, read with tools/eh_info.py) opens
// with a state whose only action is the primary base destructor on `this`
// (??1Snapshot@@UAE@XZ at 0x0005C520), so Team's primary base is Snapshot and
// its destructor is virtual.  The base constructor is the implicit one, so the
// only code it contributes is the vptr store MSVC folds into the one at +0x00.
class Snapshot
{
public:
	virtual ~Snapshot();
};

class Xfer;

// BFME's relation pools are one polymorphic base, unlike the later Zero Hour
// MemoryPoolObject + Snapshot pair.  Both pools are 0x18 bytes: retail pushes
// 0x18 for each `new` (0x000F77A7 and 0x000F77B7), and 0x14 of that is the
// 20-byte hash table the constructor twin models.
class TeamRelationPoolObject
{
public:
	virtual ~TeamRelationPoolObject() {}
};

class TeamRelationMap : public TeamRelationPoolObject
{
public:
	TeamRelationMap();
	virtual ~TeamRelationMap();

private:
	unsigned char m_mapStorage[0x14];
};

class Rva000DA590PoolObject
{
public:
	virtual ~Rva000DA590PoolObject() {}
};

class Rva000DA590Map : public Rva000DA590PoolObject
{
public:
	Rva000DA590Map();
	virtual ~Rva000DA590Map();

private:
	unsigned char m_mapStorage[0x14];
};

class Team;
class ScriptEngine;

// The scripted-slot scripts live at +0x1a8 and +0x1ac: two narrow strings the
// constructor only tests for emptiness, so only the data pointers are named.
// The scripted-slot scripts live at +0x1a8 and +0x1ac: two narrow strings the
// constructor only tests for emptiness, so only the data pointers are named.
class TeamPrototype
{
public:
	unsigned char m_pad00[0x10];

	AsciiString m_name;					// +0x10
	AsciiString m_ownerName;				// +0x14
	unsigned char m_pad18[0x1a8 - 0x18];

	AsciiString m_scriptOnAllClear;		// +0x1a8
	AsciiString m_scriptOnEnemySighted;	// +0x1ac
	unsigned char m_pad1b0[0x274 - 0x1b0];

	Team *m_teamInstanceList;				// +0x274
	inline Bool isInList_TeamInstanceList(Team *o) const;
	inline void prependTo_TeamInstanceList(Team *o);
};

// The relation map value.  Its width is the hashtable's node size, which this
// body never reads; the address-keyed name keeps that claim out of the picture.
class Rva000F7460
{
public:
	unsigned char m_pad[12];
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

extern ScriptEngine *TheScriptEngine;

class Team : public Snapshot
{
public:
	Team(TeamPrototype *proto, UnsignedInt id);
	Bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const
	{
		return *pListHead == this || m_previous || m_next;
	}
	void dlink_prependTo_TeamInstanceList(Team **pListHead)
	{
		m_next = *pListHead;
		if (*pListHead)
			(*pListHead)->m_previous = this;
		*pListHead = this;
	}

protected:
	virtual ~Team() {}

private:
	// The bucket table behind the team/player relation lookups.  100 buckets is
	// this constructor's own choice, not a member default.
	typedef _STL::pair<const UnsignedInt, Rva000F7460> TeamRelationEntry;
	typedef _STL::hash_map<UnsignedInt, Rva000F7460, _STL::hash<UnsignedInt>,
		_STL::equal_to<UnsignedInt>, _STL::allocator<TeamRelationEntry> > RelationHash;

	TeamPrototype *m_proto;					// +0x04
	UnsignedInt m_id;						// +0x08
	void *m_firstMember;					// +0x0c
	Team *m_previous;						// +0x10
	Team *m_next;							// +0x14
	AsciiString m_state;					// +0x18
	RelationHash m_relations;				// +0x1c
	Bool m_enteredOrExited;					// +0x30
	Bool m_active;							// +0x31
	Bool m_seeEnemy;						// +0x32
	Bool m_prevSeeEnemy;					// +0x33
	Bool m_checkEnemySighted;				// +0x34
	Bool m_word35;							// +0x35
	Bool m_word36;							// +0x36
	Bool m_word37;							// +0x37
	UnsignedInt m_destroyThreshold;			// +0x38
	UnsignedInt m_curUnits;					// +0x3c
	UnsignedInt m_wasIdle;					// +0x40
	Bool m_shouldAttemptGenericScript[32];	// +0x44
	void *m_genericScriptsToRun[32];		// +0x64
	Bool m_wordE4;							// +0xe4
	Bool m_wordE5;							// +0xe5
	Bool m_wordE6;							// +0xe6
	Bool m_wordE7;							// +0xe7
	UnsignedInt m_commonAttackTarget;		// +0xe8
	TeamRelationMap *m_teamRelations;		// +0xec
	Rva000DA590Map *m_playerRelations;		// +0xf0
	UnsignedInt m_wordF4;					// +0xf4
	UnsignedInt m_wordF8;					// +0xf8
	Bool m_wordFC;							// +0xfc
	_STL::list<UnsignedInt> m_xferMemberIDList;	// +0x100
	_STL::set<UnsignedInt> m_gateSet;		// +0x104
};

inline Bool TeamPrototype::isInList_TeamInstanceList(Team *o) const
{
	return o->dlink_isInList_TeamInstanceList(&m_teamInstanceList);
}

inline void TeamPrototype::prependTo_TeamInstanceList(Team *o)
{
	if (!isInList_TeamInstanceList(o))
		o->dlink_prependTo_TeamInstanceList(&m_teamInstanceList);
}

// ??0Team@@QAE@PAVTeamPrototype@@I@Z
Team::Team(TeamPrototype *proto, UnsignedInt id) :
	m_proto(proto),
	m_id(id),
	m_firstMember(0),
	m_previous(0),
	m_next(0),
	m_enteredOrExited(false),
	m_active(false),
	m_seeEnemy(false),
	m_prevSeeEnemy(false),
	m_checkEnemySighted(false),
	m_word35(false),
	m_word36(false),
	m_word37(false),
	m_destroyThreshold(0),
	m_curUnits(0),
	m_wasIdle(0),
	m_wordE4(false),
	m_wordE5(false),
	m_wordE6(false),
	m_wordE7(false),
	m_wordF4(0),
	m_wordF8(0),
	m_wordFC(false)
{
	m_commonAttackTarget = 0;

	// allocate new relation map pools
	m_playerRelations = new Rva000DA590Map;
	m_teamRelations = new TeamRelationMap;

	m_relations.clear();

	if (proto)
	{
		proto->prependTo_TeamInstanceList(this);

		// Only keep track of enemy sighted if there is a script that cares.
		if (!proto->m_scriptOnEnemySighted.isEmpty() || !proto->m_scriptOnAllClear.isEmpty())
			m_checkEnemySighted = true;

		AsciiString teamName(proto->m_name);
		teamName.StringBase<char>::concat("/", 1);
		teamName.concat(proto->m_ownerName);
		teamName.StringBase<char>::concat(" - creating team instance.", 26);
		TheScriptEngine->AppendDebugMessage(teamName, false);
	}

	for (int i = 0; i < 32; ++i)
	{
		m_shouldAttemptGenericScript[i] = true;
		m_genericScriptsToRun[i] = 0;
	}
}
