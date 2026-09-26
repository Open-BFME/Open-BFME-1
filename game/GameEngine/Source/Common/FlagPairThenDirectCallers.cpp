// One hundred and fifteen 45-byte bodies that hand a virtual call a two-byte
// object whose two fields are both set to 1, then forward the same object to a
// direct call on `this`.
//
//     push ecx / push esi / mov esi,[esp+0xC] / push edi / mov edi,ecx
//     mov al,1 / lea ecx,[esp+8] / mov [esp+8],al / mov [esp+9],al
//     mov eax,[esi] / push ecx / mov ecx,esi / call dword ptr [eax+0x28]
//     push esi / mov ecx,edi / call <REL32> / pop edi / pop esi / pop ecx
//     ret 4
//
// THE FAMILY IS INVISIBLE TO BYTE-IDENTITY GROUPING.  The trailing `call` is a
// REL32: a call to one fixed callee encodes a DIFFERENT four-byte displacement
// from every one of the 115 addresses, so the members are identical in every
// byte except the four that are obliged to differ.  Masking the displacement
// before grouping is what found them.
//
// WHAT THE BYTES SHOW.  This is the 48-byte shape of
// PairedFlagVirtualCallers.cpp with its second call changed.  The leading
// `push ecx` opens a four-byte frame slot -- nothing reads it and the matching
// `pop ecx` discards it -- and the slot is written with TWO ADJACENT BYTE
// STORES of the same 1 before its ADDRESS is pushed, so the callee receives a
// two-field object by reference with both fields true.  A two-byte class with
// two bool members is the only layout that produces two byte stores one apart.
// `ret 4` with `this` read out of ecx into edi is __thiscall with one stack
// argument.
//
// THE ONLY AXIS IS THE REL32 TARGET.  The second call is not virtual: it is a
// direct call whose ecx is `this`, so it is a non-virtual member of the calling
// class (or of a base of it), and it takes the SAME target pointer as its one
// argument -- the callee pops it, which is what makes the three trailing pops
// restore the right registers.  115 members resolve to 24 distinct callees;
// every other byte of all 115 bodies is identical.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Twenty-four different call targets cannot
// be one COMDAT, and within one target the copies are separate instantiations
// that merely compile identically.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the callers, the
// callees, the target interface or the flag pair.  Every name here is derived
// from an address and asserts no identity; the callee pins are likewise
// address-derived and additive.

struct FlagPair
{
	bool m_first;
	bool m_second;
};

class FlagPairTarget
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void applyFlags( const FlagPair &flags );
};

// One class per distinct REL32 target; the caller derives from it so `this`
// reaches the callee unadjusted.
#define BFME_FLAG_PAIR_CALLEE( ADDR )                                         \
	class Gen##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		void handle( FlagPairTarget *target );                                \
	};

#define BFME_FLAG_PAIR_THEN_CALL( NAME, CALLEE )                              \
	class NAME : public CALLEE                                                \
	{                                                                         \
	public:                                                                   \
		void invoke( FlagPairTarget *target );                                \
	};                                                                        \
	void NAME::invoke( FlagPairTarget *target )                               \
	{                                                                         \
		FlagPair flags;                                                       \
		flags.m_first = true;                                                 \
		flags.m_second = true;                                                \
		target->applyFlags( flags );                                          \
		handle( target );                                                     \
	}


BFME_FLAG_PAIR_CALLEE( 000A1510 )
BFME_FLAG_PAIR_CALLEE( 001139A0 )
BFME_FLAG_PAIR_CALLEE( 00113D50 )
BFME_FLAG_PAIR_CALLEE( 00113E70 )
BFME_FLAG_PAIR_CALLEE( 0016B140 )
BFME_FLAG_PAIR_CALLEE( 001B0E20 )
BFME_FLAG_PAIR_CALLEE( 001EF3D0 )
BFME_FLAG_PAIR_CALLEE( 002077D0 )
BFME_FLAG_PAIR_CALLEE( 0020F330 )
BFME_FLAG_PAIR_CALLEE( 00216170 )
BFME_FLAG_PAIR_CALLEE( 00217810 )
BFME_FLAG_PAIR_CALLEE( 002298B0 )
BFME_FLAG_PAIR_CALLEE( 002475A0 )
BFME_FLAG_PAIR_CALLEE( 0024F500 )
BFME_FLAG_PAIR_CALLEE( 00250A40 )
BFME_FLAG_PAIR_CALLEE( 00255160 )
BFME_FLAG_PAIR_CALLEE( 00256C90 )
BFME_FLAG_PAIR_CALLEE( 00268060 )
BFME_FLAG_PAIR_CALLEE( 00271DB0 )
BFME_FLAG_PAIR_CALLEE( 002A7790 )
BFME_FLAG_PAIR_CALLEE( 002B2080 )
BFME_FLAG_PAIR_CALLEE( 002CD700 )
BFME_FLAG_PAIR_CALLEE( 002D9BD0 )
BFME_FLAG_PAIR_CALLEE( 00776AC0 )

