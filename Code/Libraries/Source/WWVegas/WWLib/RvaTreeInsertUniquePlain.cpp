// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<AsciiString, V>::insert_unique(const value_type
// &) -- the plain insert -- 19 bodies of 310 bytes.  Every one carried only a
// machine byte-dump row.
//
// It walks from the root keeping the last node it turned left at, then steps
// back one and compares once more to decide whether the key is already there.
// The comparison inlines at both sites, which is most of the 310 bytes: two
// lengths as halfwords at +4, a null pointer standing in for the empty string
// at 0x0107388B, `repe cmpsb` over the shorter side, the length difference as
// the tiebreak -- AsciiString's compare.
//
// The retail STLport differs from the vendored one in this function and only in
// this function.  On the branch where the walk stopped at begin(), retail hands
// _M_insert the SAME node twice -- `push ebx; push ebx` -- where the stock
// source passes __x and __y separately.  vendor/stlport/stl/_tree.c already
// carries that variant behind _BFME_RETAIL_TREE_INSERT_LAYOUT; without the
// define the body is eight bytes shorter and spills the key length that retail
// keeps in a register.  This is the first file to need it for insert_unique
// rather than for _M_insert.
//
// The tree spellings are not guesses.  Each body calls a _M_insert converted in
// RvaTreeMInsertStringKey.cpp, which states the key by the compare it calls and
// the mapped width by the node it allocates; both are carried over, which is
// why the mapped types are named for the _M_insert's address.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
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

struct Rva0007D900Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0007D900Value> Rva0007D900Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0007D900Pair, _STL::_Select1st<Rva0007D900Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0007D900Pair> > Rva0007D900Tree;

// retail 0x0007D9F0, inserting through the _M_insert at 0x0007D900
template _STL::pair<Rva0007D900Tree::iterator, bool>
Rva0007D900Tree::insert_unique( const Rva0007D900Pair & );

struct Rva000BFA40Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const AsciiString, Rva000BFA40Value> Rva000BFA40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000BFA40Pair, _STL::_Select1st<Rva000BFA40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000BFA40Pair> > Rva000BFA40Tree;

// retail 0x000BFB30, inserting through the _M_insert at 0x000BFA40
template _STL::pair<Rva000BFA40Tree::iterator, bool>
Rva000BFA40Tree::insert_unique( const Rva000BFA40Pair & );

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva000BFCC0Tree;

// retail 0x000C0430, inserting through the _M_insert at 0x000BFCC0 -- a set of the key
template _STL::pair<Rva000BFCC0Tree::iterator, bool>
Rva000BFCC0Tree::insert_unique( const AsciiString & );

struct Rva000C1740Value
{
	char m_body[ 252 ];
};

typedef _STL::pair<const AsciiString, Rva000C1740Value> Rva000C1740Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000C1740Pair, _STL::_Select1st<Rva000C1740Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000C1740Pair> > Rva000C1740Tree;

// retail 0x000C1830, inserting through the _M_insert at 0x000C1740
template _STL::pair<Rva000C1740Tree::iterator, bool>
Rva000C1740Tree::insert_unique( const Rva000C1740Pair & );

struct Rva00142DF0Value
{
	char m_body[ 112 ];
};

typedef _STL::pair<const AsciiString, Rva00142DF0Value> Rva00142DF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00142DF0Pair, _STL::_Select1st<Rva00142DF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00142DF0Pair> > Rva00142DF0Tree;

// retail 0x00144560, inserting through the _M_insert at 0x00142DF0
template _STL::pair<Rva00142DF0Tree::iterator, bool>
Rva00142DF0Tree::insert_unique( const Rva00142DF0Pair & );

struct Rva00142EE0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00142EE0Value> Rva00142EE0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00142EE0Pair, _STL::_Select1st<Rva00142EE0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00142EE0Pair> > Rva00142EE0Tree;

// retail 0x001446F0, inserting through the _M_insert at 0x00142EE0
template _STL::pair<Rva00142EE0Tree::iterator, bool>
Rva00142EE0Tree::insert_unique( const Rva00142EE0Pair & );

struct Rva0033F960Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F960Value> Rva0033F960Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F960Pair, _STL::_Select1st<Rva0033F960Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F960Pair> > Rva0033F960Tree;

// retail 0x0033FA50, inserting through the _M_insert at 0x0033F960
template _STL::pair<Rva0033F960Tree::iterator, bool>
Rva0033F960Tree::insert_unique( const Rva0033F960Pair & );

struct Rva0033F870Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F870Value> Rva0033F870Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F870Pair, _STL::_Select1st<Rva0033F870Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F870Pair> > Rva0033F870Tree;

// retail 0x003423F0, inserting through the _M_insert at 0x0033F870
template _STL::pair<Rva0033F870Tree::iterator, bool>
Rva0033F870Tree::insert_unique( const Rva0033F870Pair & );

struct Rva003B9B40Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva003B9B40Value> Rva003B9B40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva003B9B40Pair, _STL::_Select1st<Rva003B9B40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva003B9B40Pair> > Rva003B9B40Tree;

// retail 0x003B9C30, inserting through the _M_insert at 0x003B9B40
template _STL::pair<Rva003B9B40Tree::iterator, bool>
Rva003B9B40Tree::insert_unique( const Rva003B9B40Pair & );

struct Rva00424520Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00424520Value> Rva00424520Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00424520Pair, _STL::_Select1st<Rva00424520Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00424520Pair> > Rva00424520Tree;

