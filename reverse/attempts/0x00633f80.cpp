// ?playerLeftGroupRoom@GameSpyInfo@@UAEXVAsciiString@@@Z
// partial score=0.99 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: GameSpyInfo::playerLeftGroupRoom(AsciiString nick) at 0x00633F80
// (168 B): m_playerInfoMap.erase(nick) with the map at this+0x4c. STLport's
// erase_unique is inlined around an out-of-line find (iterator returned in
// eax): rebalance the node out, destroy the
// pair<const AsciiString, PlayerInfo> (PlayerInfo's out-of-line destructor,
// then the key's releaseBuffer), free the 0x48-byte node, drop the count.
// The by-value nick is released on the way out.
#include "../../../../../reference/shims/stringinline/StringInline.h"

class PlayerInfo
{
public:
	~PlayerInfo();
private:
	char m_body[0x34];
};

namespace _STL
{
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

template <bool dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_Rebalance_for_erase(_Rb_tree_node_base *z, _Rb_tree_node_base *&root,
		_Rb_tree_node_base *&leftmost, _Rb_tree_node_base *&rightmost);
};

template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};

template <class Value>
struct _Rb_tree_iterator
{
	_Rb_tree_node_base *_M_node;
};

template <class Key, class Value>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<Value> iterator;
	typedef _Rb_tree_node<Value> _Node;
	iterator find(const Key &key);
	__forceinline unsigned int erase_unique(const Key &key)
	{
		iterator it = find(key);
		if (it._M_node != _M_header)
		{
			erase(it);
			return 1;
		}
		return 0;
	}
	__forceinline void erase(iterator position)
	{
		_Node *y = (_Node *)_Rb_global<true>::_Rebalance_for_erase(position._M_node,
			_M_header->_M_parent, _M_header->_M_left, _M_header->_M_right);
		y->_M_value_field.~Value();
		if (y != 0)
			__node_alloc<true, 0>::_M_deallocate(y, sizeof(_Node));
		--_M_node_count;
	}
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
};
}

typedef _STL::pair<const AsciiString, PlayerInfo> PlayerInfoPair;
typedef _STL::_Rb_tree<AsciiString, PlayerInfoPair> PlayerInfoTree;

class GameSpyInfo
{
public:
	virtual void playerLeftGroupRoom(AsciiString nick);
private:
	char m_head[0x4c - 4];
	PlayerInfoTree m_playerInfoMap;
};

void GameSpyInfo::playerLeftGroupRoom(AsciiString nick)
{
	m_playerInfoMap.erase_unique(nick);
}
