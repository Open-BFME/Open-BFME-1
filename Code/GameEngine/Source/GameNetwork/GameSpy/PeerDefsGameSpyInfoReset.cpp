// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?reset@GameSpyInfo@@UAEXXZ: Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp

// FILE: PeerDefsGameSpyInfoReset.cpp ////////////////////////////////////////
//
// GameSpyInfo::reset, retail 0x00635BA0.
//
// PeerDefs.cpp compiles this body from the same statements and lands 380 of
// the 389 bytes.  The disagreements are all BFME drift in types the vendored
// headers own, not in this function:
//
//   clearStagingRoomList()      vtable 0x94  (vendored header: 0x78)
//   m_localStagingRoom.reset()  vtable 0x08  (vendored header: 0x00)
//   m_localName = ""            StringBase<char>::set("", 0); the vendored
//                               AsciiString folds the empty assignment into
//                               an inline emptiness test plus releaseBuffer
//   two extra dwords zeroed beside m_currentGroupRoomID at +0x60 and +0x64,
//   and one extra byte zeroed at +0x6fc
//
// Landing it in PeerDefs.cpp is what was blocked: that TU also owns
// addGroupRoom, whose three unwind funclets (uw_00c40e10, uw_00c40e18,
// uw_00c40e8a) stop being emitted in the shape the ledger claims once this
// body joins them.  reset itself raises nothing -- it has no EH frame at all
// -- so moving it into its own TU with a local ABI slice leaves PeerDefs.cpp
// and its funclet rows untouched.
//
// The three red-black trees are the same STLport _Rb_tree spelled out far
// enough to inline clear() that PeerThreadClearPlayerStats.cpp uses.  Their
// _M_erase helpers resolve by mangled name:
//
//   m_buddyMap / m_buddyRequestMap  map<Int,BuddyInfo>   0x004EB5C0 (new pin;
//       the call site encodes the incremental-link thunk 0x000114AA)
//   m_savedIgnoreMap                map<Int,AsciiString> 0x0004887E (pinned)
//   m_preorderPlayers               set<Int>             0x00234730, a second
//       image copy of the instantiation already pinned at 0x0006EC60 --
//       identical instruction for instruction, differing only in its own two
//       inner REL32s
//
/////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;

class AsciiString;
class BuddyInfo;
class BuddyMessage;

namespace _STL
{

template <class Type> class allocator {};
template <class First, class Second> struct pair {};
template <class Pair> struct _Select1st {};
template <class Type> struct _Identity {};
template <class Type> struct less {};

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value _M_value_field;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:

	void clear()
	{
		if (_M_node_count != 0)
		{
			_M_erase((_Node *)(void *)_M_root());
			_M_leftmost() = _M_header;
			_M_root() = 0;
			_M_rightmost() = _M_header;
			_M_node_count = 0;
		}
	}

private:

	typedef _Rb_tree_node<Value> _Node;

	_Rb_tree_node_base *&_M_root() const { return _M_header->_M_parent; }
	_Rb_tree_node_base *&_M_leftmost() const { return _M_header->_M_left; }
	_Rb_tree_node_base *&_M_rightmost() const { return _M_header->_M_right; }

	// Declared, never defined: only the .obj is produced.
	void _M_erase(_Node *x);

	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;

};

// One node pointer: m_currentGroupRoomID sits at +0x5c, four bytes past the
// list at +0x58.
template <class Value, class Alloc>
class _List_base
{
public:
	void clear();
private:
	void *_M_node;
};

}

typedef _STL::pair<const Int, BuddyInfo> BfmeBuddyPair;
typedef _STL::_Rb_tree<Int, BfmeBuddyPair, _STL::_Select1st<BfmeBuddyPair>,
											 _STL::less<Int>, _STL::allocator<BfmeBuddyPair> > BuddyInfoMap;

typedef _STL::pair<const Int, AsciiString> BfmeIgnorePair;
typedef _STL::_Rb_tree<Int, BfmeIgnorePair, _STL::_Select1st<BfmeIgnorePair>,
											 _STL::less<Int>, _STL::allocator<BfmeIgnorePair> > SavedIgnoreMap;

// The set<Int> erase helper this call site encodes lives at 0x00234730, a
// second image copy of the instantiation pinned at 0x0006EC60 (identical but
// for its own two inner REL32s, which is why the two cannot share one pinned
// name).  The address already carries a machine-owned family-emit pin under
// a synthetic 4-byte POD element type, so the tree is spelled with that type
// rather than a new pin.
struct Gen_t_00234730_m4pod { Int m_pod; };
typedef _STL::_Rb_tree<Gen_t_00234730_m4pod, Gen_t_00234730_m4pod,
											 _STL::_Identity<Gen_t_00234730_m4pod>,
											 _STL::less<Gen_t_00234730_m4pod>,
											 _STL::allocator<Gen_t_00234730_m4pod> > PreorderSet;