BFME_FLAG_PAIR_THEN_CALL( Rva0014F1A0Caller, Gen0016B140 )
BFME_FLAG_PAIR_THEN_CALL( Rva0016B5C0Caller, Gen000A1510 )
BFME_FLAG_PAIR_THEN_CALL( Rva0016D1D0Caller, Gen0016B140 )
BFME_FLAG_PAIR_THEN_CALL( Rva0016E190Caller, Gen0016B140 )
BFME_FLAG_PAIR_THEN_CALL( Rva001EF3D0Caller, Gen00113D50 )
BFME_FLAG_PAIR_THEN_CALL( Rva001F7290Caller, Gen002077D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00200890Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva002051C0Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00205950Caller, Gen002B2080 )
BFME_FLAG_PAIR_THEN_CALL( Rva0020DA90Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00213950Caller, Gen0020F330 )
BFME_FLAG_PAIR_THEN_CALL( Rva00213B30Caller, Gen0020F330 )
BFME_FLAG_PAIR_THEN_CALL( Rva00214070Caller, Gen0020F330 )
BFME_FLAG_PAIR_THEN_CALL( Rva00214310Caller, Gen0020F330 )
BFME_FLAG_PAIR_THEN_CALL( Rva002147A0Caller, Gen0020F330 )
BFME_FLAG_PAIR_THEN_CALL( Rva00216170Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002168C0Caller, Gen00216170 )
BFME_FLAG_PAIR_THEN_CALL( Rva00216B10Caller, Gen00216170 )
BFME_FLAG_PAIR_THEN_CALL( Rva00217550Caller, Gen00216170 )
BFME_FLAG_PAIR_THEN_CALL( Rva00217CD0Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva00217FC0Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva002182E0Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva00218830Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva002189C0Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva00218C50Caller, Gen00217810 )
BFME_FLAG_PAIR_THEN_CALL( Rva00220380Caller, Gen002298B0 )
BFME_FLAG_PAIR_THEN_CALL( Rva0024D3A0Caller, Gen002475A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva0024F760Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva0024FA40Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva0024FDC0Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva0024FFC0Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva00250210Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva00250420Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva00250600Caller, Gen0024F500 )
BFME_FLAG_PAIR_THEN_CALL( Rva002509F0Caller, Gen00250A40 )
BFME_FLAG_PAIR_THEN_CALL( Rva00250A40Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00251830Caller, Gen00250A40 )
BFME_FLAG_PAIR_THEN_CALL( Rva00253CE0Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00253F90Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva002547A0Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva00254CB0Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva002550E0Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva00255160Caller, Gen001EF3D0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00255480Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva002557C0Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva00255A00Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva00255BA0Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva00256200Caller, Gen00255160 )
BFME_FLAG_PAIR_THEN_CALL( Rva002566D0Caller, Gen00256C90 )
BFME_FLAG_PAIR_THEN_CALL( Rva00256C90Caller, Gen002B2080 )
BFME_FLAG_PAIR_THEN_CALL( Rva00257530Caller, Gen00256C90 )
BFME_FLAG_PAIR_THEN_CALL( Rva00256D70Caller, Gen00256C90 )
BFME_FLAG_PAIR_THEN_CALL( Rva00256DE0Caller, Gen00256C90 )
BFME_FLAG_PAIR_THEN_CALL( Rva00258600Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva002591D0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00259780Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00259D90Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025A090Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025A990Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025AEA0Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025B5E0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025D7A0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025F220Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025FA80Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva0025FEB0Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva00260BA0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00262C30Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00263BA0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva002640C0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00264590Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00264950Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva00265A40Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026B190Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026B570Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026B7A0Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026C600Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026CE00Caller, Gen00268060 )
BFME_FLAG_PAIR_THEN_CALL( Rva0026DF10Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva0027FD30Caller, Gen002B2080 )
BFME_FLAG_PAIR_THEN_CALL( Rva0028C410Caller, Gen002B2080 )
BFME_FLAG_PAIR_THEN_CALL( Rva00292880Caller, Gen002B2080 )
BFME_FLAG_PAIR_THEN_CALL( Rva002984F0Caller, Gen002A7790 )
BFME_FLAG_PAIR_THEN_CALL( Rva002C4750Caller, Gen00271DB0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002C5530Caller, Gen00271DB0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002C7190Caller, Gen00271DB0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002C76C0Caller, Gen00271DB0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002CF1A0Caller, Gen002CD700 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D2BE0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D3040Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D3930Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D3F50Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D42D0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D4E50Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D5140Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D53B0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D60D0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D62E0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D6550Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D6800Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D7910Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D7C30Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D7F80Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D8130Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D95D0Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002D9970Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002DA460Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva002DA660Caller, Gen002D9BD0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00603070Caller, Gen00113E70 )
BFME_FLAG_PAIR_THEN_CALL( Rva006BC600Caller, Gen001B0E20 )
BFME_FLAG_PAIR_THEN_CALL( Rva00750300Caller, Gen001139A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00751210Caller, Gen001139A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00751710Caller, Gen001139A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00759370Caller, Gen001139A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva00759880Caller, Gen00776AC0 )
BFME_FLAG_PAIR_THEN_CALL( Rva0077D3F0Caller, Gen001139A0 )
BFME_FLAG_PAIR_THEN_CALL( Rva0077E160Caller, Gen00776AC0 )
BFME_FLAG_PAIR_THEN_CALL( Rva0077F280Caller, Gen001139A0 )


