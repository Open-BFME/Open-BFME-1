// cl: -GX-
// stlport
//
// Two 35-byte __thiscall lookups that hand back a pointer to the VALUE half of
// a std::map entry, or null when the key is absent.  Retail:
//
//     mov eax,[esp+4] / push esi / lea esi,[ecx+<OFF>] / push eax
//     mov ecx,esi / call 0x00142FD0
//     cmp eax,[esi] / pop esi / je NOTFOUND
//     add eax,0x14 / ret 4
//     NOTFOUND: xor eax,eax / ret 4
//
// WHAT THE BYTES SHOW.  `lea esi,[ecx+OFF]` then `mov ecx,esi` makes the callee
// a __thiscall on a SUBOBJECT at a fixed offset of the receiver, so the
// receiver owns a member there and the call is that member's own function.  The
// callee's result is compared against the FIRST DWORD of that member; that is
// STLport's `_Rb_tree::end()`, which is `_M_header._M_data` and sits at offset
// zero of the tree -- so the member is an STLport red-black tree, the callee is
// its `find`, and the comparison is `it == end()`.
//
// 0x14 FIXES THE KEY'S WIDTH.  The success path returns the node pointer plus
// 0x14.  An `_Rb_tree_node` is a 16-byte `_Rb_tree_node_base` (colour, parent,
// left, right) followed by the value, so 0x14 is four bytes into
// `pair<const Key, Value>` -- `&it->second` with a FOUR-BYTE key.  Nothing else
// in these bodies constrains the key or the value, so both are spelled as
// anonymous payloads of the right width.
//
// THE KEY ARRIVES BY REFERENCE, NOT BY VALUE.  The incoming dword is pushed
// straight through to `find`, and STLport's `find` takes `const key_type&`; a
// by-value key of any type would have had its ADDRESS taken (`lea eax,[esp+4]`)
// before the push.  So this function's own parameter is already a reference.
//
// BRANCH POLARITY IS SOURCE ORDER.  Retail falls through to `add eax,0x14` and
// jumps to the null return, so the source tests `it != end()` and returns the
// value pointer first; writing it as `if (it == end()) return 0;` inverts both
// the jump and the block order and is six bytes different.
//
// TWO ROWS, ONE MAP TYPE.  Both call the SAME address, so the key type, the
// comparator and the node width are the same in both; only the offset of the
// map within its owner differs (0x1BC and 0x1FC), which makes them two owners
// rather than two maps.  0x00142FD0 is pinned in targets/game/reverse/symbols.csv.
//
// IDENTITY IS NOT RECOVERED.  Owner, key and value names all come from
// addresses; `char m_pad[]` carries an offset and `int a[]` a width.

#include <map>

struct U4MapKey
{
	int a[1];
	U4MapKey();
	U4MapKey( const U4MapKey & );
	~U4MapKey();
	U4MapKey &operator=( const U4MapKey & );
	int compare( const U4MapKey & ) const;
	bool operator<( const U4MapKey &o ) const { return compare( o ) < 0; }
};

struct U4MapVal
{
	int a[4];
	U4MapVal();
	U4MapVal( const U4MapVal & );
	~U4MapVal();
	U4MapVal &operator=( const U4MapVal & );
};

typedef _STL::map<U4MapKey, U4MapVal > U4MapType;

#define U4_MAP_SECOND_LOOKUP( ROW, OFFSET )                                   \
	struct U4Host##ROW                                                        \
	{                                                                         \
		char m_pad[ OFFSET ];                                                 \
		U4MapType m_map;                                                      \
		const U4MapVal *lookup( const U4MapKey &key ) const;                  \
	};                                                                        \
	const U4MapVal *U4Host##ROW::lookup( const U4MapKey &key ) const           \
	{                                                                         \
		U4MapType::const_iterator it = m_map.find( key );                     \
		if ( it != m_map.end() )                                              \
			return &it->second;                                               \
		return 0;                                                             \
	}

U4_MAP_SECOND_LOOKUP( 00607D40, 0x1BC )
U4_MAP_SECOND_LOOKUP( 00608370, 0x1FC )
