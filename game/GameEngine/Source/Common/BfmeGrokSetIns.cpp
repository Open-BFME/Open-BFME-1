// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include "ascii_string.h"

struct Rva0013FA60Target;

typedef Rva0013FA60Target *Rva00751A70Key;
typedef _STL::set<Rva00751A70Key, _STL::less<Rva00751A70Key>,
	_STL::allocator<Rva00751A70Key> > Rva00751A70Set;

// The four-argument node insertion is provided by the verified retail body
// at 0x0013F760 in RvaTreeMInsertIdentity.cpp.
template <>
_STL::_Rb_tree<Rva00751A70Key, Rva00751A70Key,
    _STL::_Identity<Rva00751A70Key>, _STL::less<Rva00751A70Key>,
    _STL::allocator<Rva00751A70Key> >::iterator
_STL::_Rb_tree<Rva00751A70Key, Rva00751A70Key,
    _STL::_Identity<Rva00751A70Key>, _STL::less<Rva00751A70Key>,
    _STL::allocator<Rva00751A70Key> >::_M_insert(
    _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
    const Rva00751A70Key &, _STL::_Rb_tree_node_base *);

void *bfmeGoEMEb(void *);
typedef Rva00751A70Key (__cdecl *FindPrototypeFn)(const char *name);

struct Rva00751A70Holder
{
	char m_pad[8];
	AsciiString m_name;
};

class Rva00751A70Owner
{
public:
	Rva00751A70Set m_values;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

void __cdecl rva00751A70Insert(Rva00751A70Holder *holder, Rva00751A70Owner *owner)
{
	if (owner->m_values.insert(
		((FindPrototypeFn)bfmeGoEMEb)(holder->m_name.str())).second)
	{
		owner->m_changed = true;
	}
}