// THE SAME TWO CALLS IN THE OPPOSITE ORDER -- eighteen 37-byte bodies:
//
//     push esi / mov esi,[esp+8] / push esi / call <REL32> / mov al,1
//     lea ecx,[esp+8] / mov [esp+8],al / mov [esp+9],al / mov eax,[esi]
//     push ecx / mov ecx,esi / call dword ptr [eax+0x28] / pop esi / ret 4
//
// Same entry (`ret 4`, `this` from ecx), same flag pair, same virtual slot
// 0x28, same non-virtual callee taking the target pointer -- but the direct
// call runs FIRST and the flag pair is built afterwards.  Eight bytes shorter
// because the flag pair is written into the INCOMING ARGUMENT'S OWN STACK SLOT
// (`lea ecx,[esp+8]` with esp four below entry is [entry+4], the argument)
// rather than into a slot opened by a leading `push ecx`: the argument is dead
// once it has been copied into esi, so the local reuses it.  That reuse is a
// consequence of the statement order, not a separate source construct.
//
// Both callees these eighteen reach -- 0x000A1510 and 0x00113E70 -- are already
// callees of the 115-body family above, which is why this family lives in this
// file and adds NO new pin.

#define BFME_CALL_THEN_FLAG_PAIR( NAME, CALLEE )                              	class NAME : public CALLEE                                                 	{                                                                          	public:                                                                    		void invoke( FlagPairTarget *target );                                   	};                                                                         	void NAME::invoke( FlagPairTarget *target )                                	{                                                                          		handle( target );                                                        		FlagPair flags;                                                          		flags.m_first = true;                                                    		flags.m_second = true;                                                   		target->applyFlags( flags );                                             	}

BFME_CALL_THEN_FLAG_PAIR( Rva001139A0CallThenFlagPair, Gen00113E70 )
BFME_CALL_THEN_FLAG_PAIR( Rva0015FA90CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016AAD0CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016AB20CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016AB70CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016ABC0CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016AC10CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016AC80CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016ACB0CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016B200CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva0016CB30CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva002B6440CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva002BBA90CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva002C5A00CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva002C8140CallThenFlagPair, Gen000A1510 )
BFME_CALL_THEN_FLAG_PAIR( Rva00604F40CallThenFlagPair, Gen00113E70 )
BFME_CALL_THEN_FLAG_PAIR( Rva006069A0CallThenFlagPair, Gen00113E70 )
BFME_CALL_THEN_FLAG_PAIR( Rva00607F10CallThenFlagPair, Gen00113E70 )
