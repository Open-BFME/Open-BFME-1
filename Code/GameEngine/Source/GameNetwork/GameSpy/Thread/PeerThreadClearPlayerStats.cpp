// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?clearPlayerStats@PeerThreadClass@@: Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp

// FILE: PeerThreadClearPlayerStats.cpp ///////////////////////////////////////
//
// PeerThreadClass::clearPlayerStats, retail 0x0064C640.
//
// PeerThread.cpp compiles it at 73 of 75 bytes; the two disagreements are the
// stats maps' offsets, +0x94 and +0xa0 against that file's +0x98 and +0xa4.
// It declares PeerThreadClass inside the .cpp, so the fix would ordinarily go
// there -- but the drift is not one uniform shift.  addServerToMap at
// 0x00647950 wants m_nextStagingServer and m_stagingServers at +0x208 and
// +0x20c where the same file puts them at +0x1f8 and +0x1fc: four bytes out at
// the front of the class and sixteen the other way by the tail.  Two
// independent disagreements across a class 44 matched rows already satisfy, so
// this body moved out with only the offsets it proves and the rest as opaque
// filler.
//
// The two tail members are declared below even though nothing here uses them.
// They are what addServerToMap measured, and they are the reason this file
// exists rather than a four-byte edit in PeerThread.cpp.
//
// The stats map is STLport's _Rb_tree spelled out far enough to inline clear():
// a header node pointer, a node count and an empty comparator, twelve bytes,
// which is exactly the stride between the two members.  The template arguments
// are carried in full because _M_erase is resolved by mangled name against
// reverse/symbols.csv, where it already sits at 0x0003120F.
//
///////////////////////////////////////////////////////////////////////////////

namespace _STL
{

template <class Type> class allocator {};
// A class and not a struct: the pinned _M_erase spells it V?$char_traits@D@,
// and U would be a different symbol.
template <class Type> class char_traits {};
template <class Char, class Traits, class Alloc> class basic_string {};
template <class First, class Second> struct pair {};
template <class Pair> struct _Select1st {};
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

	// STLport's clear().  The guard is on the count, and the three header links
	// are re-read through _M_header each time because _M_erase may have moved
	// nothing the compiler can prove.
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

}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BfmeStdString;
typedef _STL::pair<const BfmeStdString, int> BfmeStatPair;

typedef _STL::_Rb_tree<BfmeStdString,
											 BfmeStatPair,
											 _STL::_Select1st<BfmeStatPair>,
											 _STL::less<BfmeStdString>,
											 _STL::allocator<BfmeStatPair> > PlayerStatMap;

namespace _STL
{

// Only operator[] is needed, and retail calls it rather than inlining it, so
// the body never has to exist here.  Twelve bytes, the same _Rb_tree.
template <class Key, class Type, class Compare, class Alloc>
class map
{
public:
	Type &operator[](const Key &key);
private:
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;
};

}

struct _SBServer;
typedef _STL::pair<const int, _SBServer *> BfmeServerPair;

typedef _STL::map<int,
									_SBServer *,
									_STL::less<int>,
									_STL::allocator<BfmeServerPair> > StagingServerMap;

// GroupRoom is 1 and StagingRoom is 2: retail decrements the argument once for
// the first arm and once more for the second.
enum RoomType { UnknownRoom, GroupRoom, StagingRoom };

class PeerThreadClass
{
public:

	void clearPlayerStats( RoomType roomType );

private:

	char m_bfmeHead[0x94];
	PlayerStatMap m_groupRoomStats;					// @0x94
	PlayerStatMap m_stagingRoomStats;				// @0xa0
	char m_bfmeMiddle[0x208 - 0xac];
	int m_nextStagingServer;								// @0x208
	StagingServerMap m_stagingServers;			// @0x20c

};

void PeerThreadClass::clearPlayerStats( RoomType roomType )
{
	switch (roomType)
	{
		case GroupRoom:
			m_groupRoomStats.clear();
			break;
		case StagingRoom:
			m_stagingRoomStats.clear();
			break;
	}
}
