// Ten 34-byte __thiscall members that ask one predicate about an index and
// then assign either that index or a lower one through a second member of the
// SAME object:
//
//   push esi / push <INDEX> / mov esi,ecx
//   call ?query@ ...          ; __thiscall, one stack argument, cleans its own
//   test al,al / mov ecx,esi
//   je other
//   push <INDEX> / call ?assign@ ... / pop esi / ret
//  other:
//   push <FALLBACK> / call ?assign@ ... / pop esi / ret
//
// WHAT THE BYTES SHOW.  `mov esi,ecx` then `mov ecx,esi` before both arms:
// the receiver of the predicate and the receiver of the assignment are the
// same object this function is a member of.  Neither call is followed by an
// esp adjustment, so both are __thiscall with the argument cleaned by the
// callee.  `test al,al` and nothing else makes the predicate's result a
// byte-wide truth value, not an int.  All ten rows call the SAME two bodies --
// 0x00416FC0 for the predicate, 0x00416FA0 for the assignment -- which is what
// makes them ten members of one class rather than ten unrelated look-alikes.
//
// The assignment call is written out TWICE, once per arm, rather than the
// index being selected first; writing it once as `assign( query(i) ? i : j )`
// compiles to 27 bytes with an sbb/and select and no branch at all, so that
// spelling is refuted by length alone.
//
// TWO AXES: the queried index (which the true arm passes on unchanged in all
// ten rows) and the fallback index the false arm passes instead.  The pairs
// are (3,0) (4,2) (9,7) (10,8) (34,33) (44,42) (45,43) (50,48) (51,49)
// (75,74) -- the fallback is one or two below the queried index every time,
// which is a fact about the data and not something this shape explains.
// 22 of the 34 bytes are concrete; the three displacements are resolved from
// pins.
//
// WHAT THE BYTES DO NOT DECIDE.  `test al,al` fits bool and char alike.  The
// indices are ints only because `6a xx` sign-extends a byte to a dword; an
// enum with int underlying type is identical.  Nothing here shows a single
// data member of the class, so it has none.  Whether the two callees are
// members of this class or of a base is not visible either.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Q2FlagOwner
{
public:
	bool query( int index );							///< body 0x00416FC0
	void assign( int index );						///< body 0x00416FA0

#define Q2_QUERIED_INDEX_ASSIGNMENT( NAME, INDEX, FALLBACK )              \
	void NAME();
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D10, 3, 0 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D40, 4, 2 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DB0, 9, 7 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DE0, 10, 8 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6F70, 34, 33 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7030, 44, 42 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7060, 45, 43 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A70D0, 50, 48 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7100, 51, 49 )
	Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A72A0, 75, 74 )
#undef Q2_QUERIED_INDEX_ASSIGNMENT
};

#define Q2_QUERIED_INDEX_ASSIGNMENT( NAME, INDEX, FALLBACK )              \
	void Q2FlagOwner::NAME()                                              \
	{                                                                     \
		if ( query( INDEX ) )                                             \
			assign( INDEX );                                              \
		else                                                              \
			assign( FALLBACK );                                           \
	}

Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D10, 3, 0 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6D40, 4, 2 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DB0, 9, 7 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6DE0, 10, 8 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A6F70, 34, 33 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7030, 44, 42 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7060, 45, 43 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A70D0, 50, 48 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A7100, 51, 49 )
Q2_QUERIED_INDEX_ASSIGNMENT( Rva005A72A0, 75, 74 )
