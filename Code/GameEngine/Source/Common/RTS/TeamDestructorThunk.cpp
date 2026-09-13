// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// ??1Team@@MAE@XZ, retail RVA 0x000F4250 (480 bytes).
//
// The public Team declaration is the Zero Hour layout.  BFME's constructor,
// Team.cpp's BFME views, and the destructor's own field operands establish a
// different object: the member list is at +0x0c, the two relation pointers at
// +0xec/+0xf0, and the transfer-list/gate-set pair at +0x100/+0x104.  Keep
// those views in this TU so the shared Team ABI is not changed.

typedef unsigned int UnsignedInt;

class Team;
class Player;
class ScriptEngine;

// The calls below are incremental-link thunks at the exact retail call sites.
// The receiver and argument types are carried by the local shims; their
// address-derived names do not claim an unproven source-level callee.
extern void j_00042910();
extern void j_0000e6b5();
extern void j_00044f30();
extern void j_00014dcb();
extern void j_0001e416();
extern void j_0001f1bd();
extern void j_0001fe2e();
extern void j_00049eb8();

class Rva000F4250ScriptCall
{
public:
	void notify( Team *team );
};

class Rva000F4250GateCall
{
public:
	void set( UnsignedInt gateID, UnsignedInt open );
};

class Rva000F4250PlayerListCall
{
public:
	Player *getNthPlayer( int index );
};

class Rva000F4250PlayerCall
{
public:
	void preTeamDestroy( const Team *team );
};

class Rva000F4250PrototypeCall
{
public:
	void remove( Team *team );
};

class Rva000F4250Hash
{
public:
	void clear();
	void destroy();
	~Rva000F4250Hash() { destroy(); }

private:
	unsigned char m_storage[ 0x14 ];
};

class Rva000F4250GateSet
{
public:
	void destroy();
	~Rva000F4250GateSet() { destroy(); }

	struct TreeHeader;
	TreeHeader *m_tree;
	UnsignedInt m_count;
};

struct Rva000F4250GateSet::TreeHeader
{
	unsigned char m_pad[ 8 ];
	struct Node *m_root;
};

struct Rva000F4250GateSetNode
{
	unsigned char m_pad[ 0x10 ];
	UnsignedInt m_gateID;
};

// The Object virtual used by Team::~Team is slot 20 (+0x50).  The preceding
// slots are intentionally unnamed: the destructor only establishes the slot
// and does not establish those source-level method identities.
class Rva000F4250MemberCall
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void setTeam( Team *team ) = 0;
};

class Rva000F4250RelationMap
{
public:
	virtual void destroy( UnsignedInt deleting );
};

// The transfer list deliberately has a non-trivial destructor.  Team's
// explicit clear() is the first walk in retail; its implicit member dtor is
// the second walk and then releases the 0xc-byte sentinel.  Keeping both as
// ordinary C++ lifetime operations reproduces the observed EH states.
namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *node, UnsignedInt bytes );
};
}

struct Rva000F4250TransferNode
{
	Rva000F4250TransferNode *m_next;
	Rva000F4250TransferNode *m_previous;
};

class Rva000F4250TransferList
{
public:
	void clear()
	{
		Rva000F4250TransferNode *node = m_node->m_next;
		while (node != m_node)
		{
			Rva000F4250TransferNode *old = node;
			node = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate( old, 0xc );
		}
		m_node->m_next = m_node;
		m_node->m_previous = m_node;
	}

	~Rva000F4250TransferList()
	{
		Rva000F4250TransferNode *node = m_node->m_next;
		while (node != m_node)
		{
			Rva000F4250TransferNode *old = node;
			node = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate( old, 0xc );
		}
		m_node->m_next = m_node;
		m_node->m_previous = m_node;
		if (m_node != 0)
			_STL::__node_alloc<true, 0>::_M_deallocate( m_node, 0xc );
	}

	Rva000F4250TransferNode *m_node;
};

// This is the one-pointer BFME StringBase object at Team+0x18.  Its private
// releaseBuffer spelling is already pinned to the canonical WWLib body.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

// Only the fields used by this destructor are laid out on the global objects.
class ScriptEngine
{
};

