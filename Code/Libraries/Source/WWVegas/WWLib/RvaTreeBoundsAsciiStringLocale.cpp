// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<...>::_M_lower_bound at 0x00631C70, an
// AsciiString-keyed tree whose comparator is a member functor (stored at
// this+8, reached with `lea ecx,[edi]`/`mov ecx,edi` from a cached this+8
// pointer) taking BOTH arguments BY VALUE:
//   push ecx (spill this); construct temp1 = AsciiString(key)   -- call 0x00887B60
//   construct temp2 = AsciiString(node->value at +0x10)          -- call 0x00887B60
//   ecx = functor-at-this+8; call thunk 0x0000B4B0 (target 0x00631350, still
//   a dump); test al,al
// The by-value ABI means the CALLEE destroys both temporaries -- 0x00631350's
// own body ends with two calls to releaseBuffer@BFMERetailAsciiString, which
// is why this caller has no destructor calls of its own despite the /EHsc
// unwind frame (needed only because the two copy constructors can throw).
// Plain pass-by-value C++ reproduces this without any manual ABI trick.
//
// 0x004F18C0 is the tree's find(), not a bare _M_lower_bound: the same
// descent, then STLport's stock _M_find() tail (vendor/stlport/stl/_tree.h) --
// compare candidate against the header (not found -> return header) and, if
// present, one more BfmeStringLocaleLess call with the operands swapped
// (key < candidate) to confirm equality before returning the candidate.
// That is exactly why it doubles the call-site count of 0x00631C70 (2x
// construct+compare instead of 1x) for 237B vs 144B.

#include "PreRTS.h"
#include "Common/AsciiString.h"

typedef bool Bool;

// The comparator has no name the bytes reach; it is spelled for the function
// it calls, exactly as RvaTreeInsertUniqueNoCase.cpp already does for the
// sibling insert bodies at this address range.
class BfmeStringLocaleLess
{
public:
	bool operator()( AsciiString left, AsciiString right ) const;	// ILT 0x0000B4B0 -> 0x00631350 (dump)
};

struct Rva00632450Value
{
	AsciiString m_key;
	int m_pad1;
	int m_pad2;
};

struct Rva00632450KeyOfValue
{
	const AsciiString &operator()( const Rva00632450Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00632450Value, Rva00632450KeyOfValue,
	BfmeStringLocaleLess, _STL::allocator<Rva00632450Value> > Rva00632450Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00632450( const Rva00632450Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

// ---- 0x004F18C0: find() -- lower_bound descent plus the equality tail. ----

struct Rva004F1FD0Value
{
	AsciiString m_key;
	int m_pad1;
	int m_pad2;
};

struct Rva004F1FD0KeyOfValue
{
	const AsciiString &operator()( const Rva004F1FD0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva004F1FD0Value, Rva004F1FD0KeyOfValue,
	BfmeStringLocaleLess, _STL::allocator<Rva004F1FD0Value> > Rva004F1FD0Tree;

// find() is public; the _M_find it calls is not, so reaching it through the
// public method is what emits it.
const Rva004F1FD0Value *BfmeTreeFindAnchor004F1FD0( const Rva004F1FD0Tree &tree, const AsciiString &key )
{
	Rva004F1FD0Tree::const_iterator it = tree.find( key );
	if ( it == tree.end() )
		return 0;
	return &( *it );
}
