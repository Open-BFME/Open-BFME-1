// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<AsciiString, V>::insert_unique(iterator, const
// value_type &) -- the hinted insert -- 16 bodies of 629 bytes.  Every one
// carried only a machine byte-dump row.
//
// The hint form checks the neighbours the caller pointed at before it walks:
// if the hinted position's predecessor orders below the new key and the
// position itself above it, the tree is handed that gap directly and no
// descent happens at all.  Only on a miss does it fall through to the ordinary
// root-down walk.  Six hundred bytes of that is the comparison, which inlines
// at every one of those sites: the two lengths read as halfwords at +4, a null
// pointer standing in for the empty string at 0x0107388B, `repe cmpsb` over
// the shorter side and the length difference as the tiebreak -- AsciiString's
// compare, spelled out four times over.
//
// These are not guesses about the tree.  Each of these bodies calls a
// four-argument _M_insert converted in RvaTreeMInsertStringKey.cpp, and that
// callee states the key by the address of the compare it calls and the mapped
// type's width by the node it allocates.  Both are carried over here unchanged,
// which is why the mapped types are named for the _M_insert's address rather
// than this body's.

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

// retail 0x0007DBC0, hinting into the _M_insert at 0x0007D900
template Rva0007D900Tree::iterator
Rva0007D900Tree::insert_unique( Rva0007D900Tree::iterator, const Rva0007D900Pair & );

struct Rva000BFA40Value
{
	char m_body[ 12 ];
};

typedef _STL::pair<const AsciiString, Rva000BFA40Value> Rva000BFA40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000BFA40Pair, _STL::_Select1st<Rva000BFA40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000BFA40Pair> > Rva000BFA40Tree;

// retail 0x000C0110, hinting into the _M_insert at 0x000BFA40
template Rva000BFA40Tree::iterator
Rva000BFA40Tree::insert_unique( Rva000BFA40Tree::iterator, const Rva000BFA40Pair & );

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva000BFCC0Tree;

// retail 0x000C05C0, hinting into the _M_insert at 0x000BFCC0 -- a set of the key
template Rva000BFCC0Tree::iterator
Rva000BFCC0Tree::insert_unique( Rva000BFCC0Tree::iterator, const AsciiString & );

struct Rva000C1740Value
{
	char m_body[ 252 ];
};

typedef _STL::pair<const AsciiString, Rva000C1740Value> Rva000C1740Pair;

typedef _STL::_Rb_tree<AsciiString, Rva000C1740Pair, _STL::_Select1st<Rva000C1740Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva000C1740Pair> > Rva000C1740Tree;

// retail 0x000C19C0, hinting into the _M_insert at 0x000C1740
template Rva000C1740Tree::iterator
Rva000C1740Tree::insert_unique( Rva000C1740Tree::iterator, const Rva000C1740Pair & );

struct Rva0033F960Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F960Value> Rva0033F960Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F960Pair, _STL::_Select1st<Rva0033F960Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F960Pair> > Rva0033F960Tree;

// retail 0x00342580, hinting into the _M_insert at 0x0033F960
template Rva0033F960Tree::iterator
Rva0033F960Tree::insert_unique( Rva0033F960Tree::iterator, const Rva0033F960Pair & );

struct Rva003B9B40Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva003B9B40Value> Rva003B9B40Pair;

typedef _STL::_Rb_tree<AsciiString, Rva003B9B40Pair, _STL::_Select1st<Rva003B9B40Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva003B9B40Pair> > Rva003B9B40Tree;

// retail 0x003BA060, hinting into the _M_insert at 0x003B9B40
template Rva003B9B40Tree::iterator
Rva003B9B40Tree::insert_unique( Rva003B9B40Tree::iterator, const Rva003B9B40Pair & );

struct Rva00448C60Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00448C60Value> Rva00448C60Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00448C60Pair, _STL::_Select1st<Rva00448C60Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00448C60Pair> > Rva00448C60Tree;

// retail 0x004493B0, hinting into the _M_insert at 0x00448C60
template Rva00448C60Tree::iterator
Rva00448C60Tree::insert_unique( Rva00448C60Tree::iterator, const Rva00448C60Pair & );

