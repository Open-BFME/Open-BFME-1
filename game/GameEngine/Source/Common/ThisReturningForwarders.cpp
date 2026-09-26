// Fifty-one 12-byte forwarders: save `this`, make one direct no-argument call
// on it, return `this`.
//
//     push esi / mov esi,ecx / call <REL32> / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  ecx is read and never reloaded, and the plain `ret`
// pops nothing: __thiscall with no arguments.  The callee is entered with ecx
// still holding the same `this` and pops nothing of its own, so it too is a
// no-argument __thiscall member of the class or of a base of it.  eax is the
// incoming `this`.
//
// WHAT THE BYTES CANNOT SETTLE.  A constructor whose only work is one chained
// call and a member that ends `return this;` compile to these same twelve
// bytes -- both spellings were compiled and compare equal.  The member form is
// written below because it asserts less: it does not claim the callee is a
// constructor.
//
// THE ONLY AXIS IS THE REL32 TARGET.  Fifty-one members over thirty-one
// distinct callees.  Two runs of sixteen at 0x005E3FD0 and 0x005E5710 sit at a
// fixed sixteen-byte stride and call the SAME sixteen callees in the SAME
// order -- one header of non-inlinable forwarders emitted twice.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_THIS_FORWARD_CALLEE( ADDR )                                      \
	class Gen##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		void perform();                                                       \
	};

#define BFME_THIS_FORWARD( NAME, CALLEE )                                     \
	class NAME : public CALLEE                                                \
	{                                                                         \
	public:                                                                   \
		NAME *forward();                                                      \
	};                                                                        \
	NAME *NAME::forward()                                                     \
	{                                                                         \
		perform();                                                            \
		return this;                                                          \
	}


BFME_THIS_FORWARD_CALLEE( 002DF780 )
BFME_THIS_FORWARD_CALLEE( 00351260 )
BFME_THIS_FORWARD_CALLEE( 003A0410 )
BFME_THIS_FORWARD_CALLEE( 005DEEE0 )
BFME_THIS_FORWARD_CALLEE( 005DEF70 )
BFME_THIS_FORWARD_CALLEE( 005DF120 )
BFME_THIS_FORWARD_CALLEE( 005DF2D0 )
BFME_THIS_FORWARD_CALLEE( 005DF480 )
BFME_THIS_FORWARD_CALLEE( 005DF510 )
BFME_THIS_FORWARD_CALLEE( 005DFD50 )
BFME_THIS_FORWARD_CALLEE( 005DFFE0 )
BFME_THIS_FORWARD_CALLEE( 005E0270 )
BFME_THIS_FORWARD_CALLEE( 005E0500 )
BFME_THIS_FORWARD_CALLEE( 005E0790 )
BFME_THIS_FORWARD_CALLEE( 005E0820 )
BFME_THIS_FORWARD_CALLEE( 005E08B0 )
BFME_THIS_FORWARD_CALLEE( 005E0A70 )
BFME_THIS_FORWARD_CALLEE( 005E0B00 )
BFME_THIS_FORWARD_CALLEE( 005E0CB0 )
BFME_THIS_FORWARD_CALLEE( 005E0E60 )
BFME_THIS_FORWARD_CALLEE( 005E1010 )
BFME_THIS_FORWARD_CALLEE( 005E11C0 )
BFME_THIS_FORWARD_CALLEE( 005E1370 )
BFME_THIS_FORWARD_CALLEE( 005E14F0 )
BFME_THIS_FORWARD_CALLEE( 005E1690 )
BFME_THIS_FORWARD_CALLEE( 005E1830 )
BFME_THIS_FORWARD_CALLEE( 005E19B0 )
BFME_THIS_FORWARD_CALLEE( 005E1B50 )
BFME_THIS_FORWARD_CALLEE( 00761E10 )
BFME_THIS_FORWARD_CALLEE( 0088C550 )
BFME_THIS_FORWARD_CALLEE( 00903090 )