// retail 0x00424BA0, inserting through the _M_insert at 0x00424520
template _STL::pair<Rva00424520Tree::iterator, bool>
Rva00424520Tree::insert_unique( const Rva00424520Pair & );

struct Rva00448C60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00448C60Value> Rva00448C60Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00448C60Pair, _STL::_Select1st<Rva00448C60Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00448C60Pair> > Rva00448C60Tree;

// retail 0x00448D50, inserting through the _M_insert at 0x00448C60
template _STL::pair<Rva00448C60Tree::iterator, bool>
Rva00448C60Tree::insert_unique( const Rva00448C60Pair & );

struct Rva00449BF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00449BF0Value> Rva00449BF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00449BF0Pair, _STL::_Select1st<Rva00449BF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00449BF0Pair> > Rva00449BF0Tree;

// retail 0x00449CE0, inserting through the _M_insert at 0x00449BF0
template _STL::pair<Rva00449BF0Tree::iterator, bool>
Rva00449BF0Tree::insert_unique( const Rva00449BF0Pair & );

struct Rva00461630Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00461630Value> Rva00461630Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00461630Pair, _STL::_Select1st<Rva00461630Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00461630Pair> > Rva00461630Tree;

// retail 0x00461720, inserting through the _M_insert at 0x00461630
template _STL::pair<Rva00461630Tree::iterator, bool>
Rva00461630Tree::insert_unique( const Rva00461630Pair & );

struct Rva00475080Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475080Value> Rva00475080Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475080Pair, _STL::_Select1st<Rva00475080Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475080Pair> > Rva00475080Tree;

// retail 0x00475170, inserting through the _M_insert at 0x00475080
template _STL::pair<Rva00475080Tree::iterator, bool>
Rva00475080Tree::insert_unique( const Rva00475080Pair & );

struct Rva00475300Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475300Value> Rva00475300Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475300Pair, _STL::_Select1st<Rva00475300Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475300Pair> > Rva00475300Tree;

// retail 0x004753F0, inserting through the _M_insert at 0x00475300
template _STL::pair<Rva00475300Tree::iterator, bool>
Rva00475300Tree::insert_unique( const Rva00475300Pair & );

struct Rva005C7490Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva005C7490Value> Rva005C7490Pair;

typedef _STL::_Rb_tree<AsciiString, Rva005C7490Pair, _STL::_Select1st<Rva005C7490Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva005C7490Pair> > Rva005C7490Tree;

// retail 0x005C8B10, inserting through the _M_insert at 0x005C7490
template _STL::pair<Rva005C7490Tree::iterator, bool>
Rva005C7490Tree::insert_unique( const Rva005C7490Pair & );

struct Rva009C98A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009C98A0Value> Rva009C98A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009C98A0Pair, _STL::_Select1st<Rva009C98A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009C98A0Pair> > Rva009C98A0Tree;

// retail 0x009C9960, inserting through the _M_insert at 0x009C98A0
template _STL::pair<Rva009C98A0Tree::iterator, bool>
Rva009C98A0Tree::insert_unique( const Rva009C98A0Pair & );

struct Rva009CF5A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009CF5A0Value> Rva009CF5A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF5A0Pair, _STL::_Select1st<Rva009CF5A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF5A0Pair> > Rva009CF5A0Tree;

// retail 0x009CF660, inserting through the _M_insert at 0x009CF5A0
template _STL::pair<Rva009CF5A0Tree::iterator, bool>
Rva009CF5A0Tree::insert_unique( const Rva009CF5A0Pair & );

struct Rva009CF7A0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const AsciiString, Rva009CF7A0Value> Rva009CF7A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF7A0Pair, _STL::_Select1st<Rva009CF7A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF7A0Pair> > Rva009CF7A0Tree;

// retail 0x009CF860, inserting through the _M_insert at 0x009CF7A0
template _STL::pair<Rva009CF7A0Tree::iterator, bool>
Rva009CF7A0Tree::insert_unique( const Rva009CF7A0Pair & );

// The mapped type here is a plain bool, so no stand-in struct is needed.
typedef _STL::pair<const AsciiString, bool> Rva00063140Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00063140Pair, _STL::_Select1st<Rva00063140Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00063140Pair> > Rva00063140Tree;

// retail 0x00063230, inserting through the _M_insert at 0x00063140
template _STL::pair<Rva00063140Tree::iterator, bool>
Rva00063140Tree::insert_unique( const Rva00063140Pair & );

typedef _STL::pair<const AsciiString, _STL::list<AsciiString, _STL::allocator<AsciiString> > > Rva000817C0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000817C0Pair, _STL::_Select1st<Rva000817C0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000817C0Pair> > Rva000817C0Tree;

// retail 0x000818B0, inserting through the _M_insert at 0x000817C0
template _STL::pair<Rva000817C0Tree::iterator, bool>
Rva000817C0Tree::insert_unique( const Rva000817C0Pair & );

// Eight bytes, the width the _M_insert at 0x005B2EF0 allocates for it.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/HotKey.h
class HotKey
{
	char m_body[ 8 ];
};

typedef _STL::pair<const AsciiString, HotKey> Rva005B2EF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva005B2EF0Pair, _STL::_Select1st<Rva005B2EF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva005B2EF0Pair> > Rva005B2EF0Tree;

// retail 0x005B2FE0, inserting through the _M_insert at 0x005B2EF0
template _STL::pair<Rva005B2EF0Tree::iterator, bool>
Rva005B2EF0Tree::insert_unique( const Rva005B2EF0Pair & );