struct Rva00449BF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00449BF0Value> Rva00449BF0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00449BF0Pair, _STL::_Select1st<Rva00449BF0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00449BF0Pair> > Rva00449BF0Tree;

// retail 0x0044AA20, hinting into the _M_insert at 0x00449BF0
template Rva00449BF0Tree::iterator
Rva00449BF0Tree::insert_unique( Rva00449BF0Tree::iterator, const Rva00449BF0Pair & );

struct Rva0033F870Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva0033F870Value> Rva0033F870Pair;

typedef _STL::_Rb_tree<AsciiString, Rva0033F870Pair, _STL::_Select1st<Rva0033F870Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F870Pair> > Rva0033F870Tree;

// retail 0x00453690, hinting into the _M_insert at 0x0033F870
template Rva0033F870Tree::iterator
Rva0033F870Tree::insert_unique( Rva0033F870Tree::iterator, const Rva0033F870Pair & );

struct Rva00461630Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00461630Value> Rva00461630Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00461630Pair, _STL::_Select1st<Rva00461630Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00461630Pair> > Rva00461630Tree;

// retail 0x00462100, hinting into the _M_insert at 0x00461630
template Rva00461630Tree::iterator
Rva00461630Tree::insert_unique( Rva00461630Tree::iterator, const Rva00461630Pair & );

struct Rva00475080Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475080Value> Rva00475080Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475080Pair, _STL::_Select1st<Rva00475080Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475080Pair> > Rva00475080Tree;

// retail 0x00475B00, hinting into the _M_insert at 0x00475080
template Rva00475080Tree::iterator
Rva00475080Tree::insert_unique( Rva00475080Tree::iterator, const Rva00475080Pair & );

struct Rva00475300Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00475300Value> Rva00475300Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00475300Pair, _STL::_Select1st<Rva00475300Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00475300Pair> > Rva00475300Tree;

// retail 0x00475E20, hinting into the _M_insert at 0x00475300
template Rva00475300Tree::iterator
Rva00475300Tree::insert_unique( Rva00475300Tree::iterator, const Rva00475300Pair & );

struct Rva005C7490Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva005C7490Value> Rva005C7490Pair;

typedef _STL::_Rb_tree<AsciiString, Rva005C7490Pair, _STL::_Select1st<Rva005C7490Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva005C7490Pair> > Rva005C7490Tree;

// retail 0x006AB6D0, hinting into the _M_insert at 0x005C7490
template Rva005C7490Tree::iterator
Rva005C7490Tree::insert_unique( Rva005C7490Tree::iterator, const Rva005C7490Pair & );

struct Rva009C98A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009C98A0Value> Rva009C98A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009C98A0Pair, _STL::_Select1st<Rva009C98A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009C98A0Pair> > Rva009C98A0Tree;

// retail 0x009C9D80, hinting into the _M_insert at 0x009C98A0
template Rva009C98A0Tree::iterator
Rva009C98A0Tree::insert_unique( Rva009C98A0Tree::iterator, const Rva009C98A0Pair & );

struct Rva009CF5A0Value
{
	char m_body[ 28 ];
};

typedef _STL::pair<const AsciiString, Rva009CF5A0Value> Rva009CF5A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF5A0Pair, _STL::_Select1st<Rva009CF5A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF5A0Pair> > Rva009CF5A0Tree;

// retail 0x009CFD20, hinting into the _M_insert at 0x009CF5A0
template Rva009CF5A0Tree::iterator
Rva009CF5A0Tree::insert_unique( Rva009CF5A0Tree::iterator, const Rva009CF5A0Pair & );

struct Rva009CF7A0Value
{
	char m_body[ 16 ];
};

typedef _STL::pair<const AsciiString, Rva009CF7A0Value> Rva009CF7A0Pair;

typedef _STL::_Rb_tree<AsciiString, Rva009CF7A0Pair, _STL::_Select1st<Rva009CF7A0Pair>,
	_STL::less<AsciiString>, _STL::allocator<Rva009CF7A0Pair> > Rva009CF7A0Tree;

// retail 0x009CFFE0, hinting into the _M_insert at 0x009CF7A0
template Rva009CF7A0Tree::iterator
Rva009CF7A0Tree::insert_unique( Rva009CF7A0Tree::iterator, const Rva009CF7A0Pair & );

