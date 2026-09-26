// One __thiscall member built out of nothing but early exits, ending in a
// duplicated one-byte constant rather than a computed condition.
//
//   0x003BED00  reads a global, tests a dword member of it, and then runs four
//               more tests -- a niladic call on that same global, a byte member
//               of THIS object, and two calls that differ only in the constant
//               they are given (4 and 8).  Any of the four succeeding lands on
//               `xor al,al`; the dword member being zero, or the last call
//               failing, lands on `mov al,1`.  Both constants are materialised
//               separately with their own epilogue, so the answers are literals
//               in the source, not a `setcc` of the last test.
//
// WHAT THE BYTES SHOW ABOUT THE RECEIVERS.  The global's address is loaded once
// and the call is made with it still in ecx, so the predicate is a member of the
// global's class; the two constant-taking calls set ecx from `this`, so those are
// members of this class.
//
// THE BLOCK ORDER IS THE HARD PART.  `xor al,al` sits BEFORE `mov al,1`, and the
// first test jumps past both blocks' worth of distance to reach the `1`.  Every
// structured spelling puts the `1` first; the source needs the two exits written
// as labels in retail's order for the displacement to come out.
//
// A SIBLING at 0x003BD9C0 -- a two-arm dispatcher reaching one callee twice, once
// with three zeroes and once with the real arguments, guarded by a SIXTEEN-BIT
// `cmp word ptr [eax+4],0` -- reproduces to the byte in size and content but
// with the two arms laid out the other way round, in all four spellings tried
// (both `&&`/`||` polarities and both goto directions produced identical code).
// It is NOT claimed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

class Glo012F7048Type
{
public:
	bool test();
	char m_pad00[ 0x4 ];
	int  m_at04;
};

extern Glo012F7048Type * Glo012F7048;

class Gen003BDF20Element;

// ONE class, and the ledger proves it: the two constant-taking calls in
// 0x003BED00 land on 0x003BDEC0, which is this class's own index walk over the
// pointer array at +0x50/+0x54 in V4VectorElementLoops.cpp.  Both files spell
// the class the same way so the call resolves through the ledger row rather than
// through a pin.
class Rva003BDEC0
{
public:
	bool anyMatching( int mask );
	bool allowed();
	char                  m_pad00[ 0x50 ];
	Gen003BDF20Element ** m_at50;
	Gen003BDF20Element ** m_at54;
	char                  m_pad58[ 0x20 ];
	bool                  m_at78;
};
bool Rva003BDEC0::allowed()
{
	if( Glo012F7048->m_at04 == 0 )
		goto yes;
	if( Glo012F7048->test() )
		goto no;
	if( m_at78 )
		goto no;
	if( anyMatching( 4 ) )
		goto no;
	if( anyMatching( 8 ) )
		goto no;
	goto yes;
no:
	return false;
yes:
	return true;
}
