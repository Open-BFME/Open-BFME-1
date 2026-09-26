// cl: -GX-
// stlport
//
// The two linear scans over the 0x1F0-wide element array this slice is built
// around.  Retail, 0x00606DC0 (77 bytes) and 0x00607000 (79 bytes):
//
//     mov esi,[ecx+8] / mov edi,[ecx+0xC] / cmp esi,edi / je EMPTY
//   LOOP:
//     push esi / mov ecx,<FILTER> / call 0x00606BF0 / test al,al / je NEXT
//     ... per-row body ...
//   NEXT:
//     add esi,0x1F0 / cmp esi,edi / jne LOOP
//   EMPTY: <failure value> / ret 8
//
// WHAT THE BYTES SHOW.  Two dwords are read off the receiver at +8 and +0xC and
// walked from the first to the second in steps of 0x1F0: STLport's
// `_Vector_base` `_M_start` / `_M_finish` over a 0x1F0-wide element, with a
// vector member at offset 8 of the receiver.  BOTH ARE READ EXACTLY ONCE,
// before the loop, even though the call inside the loop could alias them, so
// the source hoisted `begin()` and `end()` into locals rather than re-asking
// the container each turn.
//
// The call at the head of every iteration is __thiscall on the SECOND argument
// with the element pointer as its only parameter, and its result is tested as a
// byte: a predicate object handed the element.  It is the same address in both
// rows, so both take the same kind of filter.
//
// THE ELEMENT LAYOUT COMES OUT OF THE TWO BODIES TOGETHER.  0x00606DC0 tests a
// BYTE at +0x1EC and, when it passes, stores the DWORD at +0x1E8 through its
// first argument; 0x00607000 forms `element + 0x1DC`, calls the same
// `_Rb_tree::_M_find` that game/GameEngine/Source/Common/U4MapSecondLookups.cpp
// pins, compares the result against the first dword of that subobject (STLport
// `end()`) and returns it plus 0x14 -- `&it->second` over a four-byte key.  An
// STLport `_Rb_tree` is twelve bytes, so the map occupies 0x1DC..0x1E8, the
// dword sits at 0x1E8 and the flag byte at 0x1EC, and the whole runs to 0x1ED
// -- which pads to exactly the 0x1F0 stride the loops step by.  Neither body
// alone fixes that; the two together do, and the stride confirms it.
//
// BRANCH POLARITY IS SOURCE ORDER in both.  The predicate's failure jumps
// FORWARD to the loop increment and the success falls through, so the test is
// written positively and its body is nested inside; in 0x00607000 the map hit
// jumps forward out of the loop, so the source returns from inside the `if`
// rather than breaking to a shared exit.
//
// IDENTITY IS NOT RECOVERED.  Receiver, element, filter, key and value are all
// named after addresses; `char m_pad[]` carries an offset, `int a[]` a width,
// and the two dwords at +0 and +4 of the receiver are spelled `int` only
// because the vector has to start at 8.
#include <map>
#include <vector>

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

struct U4Elem
{
	char m_pad[ 0x1DC ];
	U4MapType m_map;
	int m_value;
	unsigned char m_flag;
};

class U4Filter
{
public:
	bool accepts( const U4Elem *e ) const;
};

struct U4Scan
{
	int m_f00;
	int m_f04;
	_STL::vector<U4Elem > m_elems;

	bool firstFlagged( int *out, const U4Filter *filter ) const;
	const U4MapVal *firstMapped( const U4MapKey &key, const U4Filter *filter ) const;
};

bool U4Scan::firstFlagged( int *out, const U4Filter *filter ) const
{
	const U4Elem *p = m_elems.begin();
	const U4Elem *e = m_elems.end();
	for ( ; p != e; ++p )
	{
		if ( filter->accepts( p ) && p->m_flag )
		{
			*out = p->m_value;
			return true;
		}
	}
	return false;
}

const U4MapVal *U4Scan::firstMapped( const U4MapKey &key, const U4Filter *filter ) const
{
	const U4Elem *p = m_elems.begin();
	const U4Elem *e = m_elems.end();
	for ( ; p != e; ++p )
	{
		if ( filter->accepts( p ) )
		{
			U4MapType::const_iterator it = p->m_map.find( key );
			if ( it != p->m_map.end() )
				return &it->second;
		}
	}
	return 0;
}
