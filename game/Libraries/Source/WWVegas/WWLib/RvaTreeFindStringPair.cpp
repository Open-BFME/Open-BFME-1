// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<pair<AsciiString, AsciiString>, V>::_M_find --
// five bodies of 431 bytes that carried only a machine byte-dump row.
//
// The sibling file RvaTreeFindAsciiString.cpp converts the single-AsciiString
// version of this walk at 194 bytes.  These are the same walk over a key that
// is a PAIR of AsciiStrings, and the three comparison calls in the tail say so
// outright: pair's own operator< is
//
//     x.first < y.first || (!(y.first < x.first) && x.second < y.second)
//
// and retail's tail is exactly that -- compare on the first halves, compare on
// the first halves with the operands swapped, then compare on the second halves
// four bytes further into both operands.  The descent loop is the same
// comparison with all three sites inlined; the tail leaves all three as calls,
// which is the same one-site-inlined split the AsciiString file describes.
//
// What these bytes never touch is the mapped type: there is no allocation here,
// so not even its width is knowable.  As in the sibling file each tree is
// spelled with its own key-of-value functor over a value that begins with the
// key -- which is exactly what the walk proves -- and both are named for the
// address of the body.

#include "PreRTS.h"
#include "Common/AsciiString.h"

typedef _STL::pair<AsciiString, AsciiString> BfmeStringPairKey;

namespace _STL
{
template <> struct less<BfmeStringPairKey>
{
	bool operator()( const BfmeStringPairKey &left, const BfmeStringPairKey &right ) const
	{
		return left.first.compare( right.first ) < 0
			|| ( !( right.first.compare( left.first ) < 0 )
				&& left.second.compare( right.second ) < 0 );
	}
};
}

struct Rva00198280Value
{
	BfmeStringPairKey m_key;
};

struct Rva00198280KeyOfValue
{
	const BfmeStringPairKey &operator()( const Rva00198280Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<BfmeStringPairKey, Rva00198280Value, Rva00198280KeyOfValue,
	_STL::less<BfmeStringPairKey>, _STL::allocator<Rva00198280Value> > Rva00198280Tree;

// retail 0x00198280
template _STL::_Rb_tree_node<Rva00198280Value> *
Rva00198280Tree::_M_find<BfmeStringPairKey>( const BfmeStringPairKey & ) const;

struct Rva0033FC40Value
{
	BfmeStringPairKey m_key;
};

struct Rva0033FC40KeyOfValue
{
	const BfmeStringPairKey &operator()( const Rva0033FC40Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<BfmeStringPairKey, Rva0033FC40Value, Rva0033FC40KeyOfValue,
	_STL::less<BfmeStringPairKey>, _STL::allocator<Rva0033FC40Value> > Rva0033FC40Tree;

// retail 0x0033FC40
template _STL::_Rb_tree_node<Rva0033FC40Value> *
Rva0033FC40Tree::_M_find<BfmeStringPairKey>( const BfmeStringPairKey & ) const;

struct Rva0033FE60Value
{
	BfmeStringPairKey m_key;
};

struct Rva0033FE60KeyOfValue
{
	const BfmeStringPairKey &operator()( const Rva0033FE60Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<BfmeStringPairKey, Rva0033FE60Value, Rva0033FE60KeyOfValue,
	_STL::less<BfmeStringPairKey>, _STL::allocator<Rva0033FE60Value> > Rva0033FE60Tree;

// retail 0x0033FE60
template _STL::_Rb_tree_node<Rva0033FE60Value> *
Rva0033FE60Tree::_M_find<BfmeStringPairKey>( const BfmeStringPairKey & ) const;

struct Rva00340080Value
{
	BfmeStringPairKey m_key;
};

struct Rva00340080KeyOfValue
{
	const BfmeStringPairKey &operator()( const Rva00340080Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<BfmeStringPairKey, Rva00340080Value, Rva00340080KeyOfValue,
	_STL::less<BfmeStringPairKey>, _STL::allocator<Rva00340080Value> > Rva00340080Tree;

// retail 0x00340080
template _STL::_Rb_tree_node<Rva00340080Value> *
Rva00340080Tree::_M_find<BfmeStringPairKey>( const BfmeStringPairKey & ) const;

struct Rva003402A0Value
{
	BfmeStringPairKey m_key;
};

struct Rva003402A0KeyOfValue
{
	const BfmeStringPairKey &operator()( const Rva003402A0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<BfmeStringPairKey, Rva003402A0Value, Rva003402A0KeyOfValue,
	_STL::less<BfmeStringPairKey>, _STL::allocator<Rva003402A0Value> > Rva003402A0Tree;

// retail 0x003402A0
template _STL::_Rb_tree_node<Rva003402A0Value> *
Rva003402A0Tree::_M_find<BfmeStringPairKey>( const BfmeStringPairKey & ) const;
