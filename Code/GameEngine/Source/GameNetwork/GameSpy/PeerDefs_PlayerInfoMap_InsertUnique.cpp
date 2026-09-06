// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// Open-BFME7: STLport _Rb_tree<AsciiString, pair<const AsciiString, PlayerInfo>,
// _Select1st, AsciiComparator>::insert_unique -- PlayerInfoMap of PeerDefs.h --
// the hinted form at retail 0x00634650 (1122 bytes) and the plain form it
// inlines three times.  Byte twin of LanguageFilter's UnicodeString LangMap
// insert once _M_create_node is inlined (_STLP_NO_EXCEPTIONS); the StringInline
// shape gives the by-value AsciiString temporaries the retail EH saved-esp
// order, and MSVC stops inlining the AsciiString copy forwarder after the
// fourth expansion exactly where retail calls it out of line (the
// ??0AsciiString@@QAE@ABV0@@Z sites resolve to that ILT thunk, the inlined
// ones to the StringBase<char> copy).  The _M_insert this calls is landed
// from PeerDefs_PlayerInfoMap_M_insert.cpp; the PlayerInfo stand-in only has
// to be 52 bytes with an out-of-line copy.

#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "StringInline.h"

class PlayerInfo
{
public:
	PlayerInfo( const PlayerInfo &other );
private:
	char m_body[ 52 ];
};

struct AsciiComparator
{
	bool operator()( AsciiString a, AsciiString b ) const;
};

typedef _STL::pair<const AsciiString, PlayerInfo> BfmePlayerInfoPair;

typedef _STL::_Rb_tree<AsciiString,
	BfmePlayerInfoPair,
	_STL::_Select1st<BfmePlayerInfoPair>,
	AsciiComparator,
	_STL::allocator<BfmePlayerInfoPair> > BfmePlayerInfoTree;

template BfmePlayerInfoTree::iterator
BfmePlayerInfoTree::insert_unique( BfmePlayerInfoTree::iterator, const BfmePlayerInfoPair & );

template _STL::pair<BfmePlayerInfoTree::iterator, bool>
BfmePlayerInfoTree::insert_unique( const BfmePlayerInfoPair & );
