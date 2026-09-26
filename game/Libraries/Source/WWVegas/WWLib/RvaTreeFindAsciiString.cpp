// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<AsciiString, V>::_M_find<AsciiString>, 19 bodies
// of 194 bytes.  Every one carried only a machine byte-dump row.
//
// _M_find is the lookup half of the tree: it walks from the root keeping the
// last node it did not pass on the left, then checks that candidate against the
// key once more and returns it or the header.  It allocates nothing and stores
// nothing.
//
// The key is AsciiString and the bytes say so twice over.  The descent compares
// inline -- the two lengths read as halfwords at +4, a null pointer standing in
// for the empty string at 0x0107388B, `repe cmpsb` over the shorter side and
// the length difference as the tiebreak, which is StringBase<char>::compare
// spelled out.  The final check against the candidate is the same comparison
// left as a call.  Both come from the one `less<AsciiString>` below; the
// compiler simply inlined one site and not the other.
//
// What these 194 bytes never touch is the mapped type: there is no allocation
// here, so not even its width is knowable.  Rather than assert a pair whose
// second half nothing reads, each tree is spelled with its own key-of-value
// functor over a value that begins with the AsciiString -- which is exactly
// what the walk proves -- and both are named for the address of the body.

#include "PreRTS.h"
#include "Common/AsciiString.h"

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

struct Rva000773E0Value
{
	AsciiString m_key;
};

