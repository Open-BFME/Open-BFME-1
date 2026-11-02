// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport list<T *>::_M_insert_dispatch over a const-iterator
// range, 8 bodies of 66 bytes.  Every one carried only a machine byte-dump
// row; the same shape is already converted at 0x001C53B0 and 0x00483620.
//
// One node per source element, each taken from the 0x0C-byte node allocator and
// linked in front of the position.  Twelve bytes of node is two link pointers
// and four of value, and the value is a plain store rather than a call, so the
// element is a four-byte trivially-copied type -- a pointer, which is also what
// makes the dispatch pick the iterator overload rather than the fill one.
//
// What it points AT the body never says, so each element is a pointer to a
// class named for the address of the body.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

class TeamPrototype;

// retail 0x000CF880: list<TeamPrototype *>, Player's m_playerTeamPrototypes
// (ILT 0x000129E0; tools/ilt_oracle.py confirms the name at the thunk, and
// the list copy constructor 0x000D3230 that Player::update calls reaches it).
void BfmeListInsertRangeAnchor000CF880( _STL::list<TeamPrototype *> &dst,
	_STL::list<TeamPrototype *>::iterator where,
	const _STL::list<TeamPrototype *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva001E4ED0Target;

// retail 0x001E4ED0
void BfmeListInsertRangeAnchor001E4ED0( _STL::list<Rva001E4ED0Target *> &dst,
	_STL::list<Rva001E4ED0Target *>::iterator where,
	const _STL::list<Rva001E4ED0Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva002E06C0Target;

// retail 0x002E06C0
void BfmeListInsertRangeAnchor002E06C0( _STL::list<Rva002E06C0Target *> &dst,
	_STL::list<Rva002E06C0Target *>::iterator where,
	const _STL::list<Rva002E06C0Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva004284D0Target;

// retail 0x004284D0
void BfmeListInsertRangeAnchor004284D0( _STL::list<Rva004284D0Target *> &dst,
	_STL::list<Rva004284D0Target *>::iterator where,
	const _STL::list<Rva004284D0Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva00428530Target;

// retail 0x00428530
void BfmeListInsertRangeAnchor00428530( _STL::list<Rva00428530Target *> &dst,
	_STL::list<Rva00428530Target *>::iterator where,
	const _STL::list<Rva00428530Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva00440980Target;

// retail 0x00440980
void BfmeListInsertRangeAnchor00440980( _STL::list<Rva00440980Target *> &dst,
	_STL::list<Rva00440980Target *>::iterator where,
	const _STL::list<Rva00440980Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva005A8470Target;

// retail 0x005A8470
void BfmeListInsertRangeAnchor005A8470( _STL::list<Rva005A8470Target *> &dst,
	_STL::list<Rva005A8470Target *>::iterator where,
	const _STL::list<Rva005A8470Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

class Rva00681150Target;

// retail 0x00681150
void BfmeListInsertRangeAnchor00681150( _STL::list<Rva00681150Target *> &dst,
	_STL::list<Rva00681150Target *>::iterator where,
	const _STL::list<Rva00681150Target *> &src )
{
	dst.insert( where, src.begin(), src.end() );
}

struct Rva00381D80Element
{
	char m_body[ 216 ];
};

extern void j_0002806a();

namespace _STL
{
// The node value is copied through ILT 0x0002806A -> 0x00381C30,
// whose body invokes the proven ExperienceLevel copy constructor. Keep
// this opaque list's native link sequence while using that existing route.
template <>
inline list<Rva00381D80Element>::iterator
list<Rva00381D80Element>::insert(iterator position, const Rva00381D80Element &value)
{
    _Node *node = this->_M_node.allocate(1);
    union {
        void (*raw)();
        void (__cdecl *construct)(Rva00381D80Element *, const Rva00381D80Element &);
    } target;
    target.raw = j_0002806a;
    target.construct(&node->_M_data, value);
    _List_node_base *at = position._M_node;
    _List_node_base *before = at->_M_prev;
    node->_M_next = at;
    node->_M_prev = before;
    before->_M_next = node;
    at->_M_prev = node;
    return node;
}
}

// retail 0x00381D10, an 88-byte helper for the 224-byte list node
void BfmeListInsertRangeAnchor00381D10(
	_STL::list<Rva00381D80Element> &dst,
	_STL::list<Rva00381D80Element>::iterator where,
	const _STL::list<Rva00381D80Element> &src )
{
	dst.insert( where, src.begin(), src.end() );
}