typedef _STL::_List_base<BuddyMessage, _STL::allocator<BuddyMessage> > BuddyMessageList;

// StringBase<char> is what the calls name: set at 0x00887D20, and clear()
// expands to the private releaseBuffer at 0x00887940.
template <class Char>
class StringBase
{
public:

	void set( const Char *s, int len );
	void clear() { releaseBuffer(); }

private:

	void releaseBuffer();

	Char *m_data;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	void reset( void );
private:
	char m_bfmeBody[0x1c4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void reset( void );					// slot 0x08
private:
	char m_bfmeBody[0x468 - 4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefsImplementation.h
class GameSpyInfo
{
public:

	virtual void slot_000();
	virtual void slot_004();
	virtual void clearGroupRoomList();					// slot 0x08
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void clearStagingRoomList();				// slot 0x94
	// reset's own slot is not proven -- nothing in .rdata names either the
	// body or its ILT thunk -- so it is declared last and only 0x08 and 0x94
	// carry claims.
	virtual void reset( void );

private:

	Bool m_sawFullGameList;						// @0x04
	Bool m_isDisconAfterGameStart;				// @0x05
	char m_bfmePad06[2];
	Int m_disconReason;							// @0x08
	StringBase<char> m_rawMotd;					// @0x0c
	StringBase<char> m_rawConfig;				// @0x10
	StringBase<char> m_pingString;				// @0x14
	char m_bfmePad18[0x34 - 0x18];
	BuddyInfoMap m_buddyMap;					// @0x34
	BuddyInfoMap m_buddyRequestMap;				// @0x40
	char m_bfmePad4c[0x58 - 0x4c];
	BuddyMessageList m_buddyMessages;			// @0x58
	Int m_currentGroupRoomID;					// @0x5c
	Int m_bfme60;								// @0x60
	Int m_bfme64;								// @0x64
	Bool m_gotGroupRoomList;					// @0x68
	char m_bfmePad69[3];
	StringBase<char> m_localName;				// @0x6c
	Int m_localProfileID;						// @0x70
	StringBase<char> m_localPasswd;				// @0x74
	StringBase<char> m_localEmail;				// @0x78
	StringBase<char> m_localBaseName;			// @0x7c
	PSPlayerStats m_cachedLocalPlayerStats;		// @0x80
	Bool m_disallowAsainText;					// @0x244
	Bool m_disallowNonAsianText;				// @0x245
	char m_bfmePad246[2];
	Int m_internalIP;							// @0x248
	Int m_externalIP;							// @0x24c
	Int m_maxMessagesPerUpdate;					// @0x250
	Int m_joinedStagingRoom;					// @0x254
	Bool m_isHosting;							// @0x258
	char m_bfmePad259[3];
	GameSpyStagingRoom m_localStagingRoom;		// @0x25c
	Int m_localStagingRoomID;					// @0x6c4
	char m_bfmePad6c8[0x6d4 - 0x6c8];
	SavedIgnoreMap m_savedIgnoreMap;			// @0x6d4
	char m_bfmePad6e0[0x6ec - 0x6e0];
	PreorderSet m_preorderPlayers;				// @0x6ec
	Int m_additionalDisconnects;				// @0x6f8
	Bool m_bfme6fc;								// @0x6fc

};

// ?reset@GameSpyInfo@@UAEXXZ
void GameSpyInfo::reset( void )
{
	m_sawFullGameList = false;
	m_isDisconAfterGameStart = false;
	m_currentGroupRoomID = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	clearGroupRoomList();
	clearStagingRoomList();
	m_localStagingRoomID = 0;
	m_buddyRequestMap.clear();
	m_buddyMap.clear();
	m_buddyMessages.clear();
	m_joinedStagingRoom = 0;
	m_isHosting = false;
	m_localStagingRoomID = 0;
	m_localStagingRoom.reset();
	m_gotGroupRoomList = false;
	m_localName.set("", 0);
	m_localProfileID = 0;
	m_maxMessagesPerUpdate = 100;

	m_disallowAsainText = false;
	m_disallowNonAsianText = false;
	m_disconReason = 0;
	m_localBaseName.clear();
	m_localEmail.clear();
	m_localPasswd.clear();
	m_pingString.clear();
	m_rawConfig.clear();
	m_rawMotd.clear();

	m_internalIP = m_externalIP = 0;

	m_savedIgnoreMap.clear();
	m_preorderPlayers.clear();

	m_cachedLocalPlayerStats.reset();

	m_bfme6fc = false;
	m_additionalDisconnects = -1;
}