BFME_THIS_FORWARD( Rva0007BCD0Forwarder, Gen00903090 )
BFME_THIS_FORWARD( Rva002DB200Forwarder, Gen003A0410 )
BFME_THIS_FORWARD( Rva002E2A30Forwarder, Gen002DF780 )
BFME_THIS_FORWARD( Rva00339580Forwarder, Gen00351260 )
BFME_THIS_FORWARD( Rva0033B090Forwarder, Gen00351260 )
BFME_THIS_FORWARD( Rva005E3FD0Forwarder, Gen005DFD50 )
BFME_THIS_FORWARD( Rva005E3FE0Forwarder, Gen005DFFE0 )
BFME_THIS_FORWARD( Rva005E3FF0Forwarder, Gen005E0270 )
BFME_THIS_FORWARD( Rva005E4000Forwarder, Gen005E0500 )
BFME_THIS_FORWARD( Rva005E4010Forwarder, Gen005E0790 )
BFME_THIS_FORWARD( Rva005E4020Forwarder, Gen005E0820 )
BFME_THIS_FORWARD( Rva005E4030Forwarder, Gen005E08B0 )
BFME_THIS_FORWARD( Rva005E4040Forwarder, Gen005E0A70 )
BFME_THIS_FORWARD( Rva005E4050Forwarder, Gen005E0B00 )
BFME_THIS_FORWARD( Rva005E4060Forwarder, Gen005E0CB0 )
BFME_THIS_FORWARD( Rva005E4070Forwarder, Gen005E0E60 )
BFME_THIS_FORWARD( Rva005E4080Forwarder, Gen005E1010 )
BFME_THIS_FORWARD( Rva005E4090Forwarder, Gen005E11C0 )
BFME_THIS_FORWARD( Rva005E40A0Forwarder, Gen005E1370 )
BFME_THIS_FORWARD( Rva005E40B0Forwarder, Gen005E14F0 )
BFME_THIS_FORWARD( Rva005E40C0Forwarder, Gen005E1690 )
BFME_THIS_FORWARD( Rva005E40D0Forwarder, Gen005E1830 )
BFME_THIS_FORWARD( Rva005E40E0Forwarder, Gen005E19B0 )
BFME_THIS_FORWARD( Rva005E40F0Forwarder, Gen005E1B50 )
BFME_THIS_FORWARD( Rva005E5710Forwarder, Gen005DFD50 )
BFME_THIS_FORWARD( Rva005E5720Forwarder, Gen005DFFE0 )
BFME_THIS_FORWARD( Rva005E5730Forwarder, Gen005E0270 )
BFME_THIS_FORWARD( Rva005E5740Forwarder, Gen005E0500 )
BFME_THIS_FORWARD( Rva005E5750Forwarder, Gen005E0790 )
BFME_THIS_FORWARD( Rva005E5760Forwarder, Gen005E0820 )
BFME_THIS_FORWARD( Rva005E5770Forwarder, Gen005E08B0 )
BFME_THIS_FORWARD( Rva005E5780Forwarder, Gen005E0A70 )
BFME_THIS_FORWARD( Rva005E5790Forwarder, Gen005E0B00 )
BFME_THIS_FORWARD( Rva005E57A0Forwarder, Gen005E0CB0 )
BFME_THIS_FORWARD( Rva005E57B0Forwarder, Gen005E0E60 )
BFME_THIS_FORWARD( Rva005E57C0Forwarder, Gen005E1010 )
BFME_THIS_FORWARD( Rva005E57D0Forwarder, Gen005E11C0 )
BFME_THIS_FORWARD( Rva005E57E0Forwarder, Gen005E1370 )
BFME_THIS_FORWARD( Rva005E57F0Forwarder, Gen005E14F0 )
BFME_THIS_FORWARD( Rva005E5800Forwarder, Gen005E1690 )
BFME_THIS_FORWARD( Rva005E5810Forwarder, Gen005E1830 )
BFME_THIS_FORWARD( Rva005E5820Forwarder, Gen005E19B0 )
BFME_THIS_FORWARD( Rva005E5830Forwarder, Gen005E1B50 )
BFME_THIS_FORWARD( Rva005F2D70Forwarder, Gen005DF2D0 )
BFME_THIS_FORWARD( Rva005F36C0Forwarder, Gen005DEEE0 )
BFME_THIS_FORWARD( Rva005F4FE0Forwarder, Gen005DF510 )
BFME_THIS_FORWARD( Rva005F6580Forwarder, Gen005DF120 )
BFME_THIS_FORWARD( Rva005F7970Forwarder, Gen005DF480 )
BFME_THIS_FORWARD( Rva005F8530Forwarder, Gen005DEF70 )
BFME_THIS_FORWARD( Rva00765AF0Forwarder, Gen00761E10 )
BFME_THIS_FORWARD( Rva0088CDC0Forwarder, Gen0088C550 )