class PlayerList
{
public:
	unsigned char m_pad[ 0x10 ];
	int m_playerCount;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class Rva000F4250TeamPrototype
{
public:
	unsigned char m_pad[ 0x274 ];
	Team *m_teamInstanceList;
};

class BfmeBaseVUQ
{
protected:
	virtual ~BfmeBaseVUQ() {}
};

class Team : public BfmeBaseVUQ
{
protected:
	virtual ~Team();
	Rva000F4250MemberCall *getFirstItemInTeamMemberList() const
	{
		return m_firstMember;
	}

private:
	Rva000F4250TeamPrototype *m_proto;       // +0x04
	UnsignedInt m_id;                        // +0x08
	Rva000F4250MemberCall *m_firstMember;    // +0x0c
	Team *m_previous;                        // +0x10
	Team *m_next;                             // +0x14
	BFMERetailAsciiString m_state;           // +0x18
	Rva000F4250Hash m_hash;                  // +0x1c
	unsigned char m_unmodelled[ 0xec - 0x30 ];
	Rva000F4250RelationMap *m_teamRelations; // +0xec
	Rva000F4250RelationMap *m_playerRelations; // +0xf0
	unsigned char m_gap[ 0x100 - 0xf4 ];
	Rva000F4250TransferList m_xferMemberIDList; // +0x100
	Rva000F4250GateSet m_gateSet;            // +0x104
};

#pragma comment(linker, "/alternatename:?notify@Rva000F4250ScriptCall@@QAEXPAVTeam@@@Z=?j_00042910@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@Rva000F4250GateCall@@QAEXII@Z=?j_0000e6b5@@YAXXZ")
#pragma comment(linker, "/alternatename:?getNthPlayer@Rva000F4250PlayerListCall@@QAEPAVPlayer@@H@Z=?j_00044f30@@YAXXZ")
#pragma comment(linker, "/alternatename:?preTeamDestroy@Rva000F4250PlayerCall@@QAEXPBVTeam@@@Z=?j_00014dcb@@YAXXZ")
#pragma comment(linker, "/alternatename:?remove@Rva000F4250PrototypeCall@@QAEXPAVTeam@@@Z=?j_0001e416@@YAXXZ")
#pragma comment(linker, "/alternatename:?clear@Rva000F4250Hash@@QAEXXZ=?j_0001f1bd@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroy@Rva000F4250GateSet@@QAEXXZ=?j_0001fe2e@@YAXXZ")
#pragma comment(linker, "/alternatename:?destroy@Rva000F4250Hash@@QAEXXZ=?j_00049eb8@@YAXXZ")

// ??1Team@@MAE@XZ
Team::~Team()
{
	if ( TheScriptEngine )
		((Rva000F4250ScriptCall *)TheScriptEngine)->notify( this );

	while ( m_gateSet.m_count != 0 )
	{
		Rva000F4250GateSetNode *root =
			(Rva000F4250GateSetNode *)m_gateSet.m_tree->m_root;
		((Rva000F4250GateCall *)this)->set( root->m_gateID, 0 );
	}

	if ( ThePlayerList )
	{
		for ( int i = 0; i < ThePlayerList->m_playerCount; ++i )
		{
			Player *player =
				((Rva000F4250PlayerListCall *)ThePlayerList)->getNthPlayer( i );
			if ( player )
				((Rva000F4250PlayerCall *)player)->preTeamDestroy( this );
		}
	}

	Rva000F4250MemberCall *member;
	while ( ( member = getFirstItemInTeamMemberList() ) != 0 )
	{
		member->setTeam( 0 );
	}

	if ( m_proto )
	{
		if ( ((Rva000F4250TeamPrototype *)m_proto)->m_teamInstanceList == this ||
			m_previous != 0 || m_next != 0 )
			((Rva000F4250PrototypeCall *)m_proto)->remove( this );
	}

	if ( m_teamRelations )
		m_teamRelations->destroy( 1 );
	m_teamRelations = 0;

	if ( m_playerRelations )
		m_playerRelations->destroy( 1 );
	m_playerRelations = 0;

	m_hash.clear();
	m_xferMemberIDList.clear();
}
