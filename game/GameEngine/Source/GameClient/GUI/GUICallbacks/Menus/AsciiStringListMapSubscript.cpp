// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// std::map<AsciiString, std::list<AsciiString> >::operator[](const AsciiString &)
// at retail 0x00082050, 244 bytes.
//
// Identity: the ledger name is the canonical STLport instantiation
// _STL::map<AsciiString, _STL::list<AsciiString>, _STL::less<AsciiString>,
// _STL::allocator<pair<const AsciiString, list<AsciiString> > > >::operator[],
// the ILT thunk 0x0002D74A (symbols.csv, route=0x00082050) routes to it, and
// its seven call sites are all `m_emailNickMap[email]` subscripts in
// GameSpyLoginPreferences (addLogin x4, load, getNicksForEmail, bfmeSetRT).
// Those call sites prove the ABI too: ecx = the map member (this+0x20), one
// pushed argument (an AsciiString temp), the callee pops it (`ret 4`), and the
// result in eax is dereferenced as the mapped list.
//
// The body is STLport's _map.h operator[] verbatim: lower_bound, one out-of-line
// AsciiString::compare, then value_type(__k, default-constructed list) handed
// to _Rb_tree::insert_unique, then the temporary unwound (pair dtor, list
// clear, sentinel deallocate).
//
// _STLP_DEFAULT_CONSTRUCTOR_BUG stays undefined: the workaround would turn the
// mapped-type default construction into a by-value __default_constructed()
// call, while retail inlines it (12-byte __new_alloc::allocate, self-linked
// sentinel, stored straight into the temporary).

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG

#include <list>
#include <map>

#include "ascii_string.h"

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

typedef std::list<AsciiString> AsciiStringList;
typedef std::map<AsciiString, AsciiStringList> NickMap;

template AsciiStringList &NickMap::operator[](const AsciiString &key);
