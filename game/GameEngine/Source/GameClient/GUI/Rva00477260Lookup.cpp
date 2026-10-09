// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// Retail 0x00477260 takes a this pointer whose tree begins at +0x1C.
// The FontSubstitution parser at 0x004779C0 and the matched map/tree
// callees establish the key, node, and mapped vector layout. No independent
// caller establishes the owner class, so it remains address-derived.
//
// Retail initializes a private 4-byte stack slot to zero before the first
// tree lookup, then never reads the slot or passes its address. A volatile
// local preserves that observed write. Its original source-level purpose is
// unknown; it has no effect on the lookup or returned vector.

#include "ascii_string.h"

enum Rva00475300Mapped { Rva00475300MappedZero = 0 };
struct Rva00475680Value;
struct Rva00475680KeyOfValue;
class Rva00477260Lookup;
namespace _STL
{
template <class First, class Second> struct pair;
template <class Value> struct less;
template <class Value> class allocator;
template <class Value> struct _Rb_tree_node;
template <class Key, class Value, class Extract, class Compare, class Alloc>
class _Rb_tree
{
    friend class ::Rva00477260Lookup;
    template <class Lookup>
    _Rb_tree_node<Value> *_M_find(const Lookup &) const;
};
template <class Key, class Mapped, class Compare, class Alloc> class map
{
public:
    Mapped &operator[](const Key &);
};
}

class Rva004779C0Vector
{
public:
	Rva004779C0Vector() : m_first(0), m_last(0), m_end(0) {}
	void *m_first;
	void *m_last;
	void *m_end;
};

struct Rva00475680Node
{
	char m_beforeValue[0x14];
	Rva004779C0Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *m_header;
};

class Rva00477260Lookup
{
public:
	Rva004779C0Vector *getOrCreate(const AsciiString &key);

private:
	char m_beforeTree[0x1c];
	Rva00475680Tree m_tree;
};

Rva004779C0Vector *Rva00477260Lookup::getOrCreate(const AsciiString &key)
{
	Rva00475680Tree *tree = &m_tree;
	Rva00475680Node *volatile emptyIterator = 0;
	Rva00475680Node *node = reinterpret_cast<Rva00475680Node *>(reinterpret_cast<const _STL::_Rb_tree<AsciiString, Rva00475680Value, Rva00475680KeyOfValue, _STL::less<AsciiString>, _STL::allocator<Rva00475680Value> > *>(tree)->_M_find<AsciiString>(key));
	if (node == tree->m_header)
	{
		Rva004779C0Vector *created = new Rva004779C0Vector;
		reinterpret_cast<Rva004779C0Vector *&>(
            (*reinterpret_cast<_STL::map<AsciiString, Rva00475300Mapped,
                _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString,
                Rva00475300Mapped> > > *>(tree))[key]) = created;
		node = reinterpret_cast<Rva00475680Node *>(reinterpret_cast<const _STL::_Rb_tree<AsciiString, Rva00475680Value, Rva00475680KeyOfValue, _STL::less<AsciiString>, _STL::allocator<Rva00475680Value> > *>(tree)->_M_find<AsciiString>(key));
	}
	return node->m_value;
}
