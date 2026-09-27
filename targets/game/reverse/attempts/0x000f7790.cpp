// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// partial score=0.74 date=2026-09-27
// stlport
// Retail's two container allocations are direct calls to the
// ?allocate@__new_alloc@_STL@@SAPAXI@Z body (0x0082E540) with the NODE SIZE
// already scaled, which is STLport's _STLP_USE_NEWALLOC path with static
// linkage; the default pthread-flavoured allocator emits an indirect
// __imp_?-form call six bytes long instead.  See
// game/GameEngine/Source/Common/RTS/ResourceGatheringManagerLists.cpp for the
// other half of that measurement.
//
// ??0Team@@QAE@PAVTeamPrototype@@I@Z, retail RVA 0x000F7790 (631 bytes).
//
// The public Team declaration in Team.cpp is the Zero Hour layout, and it
// already defines Team::Team for it.  BFME's constructor is a different object:
// proven by the vtable store at +0x00, the two relation pointers written by
// `new` at +0xec/+0xf0, the three STLport members inlined at +0x1c (bucket
// table initialised with 100), +0x100 (12-byte list node) and +0x104 (20-byte
// set node with a count at +0x108), and the instance-list splice through
// +0x10/+0x14.  TeamDestructorThunk.cpp carries the matching BFME view of the
// same class; the two cannot be one TU, for the same reason.
//
// The three container members are the real STLport ones rather than
// hand-written stand-ins, because their constructors are what retail inlines:
// _List_base's 12-byte sentinel, _Rb_tree_base's 20-byte header plus
// _M_node_count, and hashtable's vector<_M_buckets> + count proxy behind
// _M_initialize_buckets(100).  Each was hand-modelled first and none of them
// reproduced the retail operand order; the vendored headers do.
//
// MEASURED STATE: 631 bytes, exactly retail's length, and the first 0x17A bytes
// are byte-identical.  162 non-relocation bytes still differ, all of them inside
// the `if (proto)` body (0x17A-0x24E), and probe.py scores the instruction
// stream at 0.967.  Two register-scheduling residues cause all of it:
//
//   1. The instance-list splice.  Retail reads m_teamInstanceList three times
//      (cmp [edi+0x274],esi / mov edx / mov eax) and stores the first read
//      through edx; this source has the compiler carry one read in eax into the
//      store and reload only once.  Tried and disproved: nesting the three
//      guards, moving the splice into an in-class method, reading the head
//      through an inline accessor, and making TeamPrototype polymorphic (to
//      change the alias class) all leave the codegen unchanged.  That is four
//      bytes of length in the block, which is why the block after it lands 4
//      bytes early.
//   2. Knock-on register pressure from (1): `&proto->m_name` picks edx here and
//      eax in retail, and m_ownerName.m_data is loaded twice (eax then edx)
//      where retail loads it once into edi.
//
// The state numbering is not a guess: tools/eh_info.py 0x000F7790 reads retail's
// FuncInfo (0x00DE9494) with nine unwind states, whose cleanups are
// ??1Snapshot@@UAE@XZ on `this`, ??1AsciiString@@QAE@XZ on [this]+0x18,
// a vector<unsigned> dtor on [this]+0x1c+4 (the hashtable's _M_buckets), the
// hash dtor on +0x1c, the list dtor on +0x100, the set dtor on +0x104,
// operator delete twice and the local AsciiString.  That fixes the primary
// base (Snapshot), makes +0x18 an AsciiString rather than a void pointer, and
// is why the body stores states 2/3/4/5/6/7/8 exactly where retail does.

#include <list>
#include <set>
#include <hash_map>

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// The narrow string model.  Layout is WWLib's StringBase<char>: a pointer to
// { ref_count, length, capacity, text }, which puts the length word at +4 and
// the text at +8 -- the two operands retail reads at the call site.  The copy
// ctor, dtor, str() and isEmpty() are inline because retail inlines all four
// here (0x00887B60 and 0x00887940 stay out of line, called directly).
template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void concat(const T *str, int len);
	void releaseBuffer();

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &src);
	~StringBase() { releaseBuffer(); }

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? m_data->data : ""; }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	void concat(const char *other, int len) { StringBase<char>::concat(other, len); }
};

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
		if (proto->m_teamInstanceList != this && m_previous == 0 && m_next == 0)
		{
			m_next = proto->m_teamInstanceList;
			if (proto->m_teamInstanceList)
				proto->m_teamInstanceList->m_previous = this;
			proto->m_teamInstanceList = this;
		}

		// Only keep track of enemy sighted if there is a script that cares.
		if (!proto->m_scriptOnEnemySighted.isEmpty() || !proto->m_scriptOnAllClear.isEmpty())
			m_checkEnemySighted = true;

		AsciiString teamName(proto->m_name);
		teamName.concat("/", 1);
		teamName.concat(proto->m_ownerName.str(), proto->m_ownerName.getLength());
		teamName.concat(" - creating team instance.", 26);
		TheScriptEngine->AppendDebugMessage(teamName, false);
	}

	for (int i = 0; i < 32; ++i)
	{
		m_shouldAttemptGenericScript[i] = true;
		m_genericScriptsToRun[i] = 0;
	}
}
