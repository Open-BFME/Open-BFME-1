// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool isPlayerActive() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

// Retail calls ILT 0x0002F3E7 -> 0x003405C0, the row defined in
// RvaTreeFindAsciiString.cpp as STLport's private _Rb_tree::_M_find over the
// AsciiString-keyed Rva003405C0Value tree, so the count map is declared under
// those template names (the caller is granted the private access).
struct Rva003405C0Value
{
	AsciiString m_key;
	int m_value;
};
struct Rva003405C0KeyOfValue { };

class ScriptEngine;

namespace _STL
{
template <class T> struct less { };
template <class T> class allocator { };

template <class Value>
struct _Rb_tree_node
{
	void *m_links[4];
	Value _M_value_field;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
	friend class ::ScriptEngine;

private:
	template <class KT> _Rb_tree_node<Value> *_M_find(const KT &key) const;

public:
	_Rb_tree_node<Value> *m_header;
	int m_count;
	void *m_compare;
};
}

typedef _STL::_Rb_tree_node<Rva003405C0Value> ObjectTypeCountNode;
typedef _STL::_Rb_tree<AsciiString, Rva003405C0Value, Rva003405C0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003405C0Value> > ObjectTypeCount;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	int getObjectCount(int playerIndex, const AsciiString &objectTypeName) const;

private:
	char m_unknown[0x170E0];
	ObjectTypeCount m_objectCounts[32];
};

int ScriptEngine::getObjectCount(int playerIndex,
	const AsciiString &objectTypeName) const
{
	if (!ThePlayerList->getNthPlayer(playerIndex)->isPlayerActive())
		return 0;

	const ObjectTypeCount &counts = m_objectCounts[playerIndex];
	ObjectTypeCountNode *found = counts._M_find(objectTypeName);
	if (found == counts.m_header)
		return 0;
	return found->_M_value_field.m_value;
}