struct Rva000773E0KeyOfValue
{
	const AsciiString &operator()( const Rva000773E0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva000773E0Value, Rva000773E0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva000773E0Value> > Rva000773E0Tree;

// retail 0x000773E0
template _STL::_Rb_tree_node<Rva000773E0Value> *
Rva000773E0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00080600Value
{
	AsciiString m_key;
};

struct Rva00080600KeyOfValue
{
	const AsciiString &operator()( const Rva00080600Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00080600Value, Rva00080600KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00080600Value> > Rva00080600Tree;

// retail 0x00080600
template _STL::_Rb_tree_node<Rva00080600Value> *
Rva00080600Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00080700Value
{
	AsciiString m_key;
};

struct Rva00080700KeyOfValue
{
	const AsciiString &operator()( const Rva00080700Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00080700Value, Rva00080700KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00080700Value> > Rva00080700Tree;

// retail 0x00080700
template _STL::_Rb_tree_node<Rva00080700Value> *
Rva00080700Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00142FD0Value
{
	AsciiString m_key;
};

struct Rva00142FD0KeyOfValue
{
	const AsciiString &operator()( const Rva00142FD0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00142FD0Value, Rva00142FD0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00142FD0Value> > Rva00142FD0Tree;

// retail 0x00142FD0
template _STL::_Rb_tree_node<Rva00142FD0Value> *
Rva00142FD0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva001430D0Value
{
	AsciiString m_key;
};

struct Rva001430D0KeyOfValue
{
	const AsciiString &operator()( const Rva001430D0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva001430D0Value, Rva001430D0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva001430D0Value> > Rva001430D0Tree;

// retail 0x001430D0
template _STL::_Rb_tree_node<Rva001430D0Value> *
Rva001430D0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva003404C0Value
{
	AsciiString m_key;
};

struct Rva003404C0KeyOfValue
{
	const AsciiString &operator()( const Rva003404C0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva003404C0Value, Rva003404C0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003404C0Value> > Rva003404C0Tree;

// retail 0x003404C0
template _STL::_Rb_tree_node<Rva003404C0Value> *
Rva003404C0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva003405C0Value
{
	AsciiString m_key;
};

struct Rva003405C0KeyOfValue
{
	const AsciiString &operator()( const Rva003405C0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva003405C0Value, Rva003405C0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003405C0Value> > Rva003405C0Tree;

// retail 0x003405C0
template _STL::_Rb_tree_node<Rva003405C0Value> *
Rva003405C0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva0038BFE0Value
{
	AsciiString m_key;
};

struct Rva0038BFE0KeyOfValue
{
	const AsciiString &operator()( const Rva0038BFE0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva0038BFE0Value, Rva0038BFE0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva0038BFE0Value> > Rva0038BFE0Tree;

// retail 0x0038BFE0
template _STL::_Rb_tree_node<Rva0038BFE0Value> *
Rva0038BFE0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva0038C0E0Value
{
	AsciiString m_key;
};

struct Rva0038C0E0KeyOfValue
{
	const AsciiString &operator()( const Rva0038C0E0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva0038C0E0Value, Rva0038C0E0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva0038C0E0Value> > Rva0038C0E0Tree;

// retail 0x0038C0E0
template _STL::_Rb_tree_node<Rva0038C0E0Value> *
Rva0038C0E0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva003B9DC0Value
{
	AsciiString m_key;
};

struct Rva003B9DC0KeyOfValue
{
	const AsciiString &operator()( const Rva003B9DC0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva003B9DC0Value, Rva003B9DC0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003B9DC0Value> > Rva003B9DC0Tree;

// retail 0x003B9DC0
template _STL::_Rb_tree_node<Rva003B9DC0Value> *
Rva003B9DC0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00448EE0Value
{
	AsciiString m_key;
};

struct Rva00448EE0KeyOfValue
{
	const AsciiString &operator()( const Rva00448EE0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00448EE0Value, Rva00448EE0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00448EE0Value> > Rva00448EE0Tree;

// retail 0x00448EE0
template _STL::_Rb_tree_node<Rva00448EE0Value> *
Rva00448EE0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00448FE0Value
{
	AsciiString m_key;
};

struct Rva00448FE0KeyOfValue
{
	const AsciiString &operator()( const Rva00448FE0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00448FE0Value, Rva00448FE0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00448FE0Value> > Rva00448FE0Tree;

// retail 0x00448FE0
template _STL::_Rb_tree_node<Rva00448FE0Value> *
Rva00448FE0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva004618B0Value
{
	AsciiString m_key;
};

struct Rva004618B0KeyOfValue
{
	const AsciiString &operator()( const Rva004618B0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva004618B0Value, Rva004618B0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva004618B0Value> > Rva004618B0Tree;

// retail 0x004618B0
template _STL::_Rb_tree_node<Rva004618B0Value> *
Rva004618B0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00475580Value
{
	AsciiString m_key;
};

struct Rva00475580KeyOfValue
{
	const AsciiString &operator()( const Rva00475580Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00475580Value, Rva00475580KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00475580Value> > Rva00475580Tree;

// retail 0x00475580
template _STL::_Rb_tree_node<Rva00475580Value> *
Rva00475580Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva00475680Value
{
	AsciiString m_key;
};

struct Rva00475680KeyOfValue
{
	const AsciiString &operator()( const Rva00475680Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00475680Value, Rva00475680KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00475680Value> > Rva00475680Tree;

// retail 0x00475680
template _STL::_Rb_tree_node<Rva00475680Value> *
Rva00475680Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva005B3170Value
{
	AsciiString m_key;
};

struct Rva005B3170KeyOfValue
{
	const AsciiString &operator()( const Rva005B3170Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva005B3170Value, Rva005B3170KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva005B3170Value> > Rva005B3170Tree;

// retail 0x005B3170
template _STL::_Rb_tree_node<Rva005B3170Value> *
Rva005B3170Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva005C7770Value
{
	AsciiString m_key;
};

struct Rva005C7770KeyOfValue
{
	const AsciiString &operator()( const Rva005C7770Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva005C7770Value, Rva005C7770KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva005C7770Value> > Rva005C7770Tree;

// retail 0x005C7770
template _STL::_Rb_tree_node<Rva005C7770Value> *
Rva005C7770Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva009CF9A0Value
{
	AsciiString m_key;
};

struct Rva009CF9A0KeyOfValue
{
	const AsciiString &operator()( const Rva009CF9A0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva009CF9A0Value, Rva009CF9A0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF9A0Value> > Rva009CF9A0Tree;

// retail 0x009CF9A0
template _STL::_Rb_tree_node<Rva009CF9A0Value> *
Rva009CF9A0Tree::_M_find<AsciiString>( const AsciiString & ) const;

struct Rva009CFA70Value
{
	AsciiString m_key;
};

struct Rva009CFA70KeyOfValue
{
	const AsciiString &operator()( const Rva009CFA70Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva009CFA70Value, Rva009CFA70KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva009CFA70Value> > Rva009CFA70Tree;

// retail 0x009CFA70
template _STL::_Rb_tree_node<Rva009CFA70Value> *
Rva009CFA70Tree::_M_find<AsciiString>( const AsciiString & ) const;

