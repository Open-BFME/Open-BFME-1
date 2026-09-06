// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// partial score=0.97 date=2026-09-06
// stlport
//
// Open-BFME7: STLport _Rb_tree<AsciiString, pair<const AsciiString, bool>,
// _Select1st, AsciiComparator>::insert_unique (hinted, retail 0x00634650,
// 1122 bytes) with its plain insert_unique and _M_insert -- a GameSpy-side
// map<AsciiString, bool, AsciiComparator>.  Found as a reloc-masked byte twin
// of LanguageFilter's UnicodeString LangMap insert once _M_create_node is
// inlined (_STLP_NO_EXCEPTIONS): the only differences are the string copy
// constructor and the comparator the body calls.  The StringInline shape gives
// the by-value AsciiString temporaries the retail EH saved-esp order.

#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "StringInline.h"

struct AsciiComparator
{
	bool operator()( AsciiString a, AsciiString b ) const;
};

typedef _STL::pair<const AsciiString, bool> Rva00634650Pair;

typedef _STL::_Rb_tree<AsciiString,
	Rva00634650Pair,
	_STL::_Select1st<Rva00634650Pair>,
	AsciiComparator,
	_STL::allocator<Rva00634650Pair> > Rva00634650Tree;

template Rva00634650Tree::iterator
Rva00634650Tree::insert_unique( Rva00634650Tree::iterator, const Rva00634650Pair & );

template _STL::pair<Rva00634650Tree::iterator, bool>
Rva00634650Tree::insert_unique( const Rva00634650Pair & );

template Rva00634650Tree::iterator
Rva00634650Tree::_M_insert( _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
	const Rva00634650Pair &, _STL::_Rb_tree_node_base * );
