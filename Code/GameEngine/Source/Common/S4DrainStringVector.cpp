// cl: -GX-
// stlport
//
// Four 134-byte bodies that hand every string in a member vector to one global
// object and then empty the vector:
//
//     void C::drain( void )
//     {
//         if ( !g ) return;
//         for ( it = m_vec.begin(); it != m_vec.end(); ++it ) g->take( *it );
//         m_vec.clear();
//     }
//
// WHAT THE BYTES SHOW -- the element is AsciiString, and that is RECOVERED, not
// assumed.  The destroy loop calls 0x0005EE90, the matched row
// `??1AsciiString@@QAE@XZ`, and the copy loop calls 0x00887C90, which
// symbols.csv already pins for `??4AsciiString@@QAEAAV0@ABV0@@Z` (folded with
// `StringBase<char>::set`).  A four-byte element with an out-of-line copy
// assignment and an out-of-line destructor is AsciiString exactly, so the
// minimal declaration below carries the real name and the real single-pointer
// layout, and both callees resolve from the ledger rather than from new pins.
//
// WHAT THE BYTES SHOW -- WHICH vector, and why it is ONE class rather than four.
// Start and finish are read from [this+N] and [this+N+4] and the final store
// writes finish back.  Retail's four N are 4, 0x10, 0x1C and 0x28 -- spaced
// TWELVE apart, which is exactly the size of STLport's `_Vector_base`.  Four
// adjacent vectors of the same element type is a much better account of that
// spacing than four unrelated classes that happen to land on a 12-byte grid, so
// the four bodies are spelled as four methods of one owner.  Nothing reads
// [this+0] or any end-of-storage dword, so the leading four bytes are padding
// and end-of-storage is simply untouched.
//
// THE DEAD COPY LOOP IS STLport's `erase`, NOT A BUG IN THE SOURCE.  `mov
// eax,esi / sub eax,esi` computes ZERO and the loop that follows can never run.
// That is `clear()` expanding to `erase(begin(), end())`, whose body starts
// `pointer __i = copy(__last, _M_finish, __first)` -- with `__last` ALREADY
// `_M_finish`, the count is `_M_finish - _M_finish`.  The compiler emitted the
// loop anyway.  Reading those two instructions as source would have invented a
// self-subtraction nobody wrote; reading them as the erase idiom is what
// identifies the call as `clear()` rather than as a hand-written destroy loop.
//
// THE GLOBAL IS RE-READ INSIDE THE LOOP.  `mov ecx,[<addr>]` sits at the top of
// each iteration, not before it, so the source names the global in the loop body
// rather than copying it to a local first.  Its address is the SAME in all four
// bodies, as are the assignment and the destructor; only the method called on it
// differs.  Four methods on one object is why one holder class carries the whole
// axis.
//
// THE GUARD RETURNS EARLY.  The `je` at the top jumps past the clear as well as
// past the loop, so a null global leaves the vector untouched -- one `if` around
// both statements, not two.
//
// IDENTITY IS NOT RECOVERED for the four host classes or for the holder and its
// methods; those are named after the bodies that use them, and the methods are
// DECLARED, never defined, and pinned to the addresses their REL32s resolve to
// through the ILT thunks in the way.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=( const AsciiString &o );
	~AsciiString();

private:
	char *m_data;
};

struct S4Holder0046DBB0
{
	void take0046DBB0( const AsciiString &s );
	void take0046DD00( const AsciiString &s );
	void take0046DE10( const AsciiString &s );
	void take0046DEF0( const AsciiString &s );
};

extern S4Holder0046DBB0 *g_s4Holder;

struct S4Owner
{
	char m_head[ 4 ];
	_STL::vector< AsciiString > m_vec0;
	_STL::vector< AsciiString > m_vec1;
	_STL::vector< AsciiString > m_vec2;
	_STL::vector< AsciiString > m_vec3;
	void s4drain00464B60( void );
	void s4drain00464C10( void );
	void s4drain00464CC0( void );
	void s4drain00464D70( void );
};

#define S4_DRAIN( NAME, TAKE, VEC )                                            	void S4Owner::s4drain##NAME( void )                                        	{                                                                          		if ( !g_s4Holder )                                                     			return;                                                            		for ( _STL::vector< AsciiString >::iterator it = VEC.begin();          			it != VEC.end(); ++it )                                            			g_s4Holder->TAKE( *it );                                           		VEC.clear();                                                           	}

S4_DRAIN( 00464B60, take0046DBB0, m_vec0 )
S4_DRAIN( 00464C10, take0046DD00, m_vec1 )
S4_DRAIN( 00464CC0, take0046DE10, m_vec2 )
S4_DRAIN( 00464D70, take0046DEF0, m_vec3 )
