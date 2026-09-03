// cl: /EHsc
//
// Seven 102-byte __thiscall members identical in shape to
// Q4NewInlineCtorMembers.cpp except that the receiver is ADJUSTED BY -0x14
// before it is handed to the constructor, plus one 105-byte sibling at
// 0x005E5D90 whose only size delta is `push 0x90` (5B) versus `push imm8`
// (2B) for the smaller allocations:
//
//     push <SIZE> / mov edi,ecx / call operator new / mov esi,eax
//     test / je null
//     add edi,-0x14 / push edi / mov ecx,esi / call <BASE CTOR>
//     mov [esi],<V0> / mov [esi+4],<V1> / mov [esi+<8 or 0xc>],<V2>
//     return esi
//
// WHAT THE BYTES SHOW.  `add edi,-0x14` is UNGUARDED: no null test precedes
// it, which is what a pointer adjustment on `this` looks like -- `this` cannot
// be null, so the compiler emits the subtraction bare.  A guarded adjust would
// mean a possibly-null pointer being converted; there is none here.  The
// adjustment is spelled as an explicit cast of `this - 0x14` rather than as a
// base-to-derived static_cast, because a cast asserts only the arithmetic the
// bytes show, while an inheritance spelling would additionally claim that this
// function's class is a base sitting at +0x14 of something.  What is certain
// is only that the constructor receives the receiver minus 0x14.
//
// The three constant stores are vftables again, and the store order is again
// +0 first -- so, exactly as in the sibling family, the two later ones are
// MEMBER subobjects and not secondary bases.  Here the base occupies only 4
// bytes (vptr, no data), so the members land at +4 and then at +8 or +0xc:
// five members put the third vptr at +8 (a 4-byte middle subobject) and two
// put it at +0xc (an 8-byte middle subobject).  That split is read straight
// off the displacement and is the only layout difference among the seven.
//
// THE VARYING AXIS IS THREE FIELDS: allocation size, third-vptr offset, and
// the base constructor's REL32.  Seven members, seven distinct constructors,
// sizes 0x10 (x2), 0x18, 0x1c, 0x28, 0x40, 0x4c; the two 0x10 members differ
// in their constructors, and the +0xc offset appears under two different sizes
// and two different constructors, so no field stands in for another.  As in
// the sibling family the vftable addresses are DIR32 operands copied from
// retail -- not evidence, but they force seven distinct classes.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived; nothing here
// names the adjusted-to type, which is why it appears only as an incomplete
// `OwnerY<RVA>`.
//
#define Q4_MID_DECL( T, MIDEXTRA )                                        	class OwnerY##T;                                                      	class BaseY##T                                                        	{                                                                     	public:                                                               		BaseY##T( OwnerY##T *owner );                                     		virtual void b0();                                                	};                                                                    	class MidY##T { public: virtual void m0(); MIDEXTRA };                	class TailY##T { public: virtual void t0(); };

#define Q4_MID_BODY( T, PAD )                                             	class GenY##T : public BaseY##T                                       	{                                                                     	public:                                                               		GenY##T( OwnerY##T *owner ) : BaseY##T( owner ) { }               		virtual void b0();                                                		MidY##T m_mid;                                                    		TailY##T m_tail;                                                  		PAD                                                               	};                                                                    	class HostY##T { public: GenY##T *create(); };                        	GenY##T *HostY##T::create()                                           	{                                                                     		return new GenY##T( (OwnerY##T *)( (char *)this - 0x14 ) );       	}

Q4_MID_DECL( 005E4C10, char m_data[ 4 ]; )
Q4_MID_BODY( 005E4C10, char m_pad[ 0xc ]; )

Q4_MID_DECL( 005E6030,  )
Q4_MID_BODY( 005E6030, char m_pad[ 0x4 ]; )

Q4_MID_DECL( 005E6160,  )
Q4_MID_BODY( 005E6160, char m_pad[ 0x4 ]; )

Q4_MID_DECL( 005E6290, char m_data[ 4 ]; )
Q4_MID_BODY( 005E6290, char m_pad[ 0x8 ]; )

Q4_MID_DECL( 005E7360,  )
Q4_MID_BODY( 005E7360, char m_pad[ 0x40 ]; )

Q4_MID_DECL( 005E7620,  )
Q4_MID_BODY( 005E7620, char m_pad[ 0x1c ]; )

Q4_MID_DECL( 005E7940,  )
Q4_MID_BODY( 005E7940, char m_pad[ 0x34 ]; )

Q4_MID_DECL( 005E5D90,  )
Q4_MID_BODY( 005E5D90, char m_pad[ 0x84 ]; )

